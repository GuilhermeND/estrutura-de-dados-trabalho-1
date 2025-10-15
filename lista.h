//estrutura da fila

#include "livros.h"

typedef struct _no
{
    int matricula;
    struct _no *proximo;
    struct _no *anterior;
} no;

typedef struct _lista_fila_circular
{
    int tamanho;
    no *cabeca;
    no *pe;
} fila;

// Protótipos das funções para manipulação da lista circular (fila de espera)
fila* criarListaFila();

int estaVaziaFila(fila *fila);

int inserirFila(fila *fila, int matricula);

int removerFila(fila *fila);

void imprimirFila(fila *fila);