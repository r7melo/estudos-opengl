#include <iostream>        // Biblioteca padrão para entrada e saída (ex: cout)
#include <glad/glad.h>     // Carrega todas as funções modernas do OpenGL
#include <GLFW/glfw3.h>    // Gerencia janelas e contexto do OpenGL
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


const unsigned int WIDTH = 800;  // Largura da janela
const unsigned int HEIGHT = 800; // Altura da janela



// Pirâmide

GLfloat vertices[] =
{//|     Coordenadas  |       Cores       | Textura Coord. 
    -0.5f,  0.0f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   
    -0.5f,  0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   5.0f, 0.0f,  
     0.5f,  0.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     0.5f,  0.0f,  0.5f,   0.0f, 0.0f, 1.0f,   5.0f, 0.0f,
     0.0f,  0.8f,  0.0f,   1.0f, 1.0f, 1.0f,   2.5f, 5.0f,
};

GLuint indices[] = {
    0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Estudos OpenGL", NULL, NULL);

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
    glViewport(0, 0, WIDTH, HEIGHT);







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


	Texture popCat("C:\\Users\\Romario Melo\\Documents\\estudos-opengl\\docs\\images\\07\\brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);


	float rotation = 0.0f; // Variável para armazenar o ângulo de rotação
	double prevTime = glfwGetTime();  // Tempo do frame anterior  

	glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade

    // Loop principal — mantém a janela aberta até o usuário fechá-la
    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Define a cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o buffer de profundidade
		
		shaderProgram.Activate(); // Ativa o programa de shader

		// Atualiza a rotação com base no tempo decorrido
		double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1/60) {
            rotation += 0.5f;
            prevTime = crntTime;
		}


		// Cria transformações (OBS: Sempre após a ativação do Programa de Shaders)
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);



		// Rotaciona o modelo ao redor do eixo Y
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		// Translada a câmera para trás (no eixo Z)
		view = glm::translate(view, glm::vec3(0.0f, 0.5f, -2.0f));
		// Define a projeção perspectiva
		proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		// Passa as matrizes para os uniformes do shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(model)); 
        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(model));



		glUniform1f(uniID, 1.0f); // Define o valor do uniforme "scale" para 0.5

		// Ativa a textura
		popCat.Bind();
		
		VAO1.Bind(); // Vincula o VAO (prepara os dados para serem desenhados)

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); // Desenha o triângulo


        // Troca o buffer de fundo com o buffer visível (mostra o resultado na tela)
        glfwSwapBuffers(window);

        // Processa eventos (como teclado, mouse, etc.)
        glfwPollEvents();
    }

	// Deleta os objetos criados
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
