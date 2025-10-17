# estrutura-de-dados-trabalho-1

# 📚 Sistema de Biblioteca em C

## 🎯 Objetivo Geral
Desenvolver, em grupos, uma aplicação em linguagem **C** que utilize **listas lineares** — sejam estáticas, dinâmicas, encadeadas, circulares, duplas ou com cabeçalho — de forma funcional.  
O foco é o **armazenamento, manipulação e exibição de dados** em um contexto real, integrando teoria e prática.

---

## 🧩 Cenário-Problema
A biblioteca da instituição deseja **informatizar o sistema de controle de empréstimos de livros**.  

O sistema deve permitir que os **usuários (estudantes e professores)** realizem empréstimos, devoluções e entrem em **fila de espera** caso o exemplar esteja emprestado.

📖 Cada livro possui **apenas um exemplar** e pode estar **disponível ou emprestado**.  
👥 Cada usuário pode ter **até dois livros emprestados simultaneamente**.

---

## ⚙️ Funcionalidades Mínimas Obrigatórias

- 📘 **Cadastrar livros** (título, autor, código)  
- 🧍‍♂️ **Cadastrar usuários** (nome, RA ou SIAPE, tipo: estudante ou professor)  
- 🔄 **Realizar empréstimo de livro**
  - Se o livro estiver **disponível** → registrar o empréstimo  
  - Se o livro estiver **emprestado** → adicionar à **fila de espera (lista circular)**  
- 📥 **Registrar devolução de livro**  
- 📚 **Listar livros emprestados por usuário**  
- 👀 **Exibir fila de espera de um livro**

---

## 💻 Como Usar

### 🧱 Executar o programa
Baixe o arquivo **`main.exe`** e utilize o **teclado** para navegar pelas opções do menu.

### 🧰 Compilar o código manualmente
Caso deseje modificar o código-fonte, recompile utilizando o **GCC**:

```bash
gcc main.c lista.c livros.c usuarios.c emprestimos.c escolhas.c -o main
```

Guilherme Gemniczak Da Rocha	GRR20246173
Eduardo Almeida Freitas da Silva Miranda	GRR20235363