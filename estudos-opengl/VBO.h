#ifndef VB0_CLASS_H
#define VB0_CLASS_H

#include <glad/glad.h> // Inclui o GLAD para carregar as funções do OpenGL

class VBO
{
	public:
		GLuint ID;
		VBO(GLfloat* vertices, GLsizeiptr size);
		void Bind();
		void Unbind();
		void Delete();
};

#endif