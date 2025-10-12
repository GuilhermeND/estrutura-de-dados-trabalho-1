
typedef struct no
{
    char titulo[100];
    char editora[50];
    char autor[50];
    int status; // 0 para ocupado 1 para disponível
    int cod;
    struct no *proximo;
}livro;

typedef struct list{
    livro *cabeca;
    int tamanho;
}lista_livro;

int estaVazia(lista_livro *lista);

lista_livro* criarLista();

int inserirFinal(lista_livro *lista, char titulo[100], char editora[50], char autor[50]);

int atualizarStatus(livro *livro);

int removerLivro(lista_livro *lista, char titulo[100]);

void imprimirLivroInfo(lista_livro *lista, char titulo[100]);

int buscarCod(lista_livro *lista, char titulo[100]);

void imprimirListaInfo(lista_livro *lista);



