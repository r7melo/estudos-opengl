#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Meu Primeiro App OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Falha ao criar janela GLFW" << std::endl;
		glfwTerminate();
		return -1;

	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}