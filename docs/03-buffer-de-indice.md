# 🧩 Entendendo o EBO (Element Buffer Object) no OpenGL

O **EBO (Element Buffer Object)** é um buffer usado para armazenar **índices** que dizem à GPU **quais vértices** devem ser desenhados e **em que ordem**.  
Isso evita duplicar vértices e torna o desenho de formas complexas muito mais eficiente.

---

## 🎯 Exemplo Prático

```cpp
GLfloat vertices[] = {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Inferior esquerdo
     0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Inferior direito
     0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Superior

    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inferior esquerdo (menor)
     0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inferior direito (menor)
     0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f  // Superior (menor)
};

GLuint indices[] = {
    0, 3, 5, // Triângulo inferior esquerdo
    3, 2, 4, // Triângulo inferior direito
    5, 4, 1  // Triângulo superior
};
```

---

## 🧱 Estrutura do EBO no código

```cpp
GLuint EBO;
glGenBuffers(1, &EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

- `glGenBuffers` → cria um identificador para o EBO  
- `glBindBuffer` → associa esse EBO ao contexto atual  
- `glBufferData` → envia os dados (índices) para a GPU

---

## 🎨 Ligando tudo (VAO + VBO + EBO)

```cpp
glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

O OpenGL vai entender que:
- Os **vértices** estão no `VBO`
- A **ordem** em que eles devem ser desenhados está no `EBO`
- E tudo está organizado dentro do `VAO`

---

## 🧩 Conclusão

| Conceito | Função | Descrição |
|-----------|---------|-----------|
| **VAO** | Vertex Array Object | Agrupa a configuração dos buffers |
| **VBO** | Vertex Buffer Object | Guarda os vértices (posições, cores, etc.) |
| **EBO** | Element Buffer Object | Guarda os índices (ordem dos vértices) |

✅ Usar **EBO** economiza memória e evita repetir vértices.  
✅ Sempre **confira as vírgulas** — um pequeno erro pode quebrar todo o buffer.

---

**Referência:**  
📘 [LearnOpenGL - Hello Triangle (Element Buffer)](https://learnopengl.com/Getting-started/Hello-Triangle)
