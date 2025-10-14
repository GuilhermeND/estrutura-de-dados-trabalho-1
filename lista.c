#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Funções para manipulação da lista circular (fila de espera)
// Função para criar uma lista circular
lista_circular* criarListaFila() {
    lista_circular *lista = (lista_circular*) malloc(sizeof(lista_circular)); // Aloca memória para a lista

    if (lista != NULL) { // Verifica se a alocação teve sucesso
        lista->cabeca = NULL;
        lista->pe = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

// Função para verificar se a fila de espera está vazia
int estaVaziaFila(lista_circular *lista) {
    return (lista->tamanho == 0); // Retorna 1 se estiver vazia e 0 se não estiver
}

// Função para inserir um usuário na fila (lista circular) pelo número de matrícula
int inserirFila(lista_circular *lista, int matricula) {
    no *novoNo = (no*) malloc(sizeof(no)); // Aloca memória para o novo nó

    if (novoNo == NULL) { // Verifica se a alocação teve sucesso
        return 0; // Falha na alocação de memória
    }

    // Preenche os dados do novo nó
    novoNo->matricula = matricula;

    if (estaVaziaFila(lista)) {
        lista->cabeca = novoNo; // Se a lista estiver vazia, o novo nó é a cabeça
        lista->pe = novoNo; // O ponteiro pe também aponta para o novo nó
        novoNo->proximo = novoNo; // Aponta para si mesmo, formando um círculo
        novoNo->anterior = novoNo; // Aponta para si mesmo, formando um círculo
    } else {
        // Insere o novo nó no final da lista circular
        novoNo->anterior = lista->pe; // O anterior do novo nó é o último nó atual
        novoNo->proximo = lista->cabeca; // O próximo do novo nó é a cabeça da lista
        lista->pe->proximo = novoNo; // O próximo do último nó atual aponta para o novo nó
        lista->cabeca->anterior = novoNo; // O anterior da cabeça aponta para o novo nó
        lista->pe = novoNo; // Atualiza o ponteiro pe para o novo nó
    }
    lista->tamanho++; // Incrementa o tamanho da lista
    return 1; // Sucesso
}

// Função para remover o usuário no início da fila
int removerFila(lista_circular *lista) {
    if (estaVaziaFila(lista)) {
        return 0; // A lista está vazia, não há nós para remover
    }

    no *noRemovido = lista->cabeca; // Nó a ser removido é a cabeça da lista

    if (lista->tamanho == 1) {
        // Se houver apenas um nó na lista, a lista ficará vazia após a remoção
        lista->cabeca = NULL;
        lista->pe = NULL;
    } else { // Se houver mais de um nó na lista
        // Atualiza os ponteiros para remover o nó da lista circular
        lista->cabeca = noRemovido->proximo; // A nova cabeça é o próximo nó
        lista->pe->proximo = lista->cabeca; // O próximo do último nó aponta para a nova cabeça
        lista->cabeca->anterior = lista->pe; // O anterior da nova cabeça aponta para o último nó
    }

    free(noRemovido); // Libera a memória do nó removido
    lista->tamanho--; // Decrementa o tamanho da lista
    return 1; // Sucesso
}

// Função para imprimir a fila
void imprimirFila(lista_circular *lista) {
    if (estaVaziaFila(lista)) {
        printf("A fila está vazia.\n");
        return;
    }

    no *atual = lista->cabeca; // Ponteiro para percorrer a lista
    printf("Fila: ");
    do {
        printf("%d, ", atual->matricula);
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    printf("\n");
}