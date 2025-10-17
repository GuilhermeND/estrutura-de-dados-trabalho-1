#ifndef USUARIOS_H
#define USUARIOS_H
#include "livros.h"

typedef struct user
{
    char nome[50];
    int matricula; // GRR
    int tipo; // 0 = estudante 1 = professor
    livro *livros_emprestados[2]; // armazena o ponteiro dos livros emprestados
    char data_devolucao[2][11]; // armazena a data de devolução dos livros
    struct user *proximo;
} usuario;

typedef struct list_user
{
    usuario *cabeca;
    int tamanho;
} lista_usuario;

// Protótipos das funções para manipulação da lista de usuários
lista_usuario* criarListaUsuario();
int listaUsuarioEstaVazia(lista_usuario *lista); // Verifica se a lista está vazia (1 = vazia, 0 = não vazia)
int inserirUsuario(lista_usuario *lista, char nome[50], int matricula, int cargo); // Insere um usuário na lista 
int buscarMatricula(lista_usuario *lista, char nome[50]); // busca a matricula do usuário pelo nome para imprimir
usuario* buscarUsuario(lista_usuario *lista, int matricula); // busca o ponteiro do usuário pela matrícula
int removerUsuario(lista_usuario *lista, int matricula); // Remove um usuário da lista pela matrícula
void imprimirLivrosEmprestados(lista_usuario *lista, int matricula); // Imprime os livros emprestados de um usuário pela matrícula
void imprimirListaUsuarios(lista_usuario *lista); // Imprime a lista de usuários

#endif // USUARIOS_H