#include"shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Cria o Vertex Shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // Anexa o código-fonte ao Vertex Shader
	glCompileShader(vertexShader); // Compila o Vertex Shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Cria o Fragment Shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Anexa o código-fonte ao Fragment Shader
	glCompileShader(fragmentShader); // Compila o Fragment Shader


	ID = glCreateProgram(); // Cria o programa de shader

	glAttachShader(ID, vertexShader); // Anexa o Vertex Shader ao programa
	glAttachShader(ID, fragmentShader); // Anexa o Fragment Shader ao programa
	glLinkProgram(ID); // Linka o programa de shader

	glDeleteShader(vertexShader); // Deleta o Vertex Shader (não é mais necessário após o link)
	glDeleteShader(fragmentShader); // Deleta o Fragment Shader (não é mais necessário após o link)
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}