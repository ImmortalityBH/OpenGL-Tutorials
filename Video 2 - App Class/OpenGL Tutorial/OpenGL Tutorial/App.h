#pragma once

#include "Window.h"

class App
{
public:
	App();
	~App() = default;

	bool run();

private:
	Window window;
};

