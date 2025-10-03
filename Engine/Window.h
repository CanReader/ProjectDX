#pragma once

#include <Windows.h>
#include <memory>

#ifdef ENGINE_EXPORT 
#define	DLL_API __declspec(dllexport)
#else
#define	DLL_API __declspec(dllimport)
#endif // ENGINE_EXPORT


DLL_API class Window
{
public:
	Window& operator=(const Window&) = delete;
	DLL_API ~Window();
	inline static Window& getInstance() {
		if (TheWindowInstance == nullptr)
			TheWindowInstance = std::make_unique<Window>();
		return *TheWindowInstance;
	}

	DLL_API bool Initialize(const char* name, int width, int height);
	DLL_API void MessageLoop();
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT Message, WPARAM wParam, LPARAM lParam);
private:
	Window() {}

	HWND hWnd;

	DLL_API static std::unique_ptr<Window> TheWindowInstance;
	DLL_API friend std::unique_ptr<Window> std::make_unique<Window>();
};

