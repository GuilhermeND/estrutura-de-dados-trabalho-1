//as funcoes ainda estao imcompletas, falta algumas dependencias ainda!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimos.h"
#include "usuarios.h"
#include "livros.h"
#include "lista.h"


//cria a lista controladora de filas (1 por programa)
listaFilas *criarListaFilas(){
    listaFilas *lista = (listaFilas*) malloc(sizeof(listaFilas));
    if(lista) return lista;
    else{
        printf("Erro ao alocar memória da Lista controladora");
        return NULL;
    }
}

//adiciona uma fila para a lista controladora

int adicionarListaFilas();

//remove uma fila da lista controladora

int removerListaFilas();

//deleta a controladora no fim da execucao do programa

int deletarListaFilas();



//função para verificar se existe a fila para aquele livro
int veriFila(listaFilas *lista, livro *livrop){
    int i;
    fila *localNo = lista->filaCabeca;
    for(i=0; i<lista->tamanho; i++){
        if(localNo->livro == livrop){
            return localNo;
        }
        localNo = localNo->proximo;
    }
    return NULL;
}



//função para colocar em uma fila quando ocorre um emprestimo, lida com casos de livro já emprestado ou nao e se a fila ainda existe ou n
int colocaFila(int matricula, livro *livrop, listaFilas *lista){

    if(livrop->status == 1) return 0;
    fila *enderecoFila = veriFila(lista, livrop);
    if(enderecoFila){
        inserirFila(matricula, enderecoFila->fila);
        return 1;
    }else{
        filaUsuarios *novaFila = criarListaFilaUsuarios();
        inserirFila(matricula, novaFila);
        return novaFila->tamanho;
    }
}

//funcao que efetiviamente faz o emprestimo

int fazerEmprestimo(listaFilas *lista, lista_livro *listaLivro, int isbnLivro, int matricula){
    int i;
    livro *localNo = listaLivro->cabeca;
    for(i=0; i<lista->tamanho; i++){
        if(localNo->cod == isbnLivro){
           int veri = colocaFila(matricula, localNo, lista);
            if(!veri){
                localNo->status = 0;
                return veri;
            }else return veri;
        }
        localNo = localNo->proximo;
    }
    return NULL;
}

//funcao de devolucao de livro, lida com o caso de precisar deletar a lista se so existe uma pessoa esperando e caso ha mais de uma pessoa na fila.

int devolverLivro(listaFilas *lista, lista_livro *listaLivro ,int isbnLivro, int matricula){
    int i;
    fila *filaEndereco;
    filaUsuarios* fila;
    livro *localNo = listaLivro->cabeca;
    fila_no *temp;
    for(i=0; i<listaLivro->tamanho; i++){
        if(localNo->cod == isbnLivro){
            filaEndereco = veriFila(lista, localNo);
            if(filaEndereco){
                fila = filaEndereco->fila;
                if(fila->cabeca->matricula != matricula) return 0;
            if(fila->cabeca->proximo!=NULL){
                temp = fila->cabeca;
                fila->cabeca = temp->proximo;
                free(temp);
                return 1;//as funcoes ainda estao imcompletas, falta algumas dependencias ainda!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimos.h"
#include "usuarios.h"
#include "livros.h"
#include "lista.h"


//cria a lista controladora de filas (1 por programa)
listaFilas *criarListaFilas(){
    listaFilas *lista = (listaFilas*) malloc(sizeof(listaFilas));
    if(lista) return lista;
    else{
        printf("Erro ao alocar memória da Lista controladora");
        return NULL;
    }
}

//adiciona uma fila para a lista controladora

//int adicionarListaFilas();

//remove uma fila da lista controladora

//int removerListaFilas();

//deleta a controladora no fim da execucao do programa

//int deletarListaFilas();



//função para verificar se existe a fila para aquele livro
fila *veriFila(listaFilas *lista, livro *livrop){
    int i;
    fila *localNo = lista->filaCabeca;
    for(i=0; i<lista->tamanho; i++){
        if(localNo->livro == livrop){
            return localNo;
        }
        localNo = localNo->proximo;
    }
    return NULL;
}



//função para colocar em uma fila quando ocorre um emprestimo, lida com casos de livro já emprestado ou nao e se a fila ainda existe ou n
int colocaFila(int matricula, livro *livrop, listaFilas *lista){

    if(livrop->status == 1) return 0;
    fila *enderecoFila = veriFila(lista, livrop);
    if(enderecoFila){
        inserirFila(enderecoFila->fila, matricula);
        return 1;
    }else{
        filaUsuarios *novaFila = criarListaFilaUsuarios();
        inserirFila(novaFila, matricula);
        return novaFila->tamanho;
    }
}

//funcao que efetiviamente faz o emprestimo
/*
int fazerEmprestimo(listaFilas *lista, lista_livro *listaLivro, int codLivro, int matricula){
    int i;
    livro *localNo = listaLivro->cabeca;
    for(i=0; i<lista->tamanho; i++){
        if(localNo->cod == codLivro){
           int veri = colocaFila(matricula, localNo, lista);
            if(!veri){
                localNo->status = 0;
                return veri;
            }else return veri;
        }
        localNo = localNo->proximo;
    }
    return NULL;
}
*/

//funcao de devolucao de livro, lida com o caso de precisar deletar a lista se so existe uma pessoa esperando e caso ha mais de uma pessoa na fila.
/*
int devolverLivro(listaFilas *lista, lista_livro *listaLivro ,int codLivro, int matricula){
    int i;
    fila *filaEndereco;
    filaUsuarios* fila;
    livro *localNo = listaLivro->cabeca;
    fila_no *temp;
    for(i=0; i<listaLivro->tamanho; i++){
        if(localNo->cod == codLivro){
            filaEndereco = veriFila(lista, localNo);
            if(filaEndereco){
                fila = filaEndereco->fila;
                if(fila->cabeca->matricula != matricula) return 0;
            if(fila->cabeca->proximo!=NULL){
                temp = fila->cabeca;
                fila->cabeca = temp->proximo;
                free(temp);
                return 1;
            }else{
                free(fila->cabeca);
                free(fila);
                localNo->status = 1;
                return 2;
            }
            }
        }
    }
    return 0;
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//adiciona uma fila para a lista controladora
int adicionarListaFilas(listaFilas *lista, livro *livroP, filaUsuarios *filaP) {
    fila *novoNo = (fila*) malloc(sizeof(fila));
    if (novoNo == NULL) return 0;
    
    novoNo->livro = livroP;
    novoNo->fila = filaP;
    novoNo->proximo = NULL;

    if (lista->filaCabeca == NULL) {
        lista->filaCabeca = novoNo;
    } else {
        fila *atual = lista->filaCabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    lista->tamanho++;
    return 1;
}

//remove uma fila da lista controladora
int removerListaFilas() {
    printf("Função removerListaFilas não implementada.\n");
    return 0; // Implementação pendente
}

//deleta a controladora no fim da execucao do programa
int deletarListaFilas() {
    printf("Função deletarListaFilas não implementada.\n");
    return 0; // Implementação pendente
}

// ... código de veriFila ...

// NOVO: Função que efetivamente faz o empréstimo (versão minimalista)
int fazerEmprestimo(listaFilas *lista, lista_livro *listaLivro, int codLivro, int matricula){
    // ... Implementação real será feita com a lógica de empréstimos ...
    printf("Funcionalidade de Empréstimo em desenvolvimento. Tentando encontrar livro...\n");
    livro *l = buscarLivroPorCodigo(listaLivro, codLivro);
    if(l != NULL) {
        printf("Livro encontrado: %s. Status: %d\n", l->titulo, l->status);
        // Coloca a lógica de emprestar (atualizar status e array do usuário) aqui
        return 1;
    }
    printf("Livro não encontrado.\n");
    return 0;
}

// NOVO: Função de devolução (versão minimalista)
int devolverLivro(listaFilas *lista, lista_livro *listaLivro ,int codLivro, int matricula){
    // ... Implementação real será feita com a lógica de devolução ...
    printf("Funcionalidade de Devolução em desenvolvimento. Tentando encontrar livro...\n");
    livro *l = buscarLivroPorCodigo(listaLivro, codLivro);
    if(l != NULL) {
        printf("Livro encontrado: %s. Status: %d\n", l->titulo, l->status);
        // Coloca a lógica de devolução (atualizar status e array do usuário) aqui
        return 1;
    }
    printf("Livro não encontrado.\n");
    return 0;
}
            }else{
                free(fila->cabeca);
                free(fila);
                localNo->status = 1;
                return 2;
            }
            }
        }
    }
    return 0;
}