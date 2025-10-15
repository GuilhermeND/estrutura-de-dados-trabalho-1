#include "lista.h"
#include "usuarios.h"
#include "livros.h"

// lista das filas, cada livro tem sua fila
typedef struct queues //talvez criar uma lista dinamica seja melhor
{
    livro *livro;
    fila *fila; 
    struct queues *proximo;
} fila;

typedef struct _listaFilas
{
    fila *fila;
    int tamanho;
} listaFilas;



int colocaFila(int matricula, livro *);
// se o livro estiver disponivel retorna 0
// se já estiver emprestado verifica se existe fila do livro
//se sim, chama adicionarLista()



//verifica se o livro está disponível (status = 1) se sim retorna 0 e muda o status do livro para 0
//se não estiver, procura se a fila já existe em listaFilas com algum node igual ao *livro do argumento dessa função
//se sim, chama adicionarLista()
//se não cria um fila e adicionlivroa no final de listaFilas
//chama criarListaFila() e adiciona o usuário com inserirFila()
//retorna a posição do usuário na fila = tamanho

int fazerEmprestimo(lista_livro *lista ,char nomeLivro[100], int matricula);

//se livro está emprestado chama colocarFila

int devolverLivro(lista_livro *lista ,char nomeLivro[100], int matricula);