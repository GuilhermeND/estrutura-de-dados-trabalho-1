//as funcoes ainda estao imcompletas, falta algumas dependencias ainda!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "emprestimos.h"
#include "usuarios.h"
#include "livros.h"
#include "lista.h"

data calcularDataDevolucao() {
    data data_devolucao;

    time_t agora = time(NULL);

    struct tm* data_emprestimo = localtime(&agora);

    data_emprestimo->tm_mday += 7;

    mktime(data_emprestimo);

    strftime(data_devolucao.dataHoje, sizeof(data_devolucao.dataHoje), "%Y-%m-%d", data_emprestimo);

    return data_devolucao;
}

//cria a lista controladora de filas (1 por programa)
listaFilas *criarListaFilas(){
    listaFilas *lista = (listaFilas*) malloc(sizeof(listaFilas));
    if(lista == NULL) {
        printf("Erro: Falha ao alocar memória da Lista controladora");
        return NULL;
    }
    lista->filaCabeca = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para adicionar uma fila para a lista controladora
int adicionarListaFilas();

// Função para remover uma fila da lista controladora
int removerListaFilas();

// Função para deletar a controladora no fim da execução do programa
int deletarListaFilas();

// Função para verificar se existe a fila para aquele livro
fila *veriFila(listaFilas *lista, livro *livrop){
    if (lista == NULL || lista->filaCabeca == NULL) {
        return NULL; // A lista está vazia, não há filas para verificar
    }

    fila *localNo = lista->filaCabeca;
    while (localNo != NULL) {
        if(localNo->livro == livrop){
            return localNo;
        }
        localNo = localNo->proximo;
    }
    return NULL;
}

// Função para colocar em uma fila quando ocorre um emprestimo, lida com casos de livro já emprestado ou nao e se a fila ainda existe ou n
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

int definirLivros(livro *livrop, usuario *usuariop){
    data dataDevolucao = calcularDataDevolucao();
    if(usuariop->livros_emprestados[0] != NULL && usuariop->livros_emprestados[1] != NULL){
        return 0;
    }
    if(usuariop->livros_emprestados[0] == NULL){
        usuariop->livros_emprestados[0] = livrop;
        strcpy(usuariop->data_devolucao[0], dataDevolucao.dataHoje);
    }else{
        usuariop->livros_emprestados[1] = livrop;
        strcpy(usuariop->data_devolucao[1], dataDevolucao.dataHoje);
    }
    return 1;
}


// Função que efetivamente faz o emprestimo
int fazerEmprestimo(lista_usuario *listaUsuario, listaFilas *lista, lista_livro *listaLivro, int isbnLivro, int matricula){
    int i;
    usuario *localUsuario = buscarUsuario(listaUsuario, matricula);
    livro *localNo = listaLivro->cabeca;
    for(i=0; i<lista->tamanho; i++){
        if(localNo->cod == isbnLivro){
           int veri = colocaFila(matricula, localNo, lista);
            if(!veri){
                localNo->status = 0;
                definirLivros(localNo, localUsuario);
                return veri;
            }else return veri;
        }
        localNo = localNo->proximo;
    }
    return -1;
}

// Função de devolucao de livro, lida com o caso de precisar deletar a lista se so existe uma pessoa esperando e caso ha mais de uma pessoa na fila.
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
                return fila->tamanho;
            }else{
                free(fila->cabeca);
                free(fila);
                localNo->status = 1;
                return -1;
            }
            }
        }
    }
    return 0;
}

// Função para imprimir a fila de espera de um livro
// trava o programa ao chamar essa função sem a fila existir
int imprimirFilaEspera(listaFilas *lista, lista_livro *listaLivro, int codLivro) {
    livro *book = buscarLivroPorCodigo(listaLivro, codLivro);

    if (book == NULL) { 
        printf("Erro: Livro com codigo %d nao foi encontrado.\n", codLivro);
        return 0;
    } 
    
    // 2. Procurar o nó da fila
    fila *fila_node = veriFila(lista, book); 

    // 3. Avisa se o nó da fila NÃO EXISTE
    if (fila_node == NULL) {
        printf("Erro: Nao ha fila de espera para o livro '%s' (Cod: %d) no momento.\n", book->titulo, codLivro);
        return 1; // Sucesso: Livro existe, fila não existe.
    }

    // 4. Imprimir a Fila (SÓ ACONTECE SE FILA_NODE != NULL)
    printf("Fila de espera para '%s' (Cod: %d):\n", book->titulo, codLivro);
    imprimirFila(fila_node->fila); 

    return 1;
}