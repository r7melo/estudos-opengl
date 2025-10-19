#include <iostream>        // Biblioteca padrão para entrada e saída (ex: cout)
#include <glad/glad.h>     // Carrega todas as funções modernas do OpenGL
#include <GLFW/glfw3.h>    // Gerencia janelas e contexto do OpenGL
#include <stb/stb_image.h>

#include"shaderClass.h"
#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"




// Define os vértices do triângulo (posição XYZ)
GLfloat vertices[] =
{//|     Coordenadas  |       Cores       | Textura Coord.  //  
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // Top Right
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top Left
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Bottom Left
     0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f   // Bottom Right
};

GLuint indices[] = {
    0, 1, 2,  // Triângulo 1
	0, 2, 3  // Triângulo 2 
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
    
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// [0][1][2]-[3][4][5]-[6][7]
	// Posições |  Cores  | Texturas

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); // Pega o local do uniforme "scale" no shader






    // Texture 


	Texture popCat("C:\\Users\\Romario Melo\\Documents\\estudos-opengl\\docs\\images\\06\\pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);






    // Loop principal — mantém a janela aberta até o usuário fechá-la
    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Define a cor de fundo
		glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cor
		
		shaderProgram.Activate(); // Ativa o programa de shader
		glUniform1f(uniID, .5f); // Define o valor do uniforme "scale" para 0.5

		popCat.Bind();
		
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
	popCat.Delete();
	shaderProgram.Delete();

    // Destroi a janela e libera memória
    glfwDestroyWindow(window);

    // Finaliza a biblioteca GLFW
    glfwTerminate();

    // Encerra o programa com sucesso
    return 0;
}
