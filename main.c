#include<stdio.h>
#include "escolhas.h"
#include "livros.h"
#include "lista.h"
#include "emprestimos.h"
#include "usuarios.h"

int main(){
    listaFilas *listaControladora = criarListaFilas();
    lista_livro *listaLivros = criarListaLivro();
    lista_usuario *listaUsuarios = criarListaUsuario();
    
    int escolha;
    int result;
    while(1) {
        printf("--------------BIBLIOTECA----------------\n");
        printf("Escolha uma das opcoes: \n");
        printf("1.Livros\n");
        printf("2.Usuarios\n");
        printf("3.Administrado\n");
        printf("0.Sair\n");
        printf("Opcao: ");
        result = scanf("%d", &escolha);
        if(result != 1){
            printf("Erro: Valor invalido tente novamente!\n");
            while (getchar() != '\n');
        }
        switch (escolha){
            case 1:
                escolhaLivro(listaControladora, listaLivros);
                break;

            case 2:
                escolhaUsuario(listaUsuarios);
                break;

            case 3:
                escolhaAdmnistrador(listaUsuarios, listaLivros);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Erro: Escolha inválida!\n");
                break;
        }
    }
    return 0;
}  