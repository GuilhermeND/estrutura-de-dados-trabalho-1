#include "lista.h"
#include "usuarios.h"
#include "livros.h"

typedef struct queues //talvez criar uma lista dinamica seja melhor
{
    livro *livro;
    lista_circular *lista; 

}fila;

typedef struct _listaFilas
{
    fila *fila;
    int tamanho;
}listaFilas;



int colocaFila(int matricula, livro *livro);

//verifica se o livro está disponível (status = 1) se sim retorna 0 e muda o status do livro para 0
//se não estiver, procura se a fila já existe em listaFilas com algum node igual ao *livro do argumento dessa função
//se sim, chama adicionarLista()
//se não cria um fila e adiciona no final de listaFilas
//chama criarListaFila() e adiciona o usuário com inserirFila()
//retorna a posição do usuário na fila = tamanho

int fazerEmprestimo(lista_livro *lista ,char nomeLivro[100], int matricula);

//se livro está emprestado chama colocarFila

int devolverLivro(lista_livro *lista ,char nomeLivro[100], int matricula);