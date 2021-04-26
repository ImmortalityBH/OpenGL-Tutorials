#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

class Window
{
public:
	Window() = default;
	Window(int width, int height, const char* title);
	Window(int width, int height, const char* title, const char* iconFilename);//new******************************
	~Window();

	bool init();
	bool isOpen() const { return !glfwWindowShouldClose(window); }
	void swapBuffers() const { glfwSwapBuffers(window); }
	void prepare(const float r, const float g, const float b);
	void handleEvents() const { glfwPollEvents(); }

	void setTitle(const char* title) { glfwSetWindowTitle(window, title); }

	GLFWwindow& getWindow() const { return *window; }

	//new**************************
	int getWidth() { return width; }
	int getHeight() { return height; }
	//*****************************
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//new******************************
	static void processKeyboard(GLFWwindow* window, int key, int code, int action, int mode);//keycallback
	static void processMouse(GLFWwindow* window, double xPos, double yPos);//mousecallback
	//new******************************

	void setCallbacks();
private:
	GLFWwindow* window;
	int width, height;
	const char* title;
	const char* iconFilename = nullptr;//new******************************
public:
	glm::vec2 mousePos;

};

