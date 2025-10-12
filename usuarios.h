typedef struct user
{
    char nome[50];
    char matricula[20]; // {GRR}
    int tipo; //{0 = estudante 1 = professor}
}usuario;

typedef struct list_user
{
    usuario *cabeca;
    int tamanho;
}lista_usuario;

int estaVazia(lista_usuario *lista);

lista_usuario* criarLista();

int inserirFim(lista_usuario *lista, char nome[50], char matricula[20], int cargo);

int buscarUsuario(lista_usuario *lista, char nome[50]);

int busrcarMatricula(lista_usuario *lista, char nome[50]);

int removerUsuario(lista_usuario *lista, char nome[50]);