#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h> // Inclui o GLAD para carregar as funções do OpenGL

class EBO
{
	public:
		GLuint ID;
		EBO(GLuint* indices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
};

#endif