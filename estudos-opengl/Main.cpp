#include <iostream>        // Biblioteca padrão para entrada e saída (ex: cout)
#include <glad/glad.h>     // Carrega todas as funções modernas do OpenGL
#include <GLFW/glfw3.h>    // Gerencia janelas e contexto do OpenGL

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Define os vértices do triângulo (posição XYZ)
GLfloat vertices[] = 
{//|        Coordenadas                         |       Cores          //  
    -0.50f, -0.5f * float(sqrt(3)) / 3,     0.0f,   0.0f, 1.0f, 0.0f,  // Inferior esquerdo
     0.50f, -0.5f * float(sqrt(3)) / 3,     0.0f,   1.0f, 0.0f, 0.0f,  // Inferior direito
     0.00f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   0.0f, 0.0f, 1.0f,  // Superior
    -0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,   1.0f, 0.0f, 0.0f,  // Meio esquerdo
     0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f,   0.0f, 1.0f, 0.0f,  // Meio direito
     0.00f, -0.5f * float(sqrt(3)) / 3,     0.0f,   0.0f, 0.0f, 1.0f,  // Meio Inferior
};

GLuint indices[] = {
    0, 3, 5, // Triangulo inferior esquerdo
    3, 2, 4, // Triangulo inferior direito
    5, 4, 1  // Triangulo superior
};

int main() {
    // Inicializa a biblioteca GLFW
    glfwInit();

    // Define a versão do OpenGL que será usada (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Define o perfil do OpenGL como "CORE" (apenas funções modernas)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // Carrega todas as funções OpenGL com o GLAD
    gladLoadGL();

    // Define a área de renderização (de 0,0 até 800,800)
    glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
    
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); // Pega o local do uniforme "scale" no shader

    // Define a cor de fundo (RGBA: azul escuro)
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    // Limpa o buffer de cor aplicando a cor definida
    glClear(GL_COLOR_BUFFER_BIT);

    

    // Loop principal — mantém a janela aberta até o usuário fechá-la
    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Define a cor de fundo
		glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor
		
		shaderProgram.Activate(); // Ativa o programa de shader
		glUniform1f(uniID, 1.0f); // Define o valor do uniforme "scale" para 0.5
		VAO1.Bind(); // Vincula o VAO (prepara o triângulo para ser desenhado)

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Desenha o triângulo


        // Troca o buffer de fundo com o buffer visível (mostra o resultado na tela)
        glfwSwapBuffers(window);

        // Processa eventos (como teclado, mouse, etc.)
        glfwPollEvents();
    }

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

    // Destroi a janela e libera memória
    glfwDestroyWindow(window);

    // Finaliza a biblioteca GLFW
    glfwTerminate();

    // Encerra o programa com sucesso
    return 0;
}
