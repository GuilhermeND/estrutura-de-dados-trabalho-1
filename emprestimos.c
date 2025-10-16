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
    return -1;
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