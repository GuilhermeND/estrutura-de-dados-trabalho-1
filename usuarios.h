typedef struct user
{
    char nome[50];
    int matricula; // GRR
    int tipo; // 0 = estudante 1 = professor
    char livros_emprestados[2][100]; // armazena o título dos livros emprestados
    char data_devolucao[2][11]; // armazena a data de devolução dos livros
    struct user *proximo;
} usuario;

typedef struct list_user
{
    usuario *cabeca;
    int tamanho;
} lista_usuario;

// Protótipos das funções para manipulação da lista de usuários
lista_usuario* criarListaUsuario();

int estaVazia(lista_usuario *lista);

int inserirFim(lista_usuario *lista, char nome[50], int matricula, int cargo);

void buscarMatricula(lista_usuario *lista, char nome[50]); // busca a matricula do usuário pelo nome para imprimir

int buscarUsuario(lista_usuario *lista, int matricula); // busca as informações do usuário pela matrícula para imprimir

int removerUsuario(lista_usuario *lista, int matricula);

void imprimirLivrosEmprestados(lista_usuario *lista, int matricula);