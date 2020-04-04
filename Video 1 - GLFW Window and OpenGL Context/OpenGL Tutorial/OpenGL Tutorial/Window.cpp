#include "Window.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
	: width(width), height(height), title(title)
{
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "GLFW window initialization failed!\n";
		glfwTerminate();
		return false;
	}
	//glfw window opengl version hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//enable forward compatiblity for apple users
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create glfw window\n";
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSwapInterval(1);
	setCallbacks();

	//glewExperimental = GL_TRUE;
	GLenum err = glewInit(); //glewInit returns glenum
	if (GLEW_OK != err)
	{
		std::cout << "GLEW ERROR: " << glewGetErrorString(err) << "\n";
		return false;
	}
	//sets the opengl viewport to the width and height of our window
	glViewport(0, 0, width, height);
	
	//enables depth testing for 3d graphics
	glEnable(GL_DEPTH_TEST);
	return true;
}

void Window::prepare(const float r, const float g, const float b)
{
	//clears the color buffer, good practice
	//depth buffer bit lets opengl know if a mesh is closer than another mesh
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //parameter is bitflag
	glClearColor(r, g, b, 1.0f); //clears the color buffers 
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); //set the viewport to the new width and height
}

void Window::setCallbacks()
{ // set the glfw window callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
