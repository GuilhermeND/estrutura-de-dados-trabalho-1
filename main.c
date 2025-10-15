#include<stdio.h>
#include "livros.h"
#include "lista.h"
#include "emprestimos.h"
#include "usuarios.h"

int escolhaLivro(){
    int escolha;
    printf("------------------LIVRO----------------\n");
    printf("1.Emprestar Livro\n");
    printf("2.Devolver Livro\n");
    printf("3.Buscar informacoes do livro por nome\n");
    printf("4.Imprimir disponibilidade de um livro\n");
    scanf("%d", &escolha);
    switch (escolha){
        case 1:

            break;
    
    default:
        break;
    }
}

int escolhaUsuario(){
    int escolha;
    printf("--------------USUARIO----------------\n");
    printf("1.Exibir informacoes de um usuario\n");
    printf("2.Exibir data(s) de devolucao de um usuario\n");
    scanf("%d" ,&escolha);
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
    int escolha;
    printf("--------------BIBLIOTECA----------------\n");
    printf("Escolha uma das opções: \n");
    printf("1.Livros\n");
    printf("2.Usuarios\n");
    printf("3.Administrado\n");
    scanf("%d", &escolha);
    switch (escolha){

        case 1:
            escolhaLivro();
            break;
        case 2:
            escolhaUsuario();
            break;
        case 3:
            escolhaAdmnistrador();
            break;
        default:
            printf("Escolha inválida!\n");
            break;
    }






    return 0;
}