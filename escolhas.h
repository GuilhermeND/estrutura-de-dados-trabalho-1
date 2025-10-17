#ifndef ESCOLHAS_H
#define ESCOLHAS_H

#include "livros.h"
#include "lista.h"
#include "emprestimos.h"
#include "usuarios.h"

int escolhaLivro(lista_usuario *listaUsuario, listaFilas *listaControladora ,lista_livro *listaLivros); // Função para o menu de escolha de livros
int escolhaUsuario(lista_usuario *listaUsuarios); // Função para o menu de escolha de usuários
int escolhaAdmnistrador(lista_usuario *listaUsuarios, lista_livro *listaLivros); // Função para o menu de escolha do administrador

#endif // ESCOLHAS_H