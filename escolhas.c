#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include "livros.h"
#include "lista.h"
#include "emprestimos.h"
#include "usuarios.h"

int escolhaLivro(lista_livro *listaLivros){
    int escolha_livro;
    char userIn[100];
    int userInCod;
    livro *livroBusca;
    int result;
    while(1){
        printf("------------------LIVRO----------------\n");
        printf("1.Emprestar Livro\n");
        printf("2.Devolver Livro\n");
        printf("3.Imprimir lista de livros\n");
        printf("4.Buscar informacoes do livro por nome\n");
        printf("5.Imprimir disponibilidade de um livro\n");
        printf("6.Voltar\n");
        result = scanf("%d", &escolha_livro);
        if(result != 1){
            printf("Erro: Valor invalido tente novamente!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (escolha_livro){
            case 1:

                break;
            case 2:

                break;
            case 3:
                imprimirListaInfo(listaLivros);
                break;
            case 4:
                printf("Escreva o nome do livro que deseja procurar: ");
                while (getchar() != '\n');
                fgets(userIn, sizeof(userIn), stdin);
                if (!strchr(userIn, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                userIn[strcspn(userIn, "\n")] = '\0';
                livroBusca = buscarLivroPorTitulo(listaLivros, userIn);
                printf("Titulo: %s\n Autor: %s\n Editora: %s\n Status: %d\n", livroBusca->titulo, livroBusca->autor, livroBusca->editora, livroBusca->status);

                break;
            case 5:
                printf("Escreva o nome do livro que deseja procurar: ");
                result = scanf("%d", &userIn);
                if(result != 1){
                    printf("Erro: Valor invalido tente novamente!\n");
                    while (getchar() != '\n');
                }
                livroBusca = buscarLivroPorCodigo(listaLivros, userInCod);
                if(livroBusca->status){
                    printf("O livro esta disponivel");
                }else{
                    printf("O livro nao esta disponivel");
                }
                break;
            case 6:
                return 0;
            default:
                printf("Valor Inválido!");
                break;
        }
    }
    return 1;
}

int escolhaUsuario(lista_usuario *listaUsuarios){
    int escolha_Usuario;
    int userIn;
    char userName[100];
    int result;
    while(1){
        printf("--------------USUARIO----------------\n");
        printf("1.Exibir informacoes de um usuario\n");
        printf("2.Exibir livro(s) emprestado(s) de um usuario\n");
        printf("3.Buscar matricula de usuario por nome\n");
        printf("4.Voltar\n");
        result = scanf("%d", &escolha_Usuario);
        if(result != 1){
            printf("Erro: Valor invalido tente novamente!\n");
            while (getchar() != '\n');
            continue;
        }
        

        switch (escolha_Usuario){
            case 1:
                printf("Escreva a matricula do usuario: ");
                result = scanf("%d", &userIn);
                if(result != 1){
                    printf("Erro: Valor invalido tente novamente!\n");
                    while (getchar() != '\n');
                }
                break;
            case 2:
                printf("Escreva a matricula do usuario: ");
                result = scanf("%d", &userIn);
                if(result != 1){
                    printf("Erro: Valor invalido tente novamente!\n");
                    while (getchar() != '\n');
                }
                break;
            case 3:
                printf("Escreva o nome do usuario(precisa ser o nome exato):  ");
                while (getchar() != '\n');
                fgets(userName, sizeof(userName), stdin);
                if (!strchr(userName, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                userName[strcspn(userName, "\n")] = '\0';
                buscarMatricula(listaUsuarios, userName);
                break;
            case 4: 
                return 0;
            default:
                printf("Escolha invalida!\n");
                break;
        }
    }
}

int escolhaAdmnistrador(lista_usuario *listaUsuarios, lista_livro *listaLivros){
    int senha = 130;
    int senhain = 0;
    int escolha_ADM;
    char nome[50];
    int matricula;
    int cargo;
    int cod;
    int e; // erro
    printf("--------------ADMNISTRATIVO----------------\n");
    printf("Digite a senha: ");
    int result = scanf("%d", &senhain);
    if(result != 1){
        printf("Erro: Senha invalida tente novamente!\n");
        while (getchar() != '\n');
        return 0;
    }
    if(senhain != senha){
        printf("Erro: Senha invalida tente novamente!\n");
        return 0;
    }

    printf("Logado com sucesso!\n");
    while(1){
        printf("--------------ADMNISTRATIVO----------------\n");
        printf("1.Adicionar um usuario\n");
        printf("2.Adicionar um livro\n");
        printf("3.Remover um usuario\n");
        printf("4.Remover um livro\n");
        printf("5.Voltar\n");

        result = scanf("%d", &escolha_ADM);
        
        if(result != 1){
            printf("Erro: Valor invalido tente novamente!\n");
            while (getchar() != '\n');
            continue;
        };
        while (getchar() != '\n');
        switch (escolha_ADM){
            case 1:
                printf("Escreva o nome do usuario que deseja adicionar: ");
                fgets(nome, sizeof(nome), stdin);
                if (!strchr(nome, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                nome[strcspn(nome, "\n")] = '\0';
                printf("Escreva a matricula do usuario: ");
                result = scanf("%d", &matricula);
                if(result != 1){
                    printf("Erro: Valor invalido tente novamente!\n");
                    while (getchar() != '\n');
                    continue;
                };
                while (1) {
                    printf("Digite 0 se for estudante e 1 se for professor: ");
                    result = scanf("%d", &cargo);

                    if (result != 1) {
                        printf("Erro: Valor invalido tente novamente!\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    while (getchar() != '\n');
                    if (cargo == 0 || cargo == 1) break;
                    
                    printf("Valor de cargo invalido, tente novamente!\n");
                }
                inserirUsuario(listaUsuarios, nome, matricula, cargo);
                break;
            


            case 2:
                char titulo[100];
                char editora[50];
                char autor[50]; 
                printf("Escreve o titulo do livro: ");
                fgets(titulo, sizeof(titulo), stdin);
                if (!strchr(titulo, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("\nEscreve o nome da editora do livro: ");
                fgets(editora, sizeof(editora), stdin);
                if (!strchr(editora, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                printf("\nEscreve o nome do autor do livro: ");
                fgets(autor, sizeof(autor), stdin);
                if (!strchr(autor, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                inserirLivro(listaLivros, titulo, editora, autor);
                break;



            case 3:
                printf("Escreva a matricula do usuario que deseja remover: ");
                result = scanf("%d", &matricula);
                if(result != 1){
                    printf("Erro: valor nao numeral, tente novamente!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                e = removerUsuario(listaUsuarios, matricula);
                if(e == 0){
                    printf("Erro ao remover usuario!");
                }else{
                    printf("Removido com sucesso!\n");
                }
                break;


            case 4:
                printf("Escreva o codigo do livro que deseja remover: ");
                result = scanf("%d", &cod);
                if(result != 1){
                    printf("Erro: valor nao numeral, tente novamente!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');
                e = removerLivro(listaLivros, cod);
                if(e == 0){
                    printf("Erro ao remover livro!");
                }else{
                    printf("Removido com sucesso!\n");
                }
                break;

                
            case 5:
                return 0;    
            default:
                break;
        }
    }
}