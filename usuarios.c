#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

// Funções para manipulação da lista de usuários
// Função para criar uma lista de usuários
lista_usuario* criarListaUsuario() { 
    lista_usuario *lista = (lista_usuario*) malloc(sizeof(lista_usuario)); // Aloca memória para a lista

    if (lista != NULL) { // Verifica se a alocação teve sucesso
        lista->cabeca = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

// Função para verificar se a lista está vazia
int estaVazia(lista_usuario *lista) {
    return (lista->tamanho == 0); // Retorna 1 se estiver vazia e 0 se não estiver
}

// Função para inserir um usuário no final da lista
int inserirFim(lista_usuario *lista, char nome[50], int matricula, int cargo) {
    usuario *novoUsuario = (usuario*) malloc(sizeof(usuario)); // Aloca memória para o novo usuário

    if (novoUsuario == NULL) { // Verifica se a alocação teve sucesso
        return 0; // Falha na alocação de memória
    }

    // Preenche os dados do novo usuário
    strcpy(novoUsuario->nome, nome);
    strcpy(novoUsuario->matricula, matricula);
    novoUsuario->tipo = cargo; // 0 = estudante, 1 = professor
    novoUsuario->proximo = NULL; // O próximo do novo usuário é NULL, pois o atual será o último da lista

    if (estaVazia(lista)) {
        lista->cabeca = novoUsuario; // Se a lista estiver vazia, o novo usuário é a cabeça
    } else {
        usuario *atual = lista->cabeca; // Começa a percorrer a lista a partir da cabeça
        while (atual->proximo != NULL) {
            atual = atual->proximo; // Percorre até o final da lista
        }
        atual->proximo = novoUsuario; // Adiciona o novo usuário no final
    }
    lista->tamanho++; // Incrementa o tamanho da lista
    return 1; // Sucesso
}

// Função para buscar um usuário pelo nome
int buscarUsuario(lista_usuario *lista, char nome[50]) {
    if (estaVazia(lista)) {
        return 0; // A lista está vazia, não há usuários para buscar
    }

    usuario *atual = lista->cabeca; // Ponteiro para percorrer a lista

    // Percorre a lista para encontrar o usuário com o nome especificado
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return 1; // Usuário encontrado
        }
        atual = atual->proximo;
    }

    return 0; // Usuário não encontrado
}

// Função para buscar um usuário pela matrícula
int buscarMatricula(lista_usuario *lista, char nome[50]) {
    if (estaVazia(lista)) {
        return 0; // A lista está vazia, não há usuários para buscar
    }

    usuario *atual = lista->cabeca; // Ponteiro para percorrer a lista

    // Percorre a lista para encontrar o usuário com o nome especificado
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual->matricula; // Retorna a matrícula do usuário encontrado
        }
        atual = atual->proximo;
    }

    return 0; // Usuário não encontrado
}

int removerUsuario(lista_usuario *lista, char nome[50]) {
    if (estaVazia(lista)) {
        return 0; // A lista está vazia, nada para remover
    }

    usuario *atual = lista->cabeca; // Ponteiro para percorrer a lista
    usuario *anterior = NULL; // Ponteiro para o usuário anterior

    // Percorre a lista para encontrar o usuário com o nome especificado
    while (atual != NULL && strcmp(atual->nome, nome) != 0) { 
        anterior = atual; 
        atual = atual->proximo; 
    }

    if (atual == NULL) {
        return 0; // Usuário não encontrado
    }

    // Remove o usuário da lista
    if (anterior == NULL) {
        // O usuário a ser removido é a cabeça da lista
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual); // Libera a memória do usuário removido
    lista->tamanho--; // Decrementa o tamanho da lista
    return 1; // Sucesso
}