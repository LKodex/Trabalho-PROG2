#pragma once

#define APP_PREFIX ">>>"

#define MAX_CHAR 31

struct Aluno {
    char nome[MAX_CHAR];
    int ra;
    double p1;
    double p2;
    double t;
    double po;
};

struct AlunoList {
    Aluno aluno;
    AlunoList *next;
};

//-- APP --//
/**
 * @brief Insere ordenado lexicograficamente o aluno na lista encadeada, caso a lista esteja vazia (nullptr) ela é inicializada com o elemento
 * 
 * @param AlunoList* lista 
 * @param Aluno aluno 
 */
void cadastrarAluno(AlunoList *&lista, Aluno aluno);

/**
 * @brief Busca todos os alunos na lista que contenham a sequencia de caracteres de nome em seu nome
 * 
 * @param AlunoList* lista
 * @param char* nome[]
 */
void buscarAluno(AlunoList *&lista, char nome[MAX_CHAR]);

//-- FILES --//
/**
 * @brief Recebe o nome de um arquivo como parametro para ser lido e retornar uma lista encadeada
 * 
 * @param char* fileName[] - Nome do arquivo
 * @return (AlunoList *) Retorna o inicio de uma lista encadeada ou nullptr em caso de erro
 */
AlunoList *lerArquivo(char fileName[MAX_CHAR]);

/**
 * @brief Salva o nome, RA e média final dos alunos aprovados em um arquivo de texto [Padrão: aprovados.txt]
 * 
 * @param AlunoList* lista 
 */
void salvarAprovados(AlunoList *&lista);

/**
 * @brief Salva o nome, RA e média final dos alunos reprovados em um arquivo de texto [Padrão: reprovados.txt]
 * 
 * @param AlunoList* lista 
 */
void salvarReprovados(AlunoList *&lista);

/**
 * @brief Salva todos os dados armazenados na lista em um arquivo de texto [Padrão: atual.txt]
 * 
 * @param AlunoList* lista 
 */
void salvarAtual(AlunoList *&lista);

//-- UTILS --//
/**
 * @brief Limpa e libera a memória préviamente alocada para a lista encadeada
 * 
 * @param AlunoList* lista 
 */
void desalocar(AlunoList *&lista);

/**
 * @brief Calcula e retorna a média final do aluno considerando a PO
 * 
 * @param Aluno aluno 
 * @return (double) Média final do aluno
 */
double calcularMediaFinal(Aluno aluno);

/**
 * @brief Imprime todos elementos da lista e seus dados na tela
 * 
 * @param AlunoList* lista 
 */
void imprimir(AlunoList *&lista);
