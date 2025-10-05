#include <iostream>        // Biblioteca padr�o para entrada e sa�da (ex: cout)
#include <glad/glad.h>     // Carrega todas as fun��es modernas do OpenGL
#include <GLFW/glfw3.h>    // Gerencia janelas e contexto do OpenGL

int main() {
    // Inicializa a biblioteca GLFW
    glfwInit();

    // Define a vers�o do OpenGL que ser� usada (3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Define o perfil do OpenGL como "CORE" (apenas fun��es modernas)
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

    // Carrega todas as fun��es OpenGL com o GLAD
    gladLoadGL();

    // Define a �rea de renderiza��o (de 0,0 at� 800,800)
    glViewport(0, 0, 800, 800);

    // Define a cor de fundo (RGBA: azul escuro)
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    // Limpa o buffer de cor aplicando a cor definida
    glClear(GL_COLOR_BUFFER_BIT);

    // Troca o buffer de fundo com o buffer vis�vel (mostra o resultado na tela)
    glfwSwapBuffers(window);

    // Loop principal � mant�m a janela aberta at� o usu�rio fech�-la
    while (!glfwWindowShouldClose(window))
    {
        // Processa eventos (como teclado, mouse, etc.)
        glfwPollEvents();
    }

    // Destroi a janela e libera mem�ria
    glfwDestroyWindow(window);

    // Finaliza a biblioteca GLFW
    glfwTerminate();

    // Encerra o programa com sucesso
    return 0;
}
