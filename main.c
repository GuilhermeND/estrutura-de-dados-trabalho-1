#include<stdio.h>
#include "livros.h"
#include "lista.h"
#include "emprestimos.h"
#include "usuarios.h"

int escolhaLivro(lista_livro *listaLivros){
    int escolha;
    char userIn[100];
    while(1){
        printf("------------------LIVRO----------------\n");
        printf("1.Emprestar Livro\n");
        printf("2.Devolver Livro\n");
        printf("3.Imprimir lista de livros\n");
        printf("4.Buscar informacoes do livro por nome\n");
        printf("5.Imprimir disponibilidade de um livro\n");
        printf("6.Voltar\n");
        scanf("%d", &escolha);
        switch (escolha){
            case 1:

                break;
            case 2:

                break;
            case 3:
                imprimirListaInfo(listaLivros);
                break;
            case 4:
                printf("Escreva o nome do livro que deseja procurar: ");
                fgets(userIn, sizeof(userIn), stdin);
                imprimirLivroInfo(listaLivros, userIn);

                break;
            case 5:
                printf("Escreva o nome do livro que deseja procurar: ");
                fgets(userIn, sizeof(userIn), stdin);
                imprimirStatus(listaLivros, userIn);
                break;
            case 6:
                return 0;
                break;
            default:
                printf("Valor Inválido!");
                break;
        }
    }
    return 1;
}

int escolhaUsuario(lista_usuario *listaUsuarios){
    int escolha;
    int userIn;
    char userName[100];
    while(1){
        printf("--------------USUARIO----------------\n");
        printf("1.Exibir informacoes de um usuario\n");
        printf("2.Exibir livro(s) emprestado(s) de um usuario\n");
        printf("3.Buscar matricula de usuario por nome\n");
        printf("4.Voltar\n");
        scanf("%d" ,&escolha);

        switch (escolha){
            case 1:
                printf("Escreva a matricula do usuario: ");
                scanf("%d", &userIn);
                break;
            case 2:
                printf("Escreva a matricula do usuario: ");
                scanf("%d", &userIn);
                break;
            case 3:
                printf("Escreva o nome do usuario(precisa ser o nome exato):  ");
                fgets(userName, sizeof(userName), stdin);
                buscarMatricula(listaUsuarios, userName);
                break;
            case 4: 
                return 0;
                break;
            
            default:
                printf("Escolha inválida!");
                break;
        }
    }
}

int escolhaAdmnistrador(){
    int senha = 130;
    int senhain;
    int escolha;
    printf("--------------ADMNISTRATIVO----------------\n");
    printf("Digite a senha: ");
    scanf("%d", &senhain);
    if(senhain != senha){
        printf("Senha inválida tente novamente!\n");
        return 0;
    }

    printf("Logado com sucesso!");
    printf("--------------ADMNISTRATIVO----------------\n");
    printf("1.Adicionar um usuario\n");
    printf("2.Adicionar um livro\n");
    printf("3.Remover um usuario\n");
    printf("4.Remover um livro\n");
    printf("5.Voltar\n");

    scanf("%d", &escolha);

    switch (escolha){
        case 1:
            
            break;
        
        default:
            break;
    }

}


int main(){
    listaFilas *listraControladora = criarListaFilas();
    lista_livro *listaLivros = criarLista();
    lista_usuario *listaUsuarios = criarListaUsuario();
    
    int escolha;

    while(escolha != 0) {
        printf("--------------BIBLIOTECA----------------\n");
        printf("Escolha uma das opções: \n");
        printf("1.Livros\n");
        printf("2.Usuarios\n");
        printf("3.Administrado\n");
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                escolhaLivro(listaLivros);
                break;

            case 2:
                escolhaUsuario(listaUsuarios);
                break;

            case 3:
                escolhaAdmnistrador();
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Escolha inválida!\n");
                break;
        }
    }

    return 0;
}