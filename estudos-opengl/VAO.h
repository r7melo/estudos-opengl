#ifndef VA0_CLASS_H
#define VA0_CLASS_H

#include <glad/glad.h> // Inclui o GLAD para carregar as funções do OpenGL
#include"VBO.h"

class VAO
{
	public:
		GLuint ID;
		VAO();

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
};

#endif