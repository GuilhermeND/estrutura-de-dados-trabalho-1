#include "livros.h"

typedef struct _no
{
    int matricula;
    struct _no *proximo;
    struct _no *anterior;
}no;

typedef struct _lista_circular
{
    int tamanho;
    no *cabeca;
    no *pe;
}lista_circular;

lista_circular* criarListaFila();

int inserirFila(lista_circular *lista, int matricula);


