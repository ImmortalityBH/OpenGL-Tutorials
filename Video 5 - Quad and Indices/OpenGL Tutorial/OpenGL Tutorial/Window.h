#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window() = default;
	Window(int width, int height, const char* title);
	~Window();

	bool init();
	bool isOpen() const { return !glfwWindowShouldClose(window); }
	void swapBuffers() const { glfwSwapBuffers(window); }
	void prepare(const float r, const float g, const float b);
	void handleEvents() const { glfwPollEvents(); }

	void setTitle(const char* title) { glfwSetWindowTitle(window, title); }

	GLFWwindow& getWindow() const { return *window; }

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//static void processKeyboard(GLFWwindow* window, int key, int code, int action, int mode);
	//static void processMouse(GLFWwindow* window, double xPos, double yPos);

	void setCallbacks();
private:
	GLFWwindow* window;
	int width, height;
	const char* title;
};

