#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livros.h"

// Funções para manipulação da lista de livros
// Função para criar uma lista de livros
lista_livro* criarLista() {
    lista_livro *lista = (lista_livro*) malloc(sizeof(lista_livro)); // Aloca memória para a lista

    if (lista != NULL) { // Verifica se a alocação teve sucesso
        lista->cabeca = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

// Função para verificar se a lista está vazia
int estaVazia(lista_livro *lista) {
    return (lista->tamanho == 0); // Retorna 1 se estiver vazia e 0 se não estiver
}

// Função para inserir um livro no final da lista
int inserirFinal(lista_livro *lista, char titulo[100], char editora[50], char autor[50]) {
    livro *novoLivro = (livro*) malloc(sizeof(livro)); // Aloca memória para o novo livro

    if (novoLivro == NULL) { // Verifica se a alocação teve sucesso
        return 0; // Falha na alocação de memória
    }

    // Preenche os dados do novo livro
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->editora, editora);
    strcpy (novoLivro->autor, autor);
    novoLivro->status = 1; // Um livro novo sempre está disponível
    novoLivro->isbn = lista->tamanho + 1; // Atribui um ISBN sequencial
    novoLivro->proximo = NULL; // O próximo do novo livro é NULL, pois o atual será o último da lista

    if (estaVazia(lista)) {
        lista->cabeca = novoLivro; // Se a lista estiver vazia, o novo livro é a cabeça
    } else {
        livro *atual = lista->cabeca; // Começa a percorrer a lista a partir da cabeça
        while (atual->proximo != NULL) {
            atual = atual->proximo; // Percorre até o final da lista
        }
        atual->proximo = novoLivro; // Adiciona o novo livro no final
    }
    lista->tamanho++;
    return 1; // Sucesso
}

// Função para atualizar o status de um livro (disponível ou emprestado)
int atualizarStatus(livro *livro){
    if (livro->status == 1) {
        livro->status = 0; // Muda para emprestado
    } else {
        livro->status = 1; // Muda para disponível
    }
    return 1; // Sucesso
}

// Função para remover um livro da lista pelo título
int removerLivro(lista_livro *lista, char titulo[100]) {
    if (estaVazia(lista)) {
        return 0; // A lista está vazia, nada para remover
    }

    livro *atual = lista->cabeca; // Ponteiro para percorrer a lista
    livro *anterior = NULL; // Ponteiro para o livro anterior

    // Percorre a lista para encontrar o livro com o título especificado
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) { 
        anterior = atual; 
        atual = atual->proximo; 
    }

    if (atual == NULL) {
        return 0; // Livro não encontrado
    }

    // Remove o livro da lista
    if (anterior == NULL) {
        // O livro a ser removido é a cabeça da lista
        lista->cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual); // Libera a memória do livro removido
    lista->tamanho--; // Decrementa o tamanho da lista
    return 1; // Sucesso
}

// Função para imprimir as informações de um livro pelo título
void imprimirLivroInfo(lista_livro *lista, char titulo[100]) {
    if (estaVazia(lista)) {
        printf("A lista de livros está vazia.\n");
        return;
    }

    livro *atual = lista->cabeca; // Ponteiro para percorrer a lista

    // Percorre a lista para encontrar o livro com o título especificado
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Livro com título '%s' não encontrado.\n", titulo);
        return;
    }

    // Imprime as informações do livro encontrado
    printf("Título: %s\n", atual->titulo);
    printf("Editora: %s\n", atual->editora);
    printf("Autor: %s\n", atual->autor);
    printf("Status: %s\n", (atual->status == 1) ? "Disponível" : "Emprestado");
    printf("ISBN: %d\n", atual->isbn);
}

// Função para buscar o ISBN de um livro pelo título
int buscarISBN(lista_livro *lista, char titulo[100]) {
    if (estaVazia(lista)) {
        return -1; // A lista está vazia, não há ISBN para retornar
    }

    livro *atual = lista->cabeca; // Ponteiro para percorrer a lista

    // Percorre a lista para encontrar o livro com o título especificado
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            return atual->isbn; // Retorna o ISBN do livro encontrado
        }
        atual = atual->proximo;
    }

    return -1; // Livro não encontrado
}

// Função para imprimir as informações de todos os livros na lista
void imprimirListaInfo(lista_livro *lista) {
    if (estaVazia(lista)) {
        printf("A lista de livros está vazia.\n");
        return;
    }

    livro *atual = lista->cabeca; // Ponteiro para percorrer a lista

    // Percorre a lista e imprime as informações de cada livro
    while (atual != NULL) {
        printf("Título: %s\n", atual->titulo);
        printf("Editora: %s\n", atual->editora);
        printf("Autor: %s\n", atual->autor);
        printf("Status: %s\n", (atual->status == 1) ? "Disponível" : "Emprestado");
        printf("ISBN: %d\n", atual->isbn);
        printf("-------------------------\n");
        atual = atual->proximo;
    }
}