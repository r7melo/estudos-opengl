
# 🧱 Janela OpenGL com GLFW e GLAD

### 1. Inclui as bibliotecas necessárias
```cpp
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
```

---

### 2. Inicializa a biblioteca GLFW
```cpp
glfwInit();
```

---

### 3. Define a versão do OpenGL (3.3)
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
```

---

### 4. Define o perfil como "CORE" (apenas funções modernas)
```cpp
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

---

### 5. Cria uma janela 800x800 chamada "YoutubeOpenGL"
```cpp
GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
```

---

### 6. Verifica se a janela foi criada corretamente
```cpp
if (window == NULL)
{
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
}
```

---

### 7. Define a janela criada como o contexto atual
```cpp
glfwMakeContextCurrent(window);
```

---

### 8. Carrega as funções do OpenGL com GLAD
```cpp
gladLoadGL();
```

---

### 9. Define a área de renderização (viewport)
```cpp
glViewport(0, 0, 800, 800);
```

---

### 10. Define a cor de fundo (RGBA)
```cpp
glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
```

---

### 11. Limpa o buffer de cor com a cor definida
```cpp
glClear(GL_COLOR_BUFFER_BIT);
```

---

### 12. Troca o buffer de fundo pelo visível (mostra na tela)
```cpp
glfwSwapBuffers(window);
```

---

### 13. Mantém a janela aberta até o usuário fechar
```cpp
while (!glfwWindowShouldClose(window))
{
    glfwPollEvents();
}
```

---

### 14. Destroi a janela e libera recursos
```cpp
glfwDestroyWindow(window);
```

---

### 15. Finaliza a biblioteca GLFW antes de encerrar
```cpp
glfwTerminate();
```

---

### 16. Encerra o programa com sucesso
```cpp
return 0;
```
