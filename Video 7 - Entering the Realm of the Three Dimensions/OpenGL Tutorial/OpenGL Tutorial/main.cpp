#include <iostream>
#include "App.h"

int main()
{
	App app;
	if (!app.run())
	{
		std::cout << "uh oh\n";
		return -1;
	}
	return 0;
}