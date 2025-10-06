#include"EBO.h"

EBO::EBO(GLuint* indeces, GLsizeiptr size)
{
	glGenBuffers(1, &ID); // Gera o EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // Define o EBO como o buffer de vértices atual
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, GL_STATIC_DRAW); // Copia os dados dos vértices para o EBO
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // Vincula o EBO
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Desvincula o EBO
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID); // Deleta o EBO
}