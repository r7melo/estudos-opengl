#ifndef SHADER_CLASS
#define SHADER_CLASS

#include <glad/glad.h> // Inclui o GLAD para carregar as funções do OpenGL
#include <string>     // Inclui a biblioteca padrão de strings
#include <fstream>    // Inclui a biblioteca para manipulação de arquivos
#include <sstream>    // Inclui a biblioteca para manipulação de streams
#include <cerrno>     // Inclui a biblioteca para manipulação de erros

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