# Refatoração OpenGL: Organização em Classes

Este commit reorganiza o projeto de OpenGL criando classes para cada componente principal, melhorando a modularidade e clareza do código.

---

## Classes Criadas

| Classe  | Função |
|---------|--------|
| `VBO`   | Gerencia o Vertex Buffer Object (buffer de vértices). Métodos: `Bind`, `Unbind`, `Delete`. |
| `EBO`   | Gerencia o Element Buffer Object (buffer de índices). Métodos: `Bind`, `Unbind`, `Delete`. |
| `VAO`   | Gerencia o Vertex Array Object, que agrupa VBOs. Métodos: `LinkVBO`, `Bind`, `Unbind`, `Delete`. |
| `Shader`| Gerencia Shader Program. Lê arquivos `.vert` e `.frag`, compila, linka e ativa shaders. |

---

## Mudanças nos Shaders

- Shaders separados em arquivos externos (`default.vert` e `default.frag`).
- Classe `Shader` responsável por carregar, compilar e linkar shaders.

---

## Main.cpp

- Instancia objetos das classes (`VAO`, `VBO`, `EBO`, `Shader`).
- Linka VBOs aos VAOs com `LinkVBO`.
- Substituição do código repetitivo por chamadas de métodos (`Bind`, `Activate`, `DrawElements`).

---

## Benefícios da Organização

1. **Modularidade**: cada classe gerencia apenas seu componente.
2. **Reutilização**: fácil criar novos objetos sem duplicar código.
3. **Código mais limpo**: `Main.cpp` concentra apenas lógica de renderização e criação de objetos.
4. **Manutenção facilitada**: alterações em shaders ou buffers isoladas em suas classes.

---

