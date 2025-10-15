//estrutura da fila

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
filaUsuarios* criarListaFila();

int estaVaziaFila(filaUsuarios *fila);

int inserirFila(filaUsuarios *fila, int matricula);

int removerFila(filaUsuarios *fila);

void imprimirFila(filaUsuarios *fila);