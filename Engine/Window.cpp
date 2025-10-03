#include "Window.h"

std::unique_ptr<Window> Window::TheWindowInstance;

Window::~Window()
{
}

bool Window::Initialize(const char* name, int width, int height)
{
	WNDCLASSEX wnd;
	ZeroMemory(&wnd,sizeof(WNDCLASSEX));
	wnd.cbClsExtra = NULL;
	wnd.cbWndExtra = NULL;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.hCursor = LoadCursor(GetModuleHandle(NULL),IDC_ARROW);
	wnd.hIcon = LoadIcon(GetModuleHandle(NULL),IDI_APPLICATION);
	wnd.hIconSm = LoadIcon(GetModuleHandle(NULL), IDI_APPLICATION);
	wnd.lpfnWndProc = Window::WndProc;
	wnd.lpszClassName = L"WClass";
	wnd.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wnd))
		return false;

	hWnd = CreateWindowExA(
		WS_EX_APPWINDOW,
		"WClass",
		name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, NULL,
		GetModuleHandle(NULL),
		NULL);

	if (!hWnd)
		return false;

	ShowWindow(hWnd,SW_SHOW);
	ShowCursor(SW_SHOW);
	BringWindowToTop(hWnd);

	return true;
}

void Window::MessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//Render our scene!
		}
	}
}

LRESULT Window::WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		FreeConsole();
		return 0;
	}break;
	default: 
		return DefWindowProc(hWnd,Message,wParam,lParam);
	}
}
