#ifndef LIVROS_H
#define LIVROS_H

typedef struct no 
{
    char titulo[100];
    char editora[50];
    char autor[50];
    int status; // 0 = emprestado, 1 = disponivel
    int cod;
    struct no *proximo;
} livro;

typedef struct list 
{
    livro *cabeca;
    int tamanho;
} lista_livro;

// Protótipos das funções para manipulação da lista de livros
lista_livro* criarListaLivro();
int listaLivroEstaVazia(lista_livro *lista); // Verifica se a lista está vazia (1 = vazia, 0 = não vazia)
int inserirLivro(lista_livro *lista, char titulo[100], char editora[50], char autor[50]); // Insere um livro na lista
int atualizarStatus(livro *livro); // Atualiza o status do livro (disponível ou emprestado)
int removerLivro(lista_livro *lista, int cod); // Remove um livro da lista pelo título
livro* buscarLivroPorTitulo(lista_livro *lista, char titulo[100]); // Busca um livro pelo título, retorna o ponteiro
livro* buscarLivroPorCodigo(lista_livro *lista, int cod); // Busca um livro pelo código, retorna o ponteiro
void imprimirListaInfo(lista_livro *lista); // Imprime as informações de todos os livros na lista
int deletarListaLivros(lista_livro *lista);

#endif // LIVROS_H