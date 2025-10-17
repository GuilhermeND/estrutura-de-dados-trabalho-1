#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Funções para manipulação da lista circular (fila de espera)
// Função para criar uma lista circular
filaUsuarios* criarListaFilaUsuarios() {
    filaUsuarios *f = (filaUsuarios*) malloc(sizeof(filaUsuarios)); // Aloca memória para a lista

    if (f!= NULL) { // Verifica se a alocação teve sucesso
        f->cabeca = NULL;
        f->pe = NULL;
        f->tamanho = 0;
    }
    return f;
}

// Função para verificar se a fila de espera está vazia
int FilaEstaVazia(filaUsuarios *lista) {
    if (lista == NULL) {
        return 1; // A lista não foi inicializada, considera-se vazia
    }
    return (lista->tamanho == 0); // Retorna 1 se estiver vazia e 0 se não estiver
}

// Função para inserir um usuário na fila (lista circular) pelo número de matrícula
int inserirFila(filaUsuarios *lista, int matricula) {
    fila_no *novoNo = (fila_no*) malloc(sizeof(fila_no)); // Aloca memória para o novo nó

    if (novoNo == NULL) { // Verifica se a alocação teve sucesso
        return 0; // Falha na alocação de memória
    }

    // Preenche os dados do novo nó
    novoNo->matricula = matricula;

    if (FilaEstaVazia(lista)) {
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
int removerFila(filaUsuarios *lista) {
    if (FilaEstaVazia(lista)) {
        return 0; // A lista está vazia, não há nós para remover
    }

    fila_no *noRemovido = lista->cabeca; // Nó a ser removido é a cabeça da lista

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
void imprimirFila(filaUsuarios *lista) {
    if (lista == NULL) {
        printf("Erro: A estrutura da fila nao foi inicializada.\n");
        return;
    }

    if (FilaEstaVazia(lista)) {
        printf("Erro: A fila esta vazia.\n");
        return;
    }

    fila_no *atual = lista->cabeca; // Ponteiro para percorrer a lista
    do {
        printf(" %d, ", atual->matricula);
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    printf("\n");
}