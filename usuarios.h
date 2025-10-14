typedef struct user
{
    char nome[50];
    int matricula; // {GRR}
    int tipo; // {0 = estudante 1 = professor}
    struct user *proximo;
} usuario;

typedef struct list_user
{
    usuario *cabeca;
    int tamanho;
} lista_usuario;

// Protótipos das funções para manipulação da lista de usuários
lista_usuario* criarLista();

int estaVazia(lista_usuario *lista);

int inserirFim(lista_usuario *lista, char nome[50], int matricula, int cargo);

int buscarUsuario(lista_usuario *lista, char nome[50]); // busca as informações do usuário pelo nome para imprimir //

int buscarMatricula(lista_usuario *lista, char nome[50]); // busca a matricula do usuário pelo nome para imprimir //

int removerUsuario(lista_usuario *lista, char nome[50]);