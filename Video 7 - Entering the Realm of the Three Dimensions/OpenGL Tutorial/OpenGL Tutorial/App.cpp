#include "App.h"
#include <iostream>
#include "Shader.h"

App::App()
	:
	window(800, 600, "Window", "bib.jpg")
{
}

bool App::run()
{
	if (!window.init())
	{
		std::cout << "Window init failed!\n";
		return false;
	}

	Shader shader("vertexShader.glsl", "fragmentShader.glsl");

	struct vertex
	{
		float x, y, z;
		float r, g, b;
	};

	//new***********************************************************
	const vertex vertices[] =
	{
		{-0.5f,0.5f,-0.5f, 1.0f, 0.0f, 0.0f },
		{-0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f },
		{0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 1.0f },
		{0.5f,0.5f,-0.5f, 1.0f, 0.0f, 0.0f },

		{-0.5f,0.5f,0.5f, 1.0f, 0.0f, 0.0f },
		{-0.5f,-0.5f,0.5f, 0.0f, 1.0f, 0.0f },
		{0.5f,-0.5f,0.5f, 0.0f, 0.0f, 1.0f },
		{0.5f,0.5f,0.5f, 1.0f, 0.0f, 0.0f },

		{0.5f,0.5f,-0.5f, 1.0f, 0.0f, 0.0f },
		{0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f },
		{0.5f,-0.5f,0.5f, 0.0f, 0.0f, 1.0f },
		{0.5f,0.5f,0.5f, 1.0f, 0.0f, 0.0f },

		{-0.5f,0.5f,-0.5f, 1.0f, 0.0f, 0.0f },
		{-0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f },
		{-0.5f,-0.5f,0.5f, 0.0f, 0.0f, 1.0f },
		{-0.5f,0.5f,0.5f, 1.0f, 0.0f, 0.0f },

		{-0.5f,0.5f,0.5f, 1.0f, 0.0f, 0.0f },
		{-0.5f,0.5f,-0.5f, 0.0f, 1.0f, 0.0f },
		{0.5f,0.5f,-0.5f, 0.0f, 0.0f, 1.0f },
		{0.5f,0.5f,0.5f, 1.0f, 0.0f, 0.0f },
	
		{-0.5f,-0.5f,0.5f, 1.0f, 0.0f, 0.0f },
		{-0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f },
		{0.5f,-0.5f,-0.5f, 0.0f, 0.0f, 1.0f },
		{0.5f,-0.5f,0.5f, 1.0f, 0.0f, 0.0f },
	};

	const GLuint indices[] =
	{
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22,
	};
	//**************************************************************

	unsigned int VAO, VBO, EBO; // vertex array object, vertex buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); // gen buffers
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO); //bind vertex array 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// static draw means the data will rarely change

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
		//new****************************************************************************
		//projection defines the clipping space and that which you can view
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(window.mousePos.x / (float)window.getWidth(), 0.0f,-(window.mousePos.y / (float)window.getHeight())));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 0.0f, 0.5f));

		shader.setMat4("projection", proj);
		shader.setMat4("view", view);
		shader.setMat4("model", model);
		//****************************************************************************

		glBindVertexArray(VAO); //bind vao and draw
		glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		window.swapBuffers();
	}
	return true;
}
