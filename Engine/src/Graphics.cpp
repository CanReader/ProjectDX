#include "Graphics.h"
#include "Directx11.h"
#include <stdexcept>

Graphics::Graphics(HWND hWnd, int width, int height)
{
	d3d11 = std::make_shared<Directx11>();

	if (!d3d11->Initialize(hWnd, width, height))
		throw std::runtime_error("Failed to create directx11 device!");
}

Graphics::~Graphics()
{
}

void Graphics::BeginFrame() 
{
	d3d11->BeginFrame();
}

void Graphics::EndFrame()
{
	d3d11->EndFrame();
}

void Graphics::RenderObject(const std::shared_ptr<Object>& object) 
{
	//TODO: Handle rendering objects... (In Next Lecture)
}

void Graphics::SetFullScreen(bool bEnable) 
{
	d3d11->SetFullScreen(bEnable);
}

void Graphics::SetVsync(bool bEnable) 
{
	d3d11->SetVsync(bEnable);
}