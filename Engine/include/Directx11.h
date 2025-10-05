#ifndef _DIRECTX11_H_
#define _DIRECTX11_H_

#include <wrl/client.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <DXGI.h>
#include <memory>

class Directx11
{
public:
	Directx11();
	~Directx11();

	bool Initialize(HWND hWnd, int width, int height);
	void BeginFrame();
	void EndFrame();

	inline void SetClearColor(const float& r, const float& g, const float& b, const float& a) {
		clearColor[0] = r;
		clearColor[1] = g;
		clearColor[2] = b;
		clearColor[3] = a;
	}

	inline void SetVsync(bool bEnable) { vsync = bEnable; }
	inline bool GetVsync() { return vsync; }
	
	inline void SetFullScreen(bool bEnable) { swapChain->SetFullscreenState(bEnable,nullptr); }

private:
	Microsoft::WRL::ComPtr<ID3D11Device> dev;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> devcon;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	float* clearColor;
	bool vsync = false;
};


#endif