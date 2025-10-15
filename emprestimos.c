#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimos.h"
#include "usuarios.h"
#include "livros.h"
#include "lista.h"

// Função para colocar um usuário na fila de espera de um livro

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

int colocaFila(int matricula, livro *livrop, listaFilas *lista){

    if(livrop->status == 1) return 0;
    fila *enderecoFila = veriFila(lista, livrop);
    if(enderecoFila){
        inserirFila(matricula, enderecoFila->fila);
        return 1;
    }else{
        filaUsuarios *novaFila = criarListaFila();
        inserirFila(matricula, novaFila);
        return novaFila->tamanho;
    }
}

int fazerEmprestimo(listaFilas *lista, lista_livro *listaLivro, int isbnLivro, int matricula){
    int i;
    livro *localNo = listaLivro->cabeca;
    for(i=0; i<lista->tamanho; i++){
        if(localNo->isbn == isbnLivro){
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


devolverLivro(lista_livro *lista ,int isbnLivro, int matricula){
    
}