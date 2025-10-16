#ifndef LISTA_H
#define LISTA_H

#include "livros.h"

typedef struct _no
{
    int matricula;
    struct _no *proximo;
    struct _no *anterior;
} fila_no;

typedef struct _lista_fila_circular
{
    int tamanho;
    fila_no *cabeca;
    fila_no *pe;
} filaUsuarios;

// Protótipos das funções para manipulação da lista circular (fila de espera)
filaUsuarios* criarListaFilaUsuarios();
int estaVaziaFila(filaUsuarios *fila); // Verifica se a fila está vazia (1 = vazia, 0 = não vazia)
int inserirFila(filaUsuarios *fila, int matricula); // Insere um usuário na fila
int removerFila(filaUsuarios *fila); // Remove o usuário no início da fila
void imprimirFila(filaUsuarios *fila); // Imprime os usuários na fila

#endif // LISTA_H