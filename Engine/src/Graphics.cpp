#include "Graphics.h"
#include "Directx11.h"
#include "Logger.h"
#include <stdexcept>
#include "Object.h"

Graphics::Graphics(HWND hWnd, int width, int height)
{
	d3d11 = std::make_shared<Directx11>();

	if (!d3d11->Initialize(hWnd, width, height))
		throw std::runtime_error("Failed to create directx11 device!");
}

Graphics::~Graphics()
{
}
 
void Graphics::RegisterObject(std::shared_ptr<Object> obj)
{
	if (obj && obj->Initialize(d3d11->GetDevice())) {
		objects.push_back(obj);
		DX_INFO("Registered object: {}", obj->GetName());
	}
	else
	{
		DX_ERROR("Failed to register object: {}", obj->GetName());
	}
}

void Graphics::BeginFrame() 
{
	d3d11->BeginFrame();
}

void Graphics::EndFrame()
{
	d3d11->EndFrame();
}

void Graphics::RenderObjects() 
{
	for (auto obj : objects)
		obj->Render(d3d11->GetDeviceContext());
}

void Graphics::SetFullScreen(bool bEnable) 
{
	d3d11->SetFullScreen(bEnable);
	DX_INFO(bEnable ? "Fullscreen has been enabled" : "Fullscreen has been disabled");
}

void Graphics::SetVsync(bool bEnable) 
{
	d3d11->SetVsync(bEnable);
	DX_INFO(bEnable ? "Vsync settings has been enabled" : "Vsync settings has been disabled");
}