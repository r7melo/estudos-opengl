#ifndef SHADER_CLASS
#define SHADER_CLASS

#include <glad/glad.h> // Inclui o GLAD para carregar as fun��es do OpenGL
#include <string>     // Inclui a biblioteca padr�o de strings
#include <fstream>    // Inclui a biblioteca para manipula��o de arquivos
#include <sstream>    // Inclui a biblioteca para manipula��o de streams
#include <cerrno>     // Inclui a biblioteca para manipula��o de erros

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();
	private:
		void compileErrors(unsigned int shader, const char* type);
};

#endif