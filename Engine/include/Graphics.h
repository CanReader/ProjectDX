#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <Windows.h>
#include <memory>
#include <vector>

class Directx11;
class Object;

class Graphics
{
public:
	Graphics() = delete;
	Graphics(HWND hWnd,int width,int height);
	~Graphics();

	void RegisterObject(std::shared_ptr<Object> obj);

	void BeginFrame();
	void EndFrame();

	void RenderObjects();

	void SetVsync(bool bEnable);
	void SetFullScreen(bool bEnable);

private:
	std::shared_ptr<Directx11> d3d11;
	std::vector<std::shared_ptr<Object>> objects;
};

#endif