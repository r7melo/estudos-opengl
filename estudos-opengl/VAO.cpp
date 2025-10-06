#include"VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID); // Gera o VAO
}

void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID); // Vincula o VAO
}

void VAO::Unbind()
{
	glBindVertexArray(0); // Desvincula o VAO
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID); // Deleta o VAO
}