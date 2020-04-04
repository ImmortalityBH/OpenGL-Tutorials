#include "App.h"
#include <iostream>

App::App()
	:
	window(800, 600, "Window")
{
}

bool App::run()
{
	if (!window.init())
	{
		std::cout << "uh oh\n";
		return false;
	}
	while (window.isOpen())
	{
		window.handleEvents();
		window.prepare(1.0f, .0f, 1.0f);

		window.swapBuffers();
	}
	return true;
}
