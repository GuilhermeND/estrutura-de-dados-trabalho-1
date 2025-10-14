typedef struct no 
{
    char titulo[100];
    char editora[50];
    char autor[50];
    int status;
    int isbn;
    struct no *proximo;
} livro;

typedef struct list 
{
    livro *cabeca;
    int tamanho;
} lista_livro;

// Protótipos das funções para manipulação da lista de livros
lista_livro* criarLista();

int estaVazia(lista_livro *lista);

int inserirFinal(lista_livro *lista, char titulo[100], char editora[50], char autor[50]);

int atualizarStatus(livro *livro);

int removerLivro(lista_livro *lista, char titulo[100]);

void imprimirLivroInfo(lista_livro *lista, char titulo[100]);

int buscarISBN(lista_livro *lista, char titulo[100]);

void imprimirListaInfo(lista_livro *lista);