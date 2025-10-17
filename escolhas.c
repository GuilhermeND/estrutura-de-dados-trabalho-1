#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "livros.h"
#include "lista.h"
#include "emprestimos.h"
#include "usuarios.h"

int escolhaLivro(lista_usuario *listaUsuario, listaFilas *listaControladora, lista_livro *listaLivros){
    int escolha_livro;
    char userIn[100];
    int userInCod;
    int userInMat;
    livro *livroBusca;
    int result;
    int e;
    while(1){
        printf("------------------LIVRO----------------\n");
        printf("1.Emprestar Livro\n");
        printf("2.Devolver Livro\n");
        printf("3.Imprimir lista de livros\n");
        printf("4.Buscar informacoes do livro por nome\n");
        printf("5.Imprimir fila de espera de um livro\n");
        printf("6.Voltar\n");
        printf("Opcao: ");
        
        result = scanf("%d", &escolha_livro);
        if(result != 1){
            printf("Erro: Valor invalido tente novamente!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (escolha_livro){
            case 1:
                if (listaLivroEstaVazia(listaLivros)){
                    printf("Erro: A lista de livros esta vazia.\n");
                    break;
                }
                printf("Insira o codigo do livro a ser emprestado: ");
                scanf("%d", &userInCod);
                while (getchar() != '\n');
                printf("Insira o codigo da matricula de quem vai emprestar: ");
                scanf("%d", &userInMat);
                while (getchar() != '\n');
                e = fazerEmprestimo(listaUsuario, listaControladora, listaLivros, userInCod, userInMat);
                if(e == -1){
                    printf("Erro: Falha ao emprestar!\n");
                    continue;
                }else{
                    printf("Sucesso ao emprestar e a posicao na fila eh: %d\n", e);
                }
                break;
            case 2:
                if (listaLivroEstaVazia(listaLivros)){
                    printf("Erro: A lista de livros esta vazia.\n");
                    break;
                }
                printf("Insira o codigo do livro a ser devolvido: ");
                scanf("%d", &userInCod);
                while (getchar() != '\n');
                printf("Insira o codigo da matricula de quem vai devolver: ");
                scanf("%d", &userInMat);
                while (getchar() != '\n');
                e = devolverLivro(listaControladora, listaLivros, userInCod, userInMat);
                if(e == 0){
                    printf("Erro ao emprestar!\n");
                    continue;
                }else if(e == -1){
                    printf("Sucesso ao devolver e o livro está sem fila no momento!\n");
                }else{
                    printf("Sucesso ao devolver e o tamanho da fila daquele livro é %d\n", e);
                }
                break;
            case 3:
                imprimirListaInfo(listaLivros);
                break;
            case 4:
                if (listaLivroEstaVazia(listaLivros)){
                    printf("Erro: A lista de livros esta vazia.\n");
                    break;
                }
                printf("Escreva o nome do livro que deseja procurar: ");
                while (getchar() != '\n');
                fgets(userIn, sizeof(userIn), stdin);
                if (!strchr(userIn, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                userIn[strcspn(userIn, "\n")] = '\0';
                livroBusca = buscarLivroPorTitulo(listaLivros, userIn);
                if(!livroBusca){
                    printf("Livro nao encontrado!\n");
                    continue;
                }else{
                    printf("----- Informacoes do Livro -----\n");
                    printf(" Titulo: %s\n", livroBusca->titulo);
                    printf("\n Editora: %s\n", livroBusca->editora);
                    printf(" Autor: %s\n", livroBusca->autor);
                    printf(" Codigo: %d\n", livroBusca->cod);
                    if(livroBusca->status == 1){
                        printf("\n Status: Disponivel\n");
                    }else{
                        printf("\n Status: Emprestado\n");
                    }
                    printf("-------------------------\n");
                }
                break;
            case 5:
                if (listaLivroEstaVazia(listaLivros)){
                    printf("Erro: A lista de livros esta vazia.\n");
                    break;
                }
                printf("Insira o codigo do livro para ver a fila de espera: ");
                scanf("%d", &userInCod);
                while (getchar() != '\n');
                printf("Fila de espera do livro %d:\n", userInCod);
                // Imprimir a fila de espera
                imprimirFilaEspera(listaControladora, listaLivros, userInCod);
                printf("\n");
                break;

            case 6:
                return 0;
            default:
                printf("Escolha invalida!\n");
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
    int e;
    usuario *localUser;
    while(1){
        printf("--------------USUARIO----------------\n");
        printf("1.Exibir informacoes de um usuario\n");
        printf("2.Exibir livro(s) emprestado(s) de um usuario\n");
        printf("3.Buscar matricula de usuario por nome\n");
        printf("4.Voltar\n");
        printf("Opcao: ");

        result = scanf("%d", &escolha_Usuario);
        if(result != 1){
            printf("Erro: Valor invalido tente novamente!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (escolha_Usuario){
            case 1:
                if (listaUsuarioEstaVazia(listaUsuarios)){
                    printf("Erro: A lista de usuarios esta vazia!\n");
                    break;
                }
                printf("Escreva a matricula do usuario: ");
                result = scanf("%d", &userIn);
                if(result != 1){
                    printf("Erro: Valor invalido tente novamente!\n");
                    while (getchar() != '\n');
                }
                localUser = buscarUsuario(listaUsuarios, userIn);
                if(!localUser){
                    printf("Erro:Lista vazia ou usuario nao encontrado!\n");
                    continue;
                }else{
                    printf(" Nome: %s\n Matricula: %d\n", localUser->nome, localUser->matricula);
                    if(localUser->tipo == 0){
                        printf(" Tipo: Estudante\n");
                    }else{
                        printf(" Tipo: Professor\n");
                    }
                    //printf("Livros emprestados: \n");
                    //printf("Data devolucao: \n"); //FALTA FAZER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }
                break;

            case 2:
                if (listaUsuarioEstaVazia(listaUsuarios)) {
                    printf("Erro: A lista de usuarios esta vazia!\n");
                    break;
                }
                printf("Escreva a matricula do usuario: ");
                result = scanf("%d", &userIn);
                if(result != 1){
                    printf("Erro: Valor invalido tente novamente!\n");
                    while (getchar() != '\n');
                }
                break;

            case 3:
                if (listaUsuarioEstaVazia(listaUsuarios)){
                    printf("Erro: A lista de usuarios esta vazia!\n");
                    break;
                }
                printf("Escreva o nome do usuario(precisa ser o nome exato):  ");
                while (getchar() != '\n');
                fgets(userName, sizeof(userName), stdin);
                if (!strchr(userName, '\n')) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                userName[strcspn(userName, "\n")] = '\0';
                e = buscarMatricula(listaUsuarios, userName);
                if(!e){
                    printf("Usuario nao encontrado ou fila vazia!\n");
                    continue;
                }
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
    char titulo[100];
    char editora[50];
    char autor[50]; 
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
        printf("3.Listar usuarios\n");
        printf("4.Listar livros\n");
        printf("5.Remover um usuario\n");
        printf("6.Remover um livro\n");
        printf("7.Voltar\n");
        printf("Opcao: ");

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
                // deve tentar inserir e verificar se deu certo e avisar o usuario
                if (inserirUsuario(listaUsuarios, nome, matricula, cargo)) {
                    printf("Usuario adicionado com sucesso!\n");
                } else {
                    printf("Erro: Matricula ja cadastrada ou falha ao adicionar!\n");
                }
                break;
            
            case 2:  
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
                if (inserirLivro(listaLivros, titulo, editora, autor)) {
                    printf("Livro adicionado com sucesso!\n");
                } else {
                    printf("Erro: Livro ja existe ou falha ao adicionar!\n");
                }
                break;

            case 3:
                imprimirListaUsuarios(listaUsuarios);
                break;

            case 4:
                imprimirListaInfo(listaLivros);
                break;

            case 5:
                if (listaUsuarioEstaVazia(listaUsuarios)){
                    printf("Erro: A lista de usuarios esta vazia!\n");
                    break;
                }
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
                    printf("Erro: Falha ao remover usuario!\n");
                }else{
                    printf("Removido com sucesso!\n");
                }
                break;

            case 6:
                if (listaLivroEstaVazia(listaLivros)){
                    printf("Erro: A lista de livros esta vazia!\n");
                    break;
                }
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
                    printf("Erro: Falha ao remover livro!");
                }else{
                    printf("Removido com sucesso!\n");
                }
                break;

            case 7:
                return 0;    
            default:
                printf("Escolha invalida!\n");
                break;
        }
    }
}