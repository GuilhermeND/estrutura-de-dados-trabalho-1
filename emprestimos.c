//Por: Guilherme
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "emprestimos.h"
#include "usuarios.h"
#include "livros.h"
#include "lista.h"

data calcularDataDevolucao() {
    data data_devolucao;

    time_t agora = time(NULL);

    struct tm* data_emprestimo = localtime(&agora);

    data_emprestimo->tm_mday += 7;

    mktime(data_emprestimo);

    strftime(data_devolucao.dataHoje, sizeof(data_devolucao.dataHoje), "%Y-%m-%d", data_emprestimo);

    return data_devolucao;
}

//cria a lista controladora de filas (1 por programa)
listaFilas *criarListaFilas(){
    listaFilas *lista = (listaFilas*) malloc(sizeof(listaFilas));
    if(lista == NULL) {
        printf("Erro: Falha ao alocar memória da Lista controladora");
        return NULL;
    }
    lista->filaCabeca = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para adicionar uma fila para a lista controladora
int adicionarListaFilas(listaFilas *lista, livro *livrop, filaUsuarios *filaP) {
    fila *novoNo = (fila*) malloc(sizeof(fila)); // 'fila' é o nó da listaFilas
    
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memória para o nó da fila controladora.\n");
        return 0; // Falha
    }
    
    // 1. Preenche o novo nó
    novoNo->livro = livrop;
    novoNo->fila = filaP;
    novoNo->proximo = NULL;

    // 2. Insere no final da lista controladora
    if (lista->filaCabeca == NULL) {
        lista->filaCabeca = novoNo;
    } else {
        fila *atual = lista->filaCabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    
    lista->tamanho++;
    return 1; // Sucesso
}



// Função para deletar a controladora no fim da execução do programa
int deletarListaFilas(listaFilas *lista) {
    if (!lista) return 0;

    fila *atual = lista->filaCabeca;
    while (atual != NULL) {
        fila *proxFila = atual->proximo;

        // Libera a fila de usuários
        filaUsuarios *f = atual->fila;
        if (f) {
            fila_no *temp = f->cabeca;
            for (int i = 0; i < f->tamanho && temp != NULL; i++) {
                fila_no *prox = temp->proximo;
                free(temp);
                temp = prox;
            }
            free(f);
        }

        free(atual);
        atual = proxFila;
    }

    lista->filaCabeca = NULL;
    lista->tamanho = 0;
    return 1;
}

// Função para verificar se existe a fila para aquele livro
fila *veriFila(listaFilas *lista, livro *livrop){
    if (lista == NULL || lista->filaCabeca == NULL) {
        return NULL; // A lista está vazia, não há filas para verificar
    }

    fila *localNo = lista->filaCabeca;
    while (localNo != NULL) {
        if(localNo->livro == livrop){
            return localNo;
        }
        localNo = localNo->proximo;
    }
    return NULL;
}

// Função para colocar em uma fila quando ocorre um emprestimo, lida com casos de livro já emprestado ou nao e se a fila ainda existe ou n
int colocaFila(int matricula, livro *livrop, listaFilas *lista){
    fila *enderecoFila = veriFila(lista, livrop);

    if(enderecoFila) { // Verifica se a fila existe
        // Adiciona o usuário nela e retorna a nova posição.
        inserirFila(enderecoFila->fila, matricula);
        return enderecoFila->fila->tamanho; // Retorna a posição (que é o tamanho)
        
    } else {
        filaUsuarios *novaFila = criarListaFilaUsuarios(); // Cria uma nova fila de usuários
        
        if (novaFila == NULL) {
             printf("Erro: Falha ao criar a nova fila de usuários.\n");
             return 0;
        }
        
        inserirFila(novaFila, matricula); // O tamanho é 1
        
        // Conecta a nova fila à lista controladora
        int adicionado = adicionarListaFilas(lista, livrop, novaFila);
        
        if (adicionado) {
            return novaFila->tamanho; // Retorna 1 (posição na fila)
        } else {
            return 0; 
        }
    }
}

// Função para definir os livros emprestados e suas datas de devolução para o usuário
int definirLivros(livro *livrop, usuario *usuariop) {
    data dataDevolucao = calcularDataDevolucao();
    // Verifica se o usuário pode pegar mais um livro
    if (usuariop->livros_emprestados[0] != NULL && usuariop->livros_emprestados[1] != NULL) {
        return 0; // Limite atingido
    }

    // Define o livro no primeiro slot disponível
    if (usuariop->livros_emprestados[0] == NULL) {
        usuariop->livros_emprestados[0] = livrop;
        strcpy(usuariop->data_devolucao[0], dataDevolucao.dataHoje);
    } else { // Slot 1
        usuariop->livros_emprestados[1] = livrop;
        strcpy(usuariop->data_devolucao[1], dataDevolucao.dataHoje);
    }
    return 1;
}


// Função que efetivamente faz o emprestimo
int fazerEmprestimo(lista_usuario *listaUsuarios, listaFilas *listaControl, lista_livro *listaLivros, int codLivro, int matricula) {
    usuario *localUsuario = buscarUsuario(listaUsuarios, matricula);
    livro *localNo = buscarLivroPorCodigo(listaLivros, codLivro);

    // Verifica se o usuário ou livro não existirem, retorne falha
    if (localUsuario == NULL) {
        printf("Erro: Usuario com matricula %d nao encontrado.\n", matricula);
        return 0;
    }
    if (localNo == NULL) {
        printf("Erro: Livro com codigo %d nao encontrado.\n", codLivro);
        return 0;
    }

    int slot = buscarSlotVazio(localUsuario); 
    
    if (slot == -1) {
        printf("Erro: Usuario %s ja atingiu o limite de 2 livros emprestados (Limite atingido).\n", localUsuario->nome);
        return 0; // Falha
    }
    
    if (localNo->status == 1) { 
        data dataDevolucao = calcularDataDevolucao();
        // REGISTRO DE SUCESSO: Atualiza o status e os arrays do usuário
        localNo->status = 0; // Marca o livro como emprestado (Status 0)
        // Registro na struct do usuário (usando o slot que foi encontrado)
        localUsuario->livros_emprestados[slot] = localNo;
        strcpy(localUsuario->data_devolucao[slot], dataDevolucao.dataHoje);
        // Mensagem de Sucesso
        printf("Livro '%s' emprestado para %s. Devolucao: %s\n", localNo->titulo, localUsuario->nome, dataDevolucao.dataHoje);
        return 1; // Sucesso no empréstimo (Código 1)
    } else { // 4. LIVRO INDISPONÍVEL (Status = 0): Adiciona à Fila
        // Chama a lógica de fila (colocaFila)
        int pos_fila = colocaFila(matricula, localNo, listaControl);
        
        if (pos_fila > 0) { 
            // Positivo significa posição na fila (SUCESSO)
            printf("Livro indisponivel. %s adicionado a fila na posicao %d.\n", localUsuario->nome, pos_fila);
            return -pos_fila; // Retorna NEGATIVO (Ex: -1, -2, etc.)
        } else {
            printf("Erro: Falha desconhecida ao tentar adicionar usuario a fila.\n");
            return 0; // Falha
        }
    }
}


//-----------------------------Por:Eduardo----------------------------------------------------

// Função de devolucao de livro, lida com o caso de precisar deletar a lista se so existe uma pessoa esperando e caso ha mais de uma pessoa na fila.
int devolverLivro(listaFilas *listaFilasControl, lista_livro *listaLivro, lista_usuario *listaUsuarios, int codLivro, int matricula) {
    // 1. BUSCA DE REGISTROS
    usuario *localUsuario = buscarUsuario(listaUsuarios, matricula);
    livro *localNo = buscarLivroPorCodigo(listaLivro, codLivro);

    if (localUsuario == NULL) {
        printf("Erro: Usuario com matricula %d nao encontrado.\n", matricula);
        return 0;
    }
    if (localNo == NULL) {
        printf("Erro: Livro com codigo %d nao encontrado no acervo.\n", codLivro);
        return 0;
    }
    
    // 2. TENTA REMOVER O LIVRO DO USUÁRIO (Devolução do usuário atual)
    if (removerLivroDoUsuario(localUsuario, localNo)) { 

        
        printf("Sucesso: Livro '%s' devolvido por %s.\n", localNo->titulo, localUsuario->nome);

        fila *filaEndereco = veriFila(listaFilasControl, localNo);
        
        if (filaEndereco != NULL) { // Se a fila existe
            int matricula_proximo = removerFila(filaEndereco->fila); 
            
            if (matricula_proximo > 0) {

                printf("Aviso: Usuario %d da fila foi selecionado para o emprestimo.\n", matricula_proximo);
                usuario *proximo_user = buscarUsuario(listaUsuarios, matricula_proximo);
                
                if (proximo_user != NULL) {
                    // (Disponível) -> 0 (Emprestado Novamente) 
                    
                    // Tenta registrar o empréstimo no array do novo usuário
                    int registro_sucesso = definirLivros(localNo, proximo_user); 
                    
                    if (registro_sucesso) {
                        data dataDevolucao = calcularDataDevolucao();  
                        printf("Aviso: Emprestimo automatico concluido para %s (Matricula: %d).\n", proximo_user->nome, matricula_proximo);
                        printf("Nova Devolucao: %s\n", dataDevolucao.dataHoje);
                    } else {
                        // Se falhou (limite atingido no próximo usuário), o status está 0, o que é incorreto
                        // REVERTER O STATUS (0 -> 1) E AVISAR QUE O LIVRO ESTÁ DISPONÍVEL
                        atualizarStatus(localNo);
                        printf("Aviso: Usuario %d da fila atingiu o limite de livros!.\n", matricula_proximo);
                    }
                }
                // Finaliza a transação e retorna o novo tamanho da fila
                if (FilaEstaVazia(filaEndereco->fila)) {
                     return -2; // Sucesso na devolução e fila zerada 
                }
                return filaEndereco->fila->tamanho; // Retorna o novo tamanho da fila
            }
        } 
        
        // Se não havia fila ou a fila estava vazia
        return 1; // Código 1 para sucesso na devolução (sem fila)
    }
    
    printf("Erro: Livro '%s' não estava registrado como emprestado para %s.\n", localNo->titulo, localUsuario->nome);
    return 0;
}

// Função para remover o livro emprestado do usuário
int removerLivroDoUsuario(usuario *user, livro *livro) {
    if (user == NULL || livro == NULL) return 0;
    
    // Procura o ponteiro do livro no array do usuário (slot 0 e 1)
    for (int i = 0; i < 2; i++) {
        // Verifica se o ponteiro do livro é o mesmo E se o slot está ocupado
        if (user->livros_emprestados[i] == livro) {
            // Remove o registro
            user->livros_emprestados[i] = NULL;
            user->data_devolucao[i][0] = '\0'; // Limpa a string de data
            return 1; // Sucesso na remoção
        }
    }
    return 0; // Livro não estava emprestado para este usuário
}

// Função para imprimir a fila de espera de um livro
int imprimirFilaEspera(listaFilas *lista, lista_livro *listaLivro, int codLivro) {
    livro *book = buscarLivroPorCodigo(listaLivro, codLivro);

    if (book == NULL) { 
        printf("Erro: Livro com codigo %d nao foi encontrado.\n", codLivro);
        return 0;
    } 
    
    // Procurar o nó da fila
    fila *fila_node = veriFila(lista, book); 

    // Avisa se o nó da fila NÃO EXISTE
    if (fila_node == NULL) {
        printf("Erro: Nao ha fila de espera para o livro '%s' (Cod: %d) no momento.\n", book->titulo, codLivro);
        return 1; // Sucesso: Livro existe, fila não existe.
    }

    // Imprime a Fila
    printf("Fila de espera para '%s' (Cod: %d):", book->titulo, codLivro);
    imprimirFila(fila_node->fila);
    return 1;
}