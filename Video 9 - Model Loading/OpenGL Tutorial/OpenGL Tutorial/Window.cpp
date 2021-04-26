#include "Window.h"
#include <iostream>

//new***************************
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//******************************

Window::Window(int width, int height, const char* title)
	: width(width), height(height), title(title)
{
}

//new******************************
Window::Window(int width, int height, const char* title, const char* iconFilename)
	: width(width), height(height), title(title), iconFilename(iconFilename)
{
}
//*********************************

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


	//new******************************
	if (iconFilename != nullptr)
	{
		GLFWimage images[1]; 
		images[0].pixels = stbi_load(iconFilename, &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(window, 1, images); 
		stbi_image_free(images[0].pixels);
	}
	//new******************************


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


//new******************************
void Window::processKeyboard(GLFWwindow* window, int key, int code, int action, int mode)
{
	std::cout << (char)key << std::endl;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void Window::processMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window& myWindow = *static_cast<Window*>(glfwGetWindowUserPointer(window));
	myWindow.mousePos = glm::vec2(xPos, yPos);
	
	std::string mousePos = "xPos: " + std::to_string(xPos) + " yPos: " + std::to_string(yPos);
	myWindow.setTitle(mousePos.c_str());//new************
}

void Window::setCallbacks()
{ // set the glfw window callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, processKeyboard);
	glfwSetCursorPosCallback(window, processMouse);
}
//new******************************