#include <iostream>
#include "Window.h"

int main()
{
	Window window(800, 600, "Window");
	if (!window.init())
	{
		std::cout << "uh oh\n";
		return -1;
	}
	while (window.isOpen())
	{
		window.handleEvents();
		window.prepare(1.0f, .0f, 1.0f);

		window.swapBuffers();
	}

	return 0;
}