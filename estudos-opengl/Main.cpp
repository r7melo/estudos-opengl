#include <iostream>        // Biblioteca padr�o para entrada e sa�da (ex: cout)
#include <glad/glad.h>     // Carrega todas as fun��es modernas do OpenGL
#include <GLFW/glfw3.h>    // Gerencia janelas e contexto do OpenGL


// C�digo-fonte do Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// C�digo-fonte do Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {
    // Inicializa a biblioteca GLFW
    glfwInit();

    // Define a vers�o do OpenGL que ser� usada (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Define o perfil do OpenGL como "CORE" (apenas fun��es modernas)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Define os v�rtices do tri�ngulo (posi��o XYZ)
    GLfloat vertices[] = {
         -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Inferior esquerdo
          0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Inferior direito
		  0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f  // Superior
	};

    // Cria uma janela 800x800 chamada "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);

    // Verifica se a janela foi criada corretamente
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl; // Mensagem de erro
        glfwTerminate();  // Finaliza o GLFW e libera recursos
        return -1;        // Encerra o programa com erro
    }

    // Define a janela criada como o contexto atual do OpenGL
    glfwMakeContextCurrent(window);

    // Carrega todas as fun��es OpenGL com o GLAD
    gladLoadGL();

    // Define a �rea de renderiza��o (de 0,0 at� 800,800)
    glViewport(0, 0, 800, 800);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Cria o Vertex Shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Anexa o c�digo-fonte ao Vertex Shader
	glCompileShader(vertexShader); // Compila o Vertex Shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Cria o Fragment Shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Anexa o c�digo-fonte ao Fragment Shader
	glCompileShader(fragmentShader); // Compila o Fragment Shader


	GLuint shaderProgram = glCreateProgram(); // Cria o programa de shader

	glAttachShader(shaderProgram, vertexShader); // Anexa o Vertex Shader ao programa
	glAttachShader(shaderProgram, fragmentShader); // Anexa o Fragment Shader ao programa
	glLinkProgram(shaderProgram); // Linka o programa de shader

	glDeleteShader(vertexShader); // Deleta o Vertex Shader (n�o � mais necess�rio ap�s o link)
	glDeleteShader(fragmentShader); // Deleta o Fragment Shader (n�o � mais necess�rio ap�s o link)


	GLuint VAO, VBO; // Vari�veis para o Vertex Array Object e Vertex Buffer Object

	glGenVertexArrays(1, &VAO); // Gera o VAO
	glGenBuffers(1, &VBO); // Gera o VBO

	glBindVertexArray(VAO); // Vincula o Vertex Array Object (VAO)

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Garante que o VBO est� vinculado antes de configurar os atributos
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copia os dados dos v�rtices para o buffer

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Define o formato dos dados de v�rtices
	glEnableVertexAttribArray(0); // Habilita o atributo de v�rtice (posi��o)

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Desvincula o VBO (opcional)
	glBindVertexArray(0); // Desvincula o VAO (opcional)


    // Define a cor de fundo (RGBA: azul escuro)
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    // Limpa o buffer de cor aplicando a cor definida
    glClear(GL_COLOR_BUFFER_BIT);

    

    // Loop principal � mant�m a janela aberta at� o usu�rio fech�-la
    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Define a cor de fundo
		glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor
		glUseProgram(shaderProgram); // Usa o programa de shader
		glBindVertexArray(VAO); // Vincula o VAO
		glDrawArrays(GL_TRIANGLES, 0, 3); // Desenha o tri�ngulo


        // Troca o buffer de fundo com o buffer vis�vel (mostra o resultado na tela)
        glfwSwapBuffers(window);

        // Processa eventos (como teclado, mouse, etc.)
        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO); // Deleta o VAO
	glDeleteBuffers(1, &VBO); // Deleta o VBO
	glDeleteProgram(shaderProgram); // Deleta o programa de shader

    // Destroi a janela e libera mem�ria
    glfwDestroyWindow(window);

    // Finaliza a biblioteca GLFW
    glfwTerminate();

    // Encerra o programa com sucesso
    return 0;
}
