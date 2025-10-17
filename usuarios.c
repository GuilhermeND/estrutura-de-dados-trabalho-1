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
int listaUsuarioEstaVazia(lista_usuario *lista) {
    return (lista->tamanho == 0); // Retorna 1 se estiver vazia e 0 se não estiver
}

// Função para inserir um usuário no final da lista
int inserirUsuario(lista_usuario *lista, char nome[50], int matricula, int cargo) {
    usuario *novoUsuario = (usuario*) malloc(sizeof(usuario)); // Aloca memória para o novo usuário

    if (novoUsuario == NULL) { // Verifica se a alocação teve sucesso
        return 0; // Falha na alocação de memória
    }

    // Preenche os dados do novo usuário
    strcpy(novoUsuario->nome, nome);
    novoUsuario->matricula = matricula;
    novoUsuario->tipo = cargo; // 0 = estudante, 1 = professor
    novoUsuario->proximo = NULL; // O próximo do novo usuário é NULL, pois o atual será o último da lista

    // Verifica se já existe um usuário com a mesma matrícula
    usuario *usuarioRepetido = buscarUsuario(lista, matricula);
    if (usuarioRepetido != NULL) {
        free(novoUsuario); // Libera a memória do novo usuário
        return 0; // Usuário já existe
    }

    // Inicializa os arrays de livros emprestados e datas de devolução como strings vazias
    for (int i = 0; i < 2; i++) {
        novoUsuario->livros_emprestados[i] = NULL; 
        novoUsuario->data_devolucao[i][0] = '\0';
    }

    if (listaUsuarioEstaVazia(lista)) {
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

// Função para buscar um usuário pela matrícula a partir do nome
int buscarMatricula(lista_usuario *lista, char nome[50]) {
    if (listaUsuarioEstaVazia(lista)) {
        return 0; // A lista está vazia, não há usuários para buscar
    }

    usuario *atual = lista->cabeca; // Ponteiro para percorrer a lista

    // Percorre a lista para encontrar o usuário com o nome especificado
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Matricula do usuario '%s': %d\n", nome, atual->matricula); // Imprime a matrícula do usuário
            return 1; // Usuário encontrado
        }
        atual = atual->proximo;
    }

    return 0; // Usuário não encontrado
}

// Função para buscar um usuário pela matrícula
usuario* buscarUsuario(lista_usuario *lista, int matricula) {
    if (listaUsuarioEstaVazia(lista)) {
        return NULL; // A lista está vazia, não há usuários para buscar
    }

    usuario *atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->matricula == matricula) {
            return atual; // Retorna o ponteiro do nó
        }
        atual = atual->proximo;
    }
    return NULL; // Não encontrado
}

// Função para remover um usuário pela matrícula
int removerUsuario(lista_usuario *lista, int matricula) {
    if (listaUsuarioEstaVazia(lista)) {
        return 0; // A lista está vazia, nada para remover
    }

    usuario *atual = lista->cabeca; // Ponteiro para percorrer a lista
    usuario *anterior = NULL; // Ponteiro para o usuário anterior

    // Percorre a lista para encontrar o usuário com a matrícula especificada
    while (atual != NULL && atual->matricula != matricula) {
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

    printf("Usuario '%s' com matricula '%d' removido com sucesso.\n", atual->nome, matricula);
    free(atual); // Libera a memória do usuário removido
    lista->tamanho--; // Decrementa o tamanho da lista
    return 1; // Sucesso
}

// Função para imprimir os livros emprestados por um usuário
void imprimirLivrosEmprestados(lista_usuario *lista, int matricula) {
    if (listaUsuarioEstaVazia(lista)) {
        printf("A lista de usuarios esta vazia.\n");
        return;
    }
    usuario *atual = lista->cabeca; // Ponteiro para percorrer a lista
    // Percorre a lista para encontrar o usuário com a matrícula especificada
    while (atual != NULL && atual->matricula != matricula) {
        atual = atual->proximo;
    }
    // Verifica se o usuário foi encontrado
    if (atual == NULL) {
        printf("Usuario com matricula '%d' nao encontrado.\n", matricula);
        return;
    }
    // Imprime os livros emprestados pelo usuário
    printf("Livros emprestados pelo usuario '%s':\n", atual->nome);
    int livrosEncontrados = 0;

    for (int i = 0; i < 2; i++) {
        // MODIFICAÇÃO 1: Verifica se o ponteiro para o livro não é nulo
        if (atual->livros_emprestados[i] != NULL) {
            // MODIFICAÇÃO 2: Acessa o campo 'titulo' da struct 'livro' apontada
            printf("- %s\n", atual->livros_emprestados[i]->titulo);
            printf("  Data de devolucao: %s\n", atual->data_devolucao[i]);
            livrosEncontrados++;
        }
    }
    if (livrosEncontrados == 0) {
        printf("Nenhum livro emprestado no momento.\n");
    }
}


// Função para imprimir a lista de usuários
void imprimirListaUsuarios(lista_usuario *lista) {
    if (listaUsuarioEstaVazia(lista)) {
        printf("A lista de usuarios esta vazia.\n");
        return;
    }

    usuario *atual = lista->cabeca; // Ponteiro para percorrer a lista

    printf("----- Lista de Usuarios -----\n");
    while (atual != NULL) {
        printf("Nome: %s, Matricula: %d, Tipo: %s\n", 
               atual->nome, 
               atual->matricula, 
               (atual->tipo == 0) ? "Estudante" : "Professor");
        
        // MODIFICAÇÃO 1: Verifica se algum dos ponteiros de livro não é nulo
        if (atual->livros_emprestados[0] != NULL || atual->livros_emprestados[1] != NULL) {
            printf("  Livros emprestados:\n");
            for (int i = 0; i < 2; i++) {
                // MODIFICAÇÃO 2: Verifica cada ponteiro individualmente
                if (atual->livros_emprestados[i] != NULL) {
                    // MODIFICAÇÃO 3: Acessa o título do livro através do ponteiro
                    printf("  - %s (Devolucao: %s)\n", 
                           atual->livros_emprestados[i]->titulo, 
                           atual->data_devolucao[i]);
                }
            }
        } else {
            printf("  Nenhum livro emprestado.\n");
        }
        printf("\n"); // Adiciona um espaço para melhor legibilidade
        atual = atual->proximo;
    }
}

int deletarListaUsuarios(lista_usuario *lista) {
    if (!lista) return 0; // lista nula

    usuario *atual = lista->cabeca;
    while (atual != NULL) {
        usuario *prox = atual->proximo;
        // os ponteiros em livros_emprestados NÃO são liberados aqui
        free(atual);
        atual = prox;
    }

    lista->cabeca = NULL;
    lista->tamanho = 0;
    return 1; // sucesso
}