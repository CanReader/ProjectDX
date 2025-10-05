#include "Directx11.h"

Directx11::Directx11() : clearColor(new float[4] {0.3,0.4,1.0,1.0})
{
}

Directx11::~Directx11()
{
}

bool Directx11::Initialize(HWND hWnd, int width, int height)
{
	D3D_FEATURE_LEVEL featureLevels[] = {
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_1,
	D3D_FEATURE_LEVEL_10_0,
	D3D_FEATURE_LEVEL_9_3,
	D3D_FEATURE_LEVEL_9_2,
	D3D_FEATURE_LEVEL_9_1
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd,sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = 3;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.RefreshRate.Denominator = 60; //TODO: Write refresh rate handler function
	sd.BufferDesc.RefreshRate.Numerator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;    //TODO: Handle MSAA settings
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,			//TODO: Write GPU handler function
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG,
		featureLevels,
		numFeatureLevels,
		D3D11_SDK_VERSION,
		&sd,
		swapChain.GetAddressOf(),
		dev.GetAddressOf(),
		nullptr,
		devcon.GetAddressOf()
	);

	if (FAILED(hr))
		return false;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr))
		return false;

	hr = dev->CreateRenderTargetView(backBuffer.Get(),nullptr,renderTargetView.GetAddressOf());

	if (FAILED(hr))
		return false;

	devcon->OMSetRenderTargets(1,renderTargetView.GetAddressOf(),nullptr);

	D3D11_VIEWPORT vp;
	vp.Width = static_cast<FLOAT>(width);
	vp.Height = static_cast<FLOAT>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	devcon->RSSetViewports(1,&vp);

	return true;
}

void Directx11::BeginFrame()
{
	devcon->ClearRenderTargetView(renderTargetView.Get(),clearColor);
}

void Directx11::EndFrame()
{
	swapChain->Present((UINT)vsync,0);
}
