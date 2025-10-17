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

    // ========================================================
    // INFORMAÇÕES PARA TESTES (4 Usuários e 3 Livros)
    // ========================================================
    printf("--- Inicializando dados para teste ---\n");

    // USUÁRIOS: (Nome, Matrícula, Tipo: 0=Estudante, 1=Professor)
    if (inserirUsuario(listaUsuarios, "eduardo", 13, 0)) {
        printf("Usuario: Eduardo (13) adicionado.\n");
    }
    if (inserirUsuario(listaUsuarios, "guilherme", 15, 1)) {
        printf("Usuario: Guilherme (15) adicionado.\n");
    }
    if (inserirUsuario(listaUsuarios, "helcio", 20, 1)) {
        printf("Usuario: Helcio (20) adicionado.\n");
    }
    if (inserirUsuario(listaUsuarios, "amanda", 25, 0)) {
        printf("Usuario: Amanda (25) adicionado.\n");
    }

    // LIVROS: (Título, Editora, Autor)
    if (inserirLivro(listaLivros, "ed", "Prentice Hall", "Weiss")) {
        printf("Livro: ed adicionado.\n");
    }
    if (inserirLivro(listaLivros, "teste", "Saraiva", "Manzano")) {
        printf("Livro: teste adicionado.\n");
    }
    if (inserirLivro(listaLivros, "aula", "UFPR Press", "Professor X")) {
        printf("Livro: Aula adicionado.\n");
    }
    printf("--- Dados iniciais carregados. ---\n\n");
    // ========================================================
    
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
                escolhaLivro(listaUsuarios, listaControladora, listaLivros);
                break;

            case 2:
                escolhaUsuario(listaUsuarios);
                break;

            case 3:
                escolhaAdmnistrador(listaUsuarios, listaLivros);
                break;

            case 0:
                printf("Encerrando o programa.\n");
                return 0;

            default:
                printf("Erro: Escolha invalida!\n");
                break;
        }
    }
    return 0;
}  