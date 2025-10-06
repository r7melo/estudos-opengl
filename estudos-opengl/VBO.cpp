#include"VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID); // Gera o VBO
	glBindBuffer(GL_ARRAY_BUFFER, ID); // Define o VBO como o buffer de vértices atual
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Copia os dados dos vértices para o VBO
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID); // Vincula o VBO
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Desvincula o VBO
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID); // Deleta o VBO
}