#include "App.h"
#include <iostream>
#include "Shader.h"

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

	Shader shader("vertexShader.glsl", "fragmentShader.glsl");

	struct vertex
	{
		float x, y, z;
		float r, g, b;
	};

	const vertex vertices[] = //vertex data to send to the gpu
	{
		{ -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
	    { 0.0f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f },
		{ 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f },
	};

	unsigned int VAO, VBO; // vertex array object, vertex buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // gen buffers

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind vertex array, and vertex buffer
																// static draw means the data will rarely change
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0); //shader attribute 0
	glEnableVertexAttribArray(0); //enable the shader input location 0
												//six strides in total  // 3 strides in for attribute 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3)); 
	glEnableVertexAttribArray(1); //enable the shader input location 1

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (window.isOpen())
	{
		window.handleEvents();
		window.prepare(1.0f, .0f, 1.0f);

		shader.use();
		glBindVertexArray(VAO); //bind vao and draw
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		window.swapBuffers();
	}
	return true;
}
