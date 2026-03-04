#ifndef _DEBUGMESSAGEQUEUE_H_
#define _DEBUGMESSAGEQUEUE_H_

#include <d3d11.h>
#include <cstdint>
#include <unordered_set>
#include <wrl/client.h>

enum class Severity : uint8_t {
	Info = 0,
	Warning = 1,
	Error = 2,
	Fatal = 3
};

class DebugMessageQueue
{
public:
	DebugMessageQueue() = default;
	~DebugMessageQueue();

	bool Initialize(ID3D11Device* device);
	void Update();

	void SetBreakOnSeverity(Severity severity, bool bEnable);
	void EnableSeverity(Severity severity, bool bEnable);
private:

	void ProcessMessage(const D3D11_MESSAGE& message);
	bool ShouldPrint(const D3D11_MESSAGE& message);
	void PrintMessage(const D3D11_MESSAGE& message);

	uint64_t ComputeMessageHash(const D3D11_MESSAGE& message);
	Severity ConvertSeverity(const D3D11_MESSAGE_SEVERITY& severity);
	D3D11_MESSAGE_SEVERITY ConvertSeverityDX(const Severity & severity);

private:
	Microsoft::WRL::ComPtr<ID3D11InfoQueue> info;
	std::unordered_set<uint64_t> SeenMessages;

	bool SeverityEnabled[4] = {true, true, true, true};
};

#endif