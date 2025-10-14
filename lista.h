//estrutura da fila

#include "livros.h"

typedef struct _no
{
    int matricula;
    struct _no *proximo;
    struct _no *anterior;
} no;

typedef struct _lista_circular
{
    int tamanho;
    no *cabeca;
    no *pe;
} lista_circular;

// Protótipos das funções para manipulação da lista circular (fila de espera)
lista_circular* criarListaFila();

int estaVaziaFila(lista_circular *lista);

int inserirFila(lista_circular *lista, int matricula);

int removerFila(lista_circular *lista);

void imprimirFila(lista_circular *lista);