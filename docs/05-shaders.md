# Fluxo completo: do vetor até a GPU.

---

## 1) Vetor de vértices em C++ (posição XYZ + cor RGB)
```cpp
// 6 floats por vértice: [X, Y, Z, R, G, B]
GLfloat vertices[] = {
    -0.50f, -0.5f * float(sqrt(3)) / 3, 0.0f,   0.0f, 1.0f, 0.0f,  // Inferior esquerdo
     0.50f, -0.5f * float(sqrt(3)) / 3, 0.0f,   1.0f, 0.0f, 0.0f,  // Inferior direito
     0.00f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.0f, 0.0f, 1.0f,  // Superior
    -0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f, 1.0f, 0.0f, 0.0f,  // Meio esquerdo
     0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f, 0.0f, 1.0f, 0.0f,  // Meio direito
     0.00f, -0.5f * float(sqrt(3)) / 3,     0.0f, 0.0f, 0.0f, 1.0f   // Meio Inferior
};

GLuint indices[] = {
    0, 1, 2,   // triângulo superior
    3, 4, 5,   // triângulo inferior
    0, 3, 5    // exemplo extra (dependendo do seu desenho)
};
```

Percebe que cada vértice ocupa 6 floats — por isso o *stride* será 6 * sizeof(float).

---

## 2) Criação de VBO, EBO e VAO (envio para GPU)
```cpp
// gera e preenche buffers (exemplo conceitual)
VBO VBO1(vertices, sizeof(vertices));     // carrega o array 'vertices' para um Vertex Buffer Object
EBO EBO1(indices, sizeof(indices));       // carrega os indices para Element Buffer Object
VAO VAO1;
VAO1.Bind();
VBO1.Bind();
EBO1.Bind();
``` 

Explicação curta:
- **VBO** armazena os dados dos vértices (posição+cor) na memória da GPU.
- **EBO** armazena os índices que definem quais vértices formam cada triângulo.
- **VAO** armazena o estado dos atributos (como interpretar os dados do VBO) — quando você bindar o VAO depois, ele restaura esse estado.

---

## 3) Linkagem dos atributos (posição e cor) no VAO
```cpp
// Cada vértice tem 6 floats: 3 para posição, 3 para cor
VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);                // layout 0 -> aPos (X,Y,Z)
VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // layout 1 -> aColor (R,G,B)
``` 

O que cada parâmetro significa:
- `layout` — corresponde ao `layout(location = N)` no vertex shader.
- `numComponents` — quantos componentes por atributo (3 para vec3).
- `type` — tipo dos dados (GL_FLOAT).
- `stride` — distância em bytes entre o começo de um vértice e o próximo (6 * sizeof(float)).
- `offset` — deslocamento em bytes do início do vértice até esse atributo (posição: 0; cor: 3 * sizeof(float)).

Internamente o VAO faz algo como:
```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
``` 

Se isso não bater com o que tu fez no seu VAO class, dá uma olhada se `LinkAttrib` realmente passa o stride/offset para `glVertexAttribPointer`.

---

## 4) Vertex Shader — recebendo posição e cor
```glsl
#version 330 core
layout (location = 0) in vec3 aPos;    // conectado ao layout 0 (posição)
layout (location = 1) in vec3 aColor;  // conectado ao layout 1 (cor)
out vec3 color;
uniform float scale;

void main()
{
   // exemplo de uso do uniforme scale para escalonamento
   gl_Position = vec4(aPos.x + aPos.x * scale,
                      aPos.y + aPos.y * scale,
                      aPos.z + aPos.z * scale, 1.0);
   color = aColor; // passa para o fragment shader (interpolação acontece automaticamente)
}
```

Notas:
- `aPos` e `aColor` são preenchidos automaticamente pela GPU usando o VBO + VAO configurados.
- O `color` é declarado como `out`, então será interpolado e passado para o fragment shader.

---

## 5) Fragment Shader — pintando pixels
```glsl
#version 330 core
in vec3 color;       // recebido do vertex shader (já interpolado)
out vec4 FragColor;

void main()
{
   FragColor = vec4(color, 1.0); // usa a cor interpolada por vértice
}
```

Antes você tinha uma cor fixa no frag: `FragColor = vec4(0.8f,0.3f,0.02f,1.0f);` — agora cada pixel é calculado a partir da interpolação dos `aColor` dos vértices.

---

## 6) Uniform 'scale' — comunicação CPU → GPU
```cpp
// pegar o location do uniforme e enviar valor
GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
shaderProgram.Activate();
glUniform1f(uniID, 0.5f); // por exemplo, reduz para metade (ou ajusta dinamicamente)
``` 

Fluxo:
1. CPU chama `glGetUniformLocation` para obter o índice do uniforme no programa.
2. CPU chama `glUniform1f` para enviar o float para a GPU.
3. Na próxima vez que o vertex shader rodar, ele lerá `scale` com o valor enviado.

Ou seja: **dados estáticos (vértices/cores)** vão via VBO; **parâmetros dinâmicos** (ex.: escala, tempo, cor global) vão via **uniforms**.

---

## 7) Desenhando (draw call)
```cpp
VAO1.Bind();
shaderProgram.Activate();
glUniform1f(uniID, currentScale); // atualiza antes do draw, se quiser animar
glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // EBO define os índices
``` 

Pontos-chave:
- O *draw call* aciona o pipeline: o GPU lê o VBO conforme descrito pelo VAO, executa o vertex shader para cada vértice, rasteriza triângulos, e executa o fragment shader para cada pixel.
- A interpolação de `color` entre vértices é feita automaticamente pelo rasterizador antes do fragment shader.

---

## 8) Resumo do fluxo (passo a passo)
1. CPU monta `vertices[]` (XYZ + RGB) e `indices[]`.
2. CPU cria VBO e EBO e copia esses arrays para a memória da GPU.
3. CPU configura o VAO com `glVertexAttribPointer` (stride/offset) e habilita atributos.
4. CPU ativa o shader program.
5. CPU envia uniformes (ex.: `scale`) com `glUniform*`.
6. CPU faz `glDrawElements` → GPU executa vertex shader, rasterização, fragment shader.
7. Fragment shader usa `color` interpolado para cada pixel e escreve `FragColor`.

---

## Demonstração:

- Definindo cores para cada vertices:
    ![](./images/05/triangulo%20com%20shader.png)
- Definindo escala para o objeto:
    ![](./images/05/triangulo%20com%20scale.png)
---

