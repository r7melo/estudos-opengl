#include"VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID); // Gera o VAO
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLuint type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
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