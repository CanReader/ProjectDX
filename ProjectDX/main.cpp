#include "../Engine/Window.h"
#include <iostream>

int main(int argc, char** argv) {

	Window& win = Window::getInstance();

	if (win.Initialize("DirectX App",1280,720))
		win.MessageLoop();
	else
		std::cerr << "Failed to create window!";
	
	return 1;
}