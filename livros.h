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
int atualizarStatus(livro *livro); // Atualiza o status do livro (0 = emprestado, 1 = disponivel)
int removerLivro(lista_livro *lista, char titulo[100]); // Remove um livro da lista pelo título
void imprimirLivroInfo(lista_livro *lista, char titulo[100]); // Imprime as informações de um livro pelo título
int buscarCodigo(lista_livro *lista, char titulo[100]); // Busca o código de um livro pelo título
void imprimirListaInfo(lista_livro *lista); // Imprime as informações de todos os livros na lista
void imprimirStatus(lista_livro *lista, char titulo[100]); // Imprime o status (disponível/emprestado) de um livro pelo título

#endif // LIVROS_H