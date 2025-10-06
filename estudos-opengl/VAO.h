#ifndef VA0_CLASS_H
#define VA0_CLASS_H

#include <glad/glad.h> // Inclui o GLAD para carregar as funções do OpenGL
#include"VBO.h"

class VAO
{
	public:
		GLuint ID;
		VAO();

		void LinkVBO(VBO VBO, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
};

#endif