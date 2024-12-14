#include <GL/glew.h>

#include <glm/glm.hpp>
#include <iostream>

#include "Game.h"

void window_resize_callback(GLFWwindow* window, int width, int height);
void key_pressed_callback(GLFWwindow* window, int key, int scancode, int action, int mod);

Game* new_game;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(800, 600, "ProjectTerrain", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, window_resize_callback);
	glfwSetKeyCallback(window, key_pressed_callback);

	glewInit();

	new_game = new Game;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		new_game->OnUpdate();
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void key_pressed_callback(GLFWwindow* window, int key,int scancode, int action, int mod)
{
	new_game->OnKeyPressed(window,key, action,mod);
}


void window_resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}