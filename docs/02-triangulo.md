# 🧱 Triângulo em OpenGL (GLFW + GLAD)

1. Inclui as bibliotecas necessárias
```cpp
#include <iostream>        // Biblioteca padrão para entrada e saída (ex: cout)
#include <glad/glad.h>     // Carrega todas as funções modernas do OpenGL
#include <GLFW/glfw3.h>    // Gerencia janelas e contexto do OpenGL
```

2. Código-fonte do Vertex Shader
```cpp
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
```

3. Código-fonte do Fragment Shader
```cpp
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";
```

4. Inicializa a biblioteca GLFW
```cpp
glfwInit();
```

5. Define a versão do OpenGL que será usada (3.3)
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
```

6. Define o perfil do OpenGL como "CORE" (apenas funções modernas)
```cpp
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

7. Define os vértices do triângulo (posição XYZ)
```cpp
GLfloat vertices[] = {
     -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
      0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 
      0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f  
};
```

8. Cria uma janela 800x800 chamada "YoutubeOpenGL"
```cpp
GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
```

9. Verifica se a janela foi criada corretamente
```cpp
if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
```

10. Define a janela criada como o contexto atual
```cpp
glfwMakeContextCurrent(window);
```

11. Carrega todas as funções OpenGL com o GLAD
```cpp
gladLoadGL();
```

12. Define a área de renderização (de 0,0 até 800,800)
```cpp
glViewport(0, 0, 800, 800);
```


13. Cria e compila o Vertex Shader
```cpp
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

14. Cria e compila o Fragment Shader
```cpp
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

15. Cria e linka o programa de shader
```cpp
GLuint shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
```


16. Deleta os shaders após o link
```cpp
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

17. Cria o VAO e o VBO
```cpp
GLuint VAO, VBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
```

18. Configura o VAO e o VBO
```cpp
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
```

19. Define a cor de fundo (RGBA)
```cpp
glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
```

20. Limpa o buffer de cor
```cpp
glClear(GL_COLOR_BUFFER_BIT);
```

21. Loop principal — mantém a janela aberta até o usuário fechá-la
```cpp
while (!glfwWindowShouldClose(window))
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
}
```

22. Deleta buffers e programa de shader
```cpp
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteProgram(shaderProgram);
```

23. Destroi a janela e libera memória
```cpp
glfwDestroyWindow(window);
```

24. Finaliza a biblioteca GLFW
```cpp
glfwTerminate();
```

25. Encerra o programa com sucesso
```cpp
return 0;
```
