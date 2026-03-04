#include "DebugMessageQueue.h"
#include <Logger.h>

DebugMessageQueue::~DebugMessageQueue()
{
	if (info)
	{
		info->ClearStoredMessages();
		info->Release();
	}
}

bool DebugMessageQueue::Initialize(ID3D11Device* device) {

#ifdef _DEBUG
	if (!device)
		return false;

	HRESULT hr = device->QueryInterface(__uuidof(ID3D11InfoQueue),reinterpret_cast<void**>(info.GetAddressOf()));

	if (FAILED(hr))
		return false;

	SetBreakOnSeverity(Severity::Error, true);
	SetBreakOnSeverity(Severity::Fatal, true);

	return true;
#else
	return false;
#endif
}

void DebugMessageQueue::Update() {
#ifdef _DEBUG
	if (!info)
		return;

	const UINT64 count = info->GetNumStoredMessagesAllowedByRetrievalFilter();

	for (UINT64 i = 0; i < count; ++i)
	{
		SIZE_T length = 0;

		info->GetMessage(i,nullptr,&length);

		std::vector<char> buffer(length);
		D3D11_MESSAGE* message = reinterpret_cast<D3D11_MESSAGE*>(buffer.data());

		info->GetMessage(i,message,&length);

		ProcessMessage(*message);
	}

	info->ClearStoredMessages();
#endif
}

void DebugMessageQueue::SetBreakOnSeverity(Severity severity, bool bEnabled) {
#ifdef _DEBUG
	info->SetBreakOnSeverity(ConvertSeverityDX(severity),bEnabled ? TRUE : FALSE);
#endif
}

void DebugMessageQueue::EnableSeverity(Severity severity, bool bEnable)
{
	SeverityEnabled[(uint8_t)severity] = bEnable;
}

void DebugMessageQueue::ProcessMessage(const D3D11_MESSAGE& message)
{
	if (!ShouldPrint(message))
		return;

	uint64_t hash = ComputeMessageHash(message);

	// Message should be printed once!
	if (SeenMessages.find(hash) != SeenMessages.end())
		return;

	SeenMessages.insert(hash);
	PrintMessage(message);
}

bool DebugMessageQueue::ShouldPrint(const D3D11_MESSAGE& message)
{
	return SeverityEnabled[static_cast<uint8_t>(ConvertSeverity(message.Severity))];
}

void DebugMessageQueue::PrintMessage(const D3D11_MESSAGE& message)
{
	switch (message.Severity) {
	case D3D11_MESSAGE_SEVERITY_MESSAGE:
	case D3D11_MESSAGE_SEVERITY_INFO:
		DX_INFO("[DX] {}",message.pDescription);
		break;
	case D3D11_MESSAGE_SEVERITY_WARNING:
		DX_WARN("[DX] {}", message.pDescription);
		break;
	case D3D11_MESSAGE_SEVERITY_ERROR:
		DX_ERROR("[DX] {}", message.pDescription);
		break;
	case D3D11_MESSAGE_SEVERITY_CORRUPTION:
		DX_FATAL("[DX] {}", message.pDescription);
		break;
	}
}

Severity DebugMessageQueue::ConvertSeverity(const D3D11_MESSAGE_SEVERITY& severity)
{
	Severity result = Severity::Info;

	switch (severity) {
	case D3D11_MESSAGE_SEVERITY_MESSAGE:
	case D3D11_MESSAGE_SEVERITY_INFO:
		result = Severity::Info;
		break;
	case D3D11_MESSAGE_SEVERITY_WARNING:
		result = Severity::Warning;
		break;
	case D3D11_MESSAGE_SEVERITY_ERROR:
		result = Severity::Error;
		break;
	case D3D11_MESSAGE_SEVERITY_CORRUPTION:
		result = Severity::Fatal;
		break;
	default:
		result = Severity::Info;
	}

	return result;
}

D3D11_MESSAGE_SEVERITY DebugMessageQueue::ConvertSeverityDX(const Severity& severity)
{
	D3D11_MESSAGE_SEVERITY result = D3D11_MESSAGE_SEVERITY_INFO;

	switch (severity)
	{
	case Severity::Info:
		result = D3D11_MESSAGE_SEVERITY_INFO;
		break;
	case Severity::Warning:
		result = D3D11_MESSAGE_SEVERITY_WARNING;
		break;
	case Severity::Error:
		result = D3D11_MESSAGE_SEVERITY_ERROR;
		break;
	case Severity::Fatal:
		result = D3D11_MESSAGE_SEVERITY_CORRUPTION;
		break;
	default:
		result = D3D11_MESSAGE_SEVERITY_MESSAGE;
	}

	return result;
}

uint64_t DebugMessageQueue::ComputeMessageHash(const D3D11_MESSAGE& message)
{
	uint64_t hash = static_cast<uint64_t>(message.ID);
	const char* str = message.pDescription;

	while (*str)
	{
		hash = (hash * 131) + static_cast<uint64_t>(*str);
		++str;
	}

	return hash;
}
