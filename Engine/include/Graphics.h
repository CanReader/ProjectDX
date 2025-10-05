#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <Windows.h>
#include <memory>

class Directx11;
class Object;

class Graphics
{
public:
	Graphics() = delete;
	Graphics(HWND hWnd,int width,int height);
	~Graphics();

	void BeginFrame();
	void EndFrame();

	void RenderObject(const std::shared_ptr<Object>& object);

	void SetVsync(bool bEnable);
	void SetFullScreen(bool bEnable);

private:
	std::shared_ptr<Directx11> d3d11;

};

#endif