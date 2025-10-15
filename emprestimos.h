#include "lista.h"
#include "usuarios.h"
#include "livros.h"

// lista das filas, cada livro tem sua fila
typedef struct queues //talvez criar uma lista dinamica seja melhor
{
    livro *livro;
    filaUsuarios *fila; 
    struct queues *proximo;
} fila;

typedef struct _listaFilas
{
    fila *filaCabeca;
    int tamanho;
} listaFilas;

//cria a lista controladora de filas (1 por programa)
listaFilas *criarListaFilas();

//adiciona uma fila para a lista controladora

int adicionarListaFilas();

//remove uma fila da lista controladora

int removerListaFilas();

//deleta a controladora no fim da execucao do programa

int deletarListaFilas();




int veriFila(listaFilas *lista, livro *livrop);

int colocaFila(int matricula, livro *livrop, listaFilas *lista);
// se o livro estiver disponivel retorna 0
// se já estiver emprestado verifica se existe fila do livro
//se sim, chama adicionarLista()



//verifica se o livro está disponível (status = 1) se sim retorna 0 e muda o status do livro para 0
//se não estiver, procura se a fila já existe em listaFilas com algum node igual ao *livro do argumento dessa função
//se sim, chama adicionarLista()
//se não cria um fila e adicionlivroa no final de listaFilas
//chama criarListaFila() e adiciona o usuário com inserirFila()
//retorna a posição do usuário na fila = tamanho

int fazerEmprestimo(listaFilas *lista, lista_livro *listaLivro, int isbnLivro, int matricula);

//se livro está emprestado chama colocarFila

int devolverLivro(listaFilas *lista, lista_livro *listaLivro ,int isbnLivro, int matricula);