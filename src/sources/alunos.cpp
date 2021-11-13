#include <stdio.h> // Files
#include <stdlib.h> // Memory (Chained Lists)
#include <string.h> // String comparations

#include "../headers/alunos.h"

#define ATUAL "atual.txt"
#define APROVADOS "aprovados.txt"
#define REPROVADOS "reprovados.txt"

void cadastrarAluno(AlunoList *&lista, Aluno aluno) {
    AlunoList *novo;
    AlunoList *prev;
    AlunoList *celula;

    novo = (AlunoList *)(malloc(sizeof(AlunoList)));
    novo->aluno = aluno;
    novo->next = nullptr;

    // Inicializa a lista se ela estiver vazia
    if(!lista){
        lista = novo;
        return;
    }

    // Insere o aluno na primeira posição caso seja o primeiro na ordem lexicografica
    celula = lista;
    if (strcmp(novo->aluno.nome, celula->aluno.nome) == -1) {
        novo->next = celula;
        lista = novo;
        return;
    }

    // Avança as células até a célula com nome igual ou posterior a qual deve ser inserida
    while(celula != nullptr) {
        if (strcmp(novo->aluno.nome, celula->aluno.nome) == 1) {
            prev = celula;
            celula = celula->next;
        } else {
            break;
        }
    }
    
    // Insere na ordem numérica do RA caso os nomes sejam iguais
    while(celula != nullptr) {
        if (strcmp(novo->aluno.nome, celula->aluno.nome) == 0 && novo->aluno.ra > celula->aluno.ra) {
            prev = celula;
            celula = celula->next;
        } else {
            break;
        }
    }
    // Insere o novo elemento entre a celula atualmente posicionada e a anterior
    novo->next = celula;
    prev->next = novo;
}

void buscarAluno(AlunoList *&lista, char nome[MAX_CHAR]) {
    AlunoList *celula;
    AlunoList *nova = nullptr;
    AlunoList *novaCelula;
    int count;

    count = 0;
    for (celula = lista; celula != nullptr; celula = celula->next) {
        if (strstr(celula->aluno.nome, nome)) {
            if (!nova) {
                nova = (AlunoList *)(malloc(sizeof(AlunoList)));
                novaCelula = nova;
                novaCelula->aluno = celula->aluno;
            } else {
                novaCelula->next = (AlunoList *)(malloc(sizeof(AlunoList)));
                novaCelula = novaCelula->next;
                novaCelula->aluno = celula->aluno;
            }
            count++;
        }   
    }
    
    if (!nova) {
        printf("\n%s Não foram encontrados alunos!\n", APP_PREFIX);
    } else {
        imprimir(nova);
        desalocar(nova);
        printf("\n%s Total: %d\n", APP_PREFIX, count);
    }
}

//-- FILES --//
AlunoList *lerArquivo(char fileName[MAX_CHAR]) {
    FILE *arquivo;
    AlunoList *lista = nullptr;
    Aluno aluno;
    int aux;
    int count;

    arquivo = fopen(fileName, "r");
    // Se o arquivo falhar em abrir é retornado um null pointer
    if (!arquivo){
        return nullptr;
    }

    count = 0;
    while(feof(arquivo) == 0) {
        fscanf(arquivo, "%[^0-9] %d %lf %lf %lf %lf", &aluno.nome, &aluno.ra, &aluno.p1, &aluno.p2, &aluno.t, &aluno.po);
        // Remove o espaço em branco do último caractere
        for (aux = 0; aluno.nome[aux] != '\0'; aux++){ }
        aluno.nome[--aux] = '\0';
        // Remove a quebra de linha do final de cada linha
        fgetc(arquivo);
        // Para evitar retrabalho somente é chamado a função de cadastar aluno para criar e inserir ordenadamente os elementos na lista
        cadastrarAluno(lista, aluno);
        count++;
    }

    fclose(arquivo);
    printf("\n%s %d aluno(s) cadastrados com sucesso!\n", APP_PREFIX, count);
    return *&lista;
}

void salvarAprovados(AlunoList *&lista) {
    FILE *arquivo;
    AlunoList *celula;
    double mediaFinal;
    int count;

    arquivo = fopen(APROVADOS, "w");

    if (!arquivo) {
        printf("\n%s ERRO! Houve um erro ao salvar lista de aprovados!\n", APP_PREFIX);
        return;
    }
    
    count = 0;
    for (celula = lista; celula != nullptr; celula = celula->next) {
        mediaFinal = calcularMediaFinal(celula->aluno);
        if (mediaFinal >= 6){
            fprintf(arquivo, "%-30s %d\t%.1lf\n", celula->aluno.nome, celula->aluno.ra, mediaFinal);
            count++;
        }
    }
    fprintf(arquivo, "Total: %d", count);

    fclose(arquivo);
    printf("\n%s %d alunos estão aprovados e foram salvos no arquivo <%s>\n", APP_PREFIX, count, APROVADOS);
}

void salvarReprovados(AlunoList *&lista) {
    FILE *arquivo;
    AlunoList *celula;
    double mediaFinal;
    int count;

    arquivo = fopen(REPROVADOS, "w");

    if (!arquivo) {
        printf("\n%s ERRO! Houve um erro ao salvar lista de reprovados!\n", APP_PREFIX);
        return;
    }

    count = 0;
    for (celula = lista; celula != nullptr; celula = celula->next) {
        mediaFinal = calcularMediaFinal(celula->aluno);
        if (mediaFinal < 6){
            fprintf(arquivo, "%-30s %d\t%.1lf\n", celula->aluno.nome, celula->aluno.ra, mediaFinal);
            count++;
        }
    }
    fprintf(arquivo, "Total: %d", count);

    fclose(arquivo);
    printf("\n%s %d alunos estão reprovados e foram salvos no arquivo <%s>\n", APP_PREFIX, count, REPROVADOS);
}

void salvarAtual(AlunoList *&lista) {
    FILE *arquivo;
    AlunoList *celula;

    arquivo = fopen(ATUAL, "w");
    // Se o arquivo falhar em abrir é retornado false para indicar a falha ao salvar os dados
    if (!arquivo){
        printf("\n%s ERRO! Houve um erro ao salvar lista de alunos cadastrados no arquivo <%s>\n", APP_PREFIX, ATUAL);
        return;
    }

    for (celula = lista; celula != nullptr; celula = celula->next) {
        fprintf(arquivo, "%s %d %.1f %.1f %.1f %.1f", celula->aluno.nome, celula->aluno.ra, celula->aluno.p1, celula->aluno.p2, celula->aluno.t, celula->aluno.po);
        if (celula->next != nullptr) {
            fprintf(arquivo, "\n");
        }
    }
    
    fclose(arquivo);
    printf("\n%s Todos alunos salvos na memória foram cadastrados no arquivo <%s>\n", APP_PREFIX, ATUAL);
}

//-- UTILS --//
void desalocar(AlunoList *&lista) {
    AlunoList *prox;

    for(prox = lista; prox != nullptr; lista = prox){
        prox = lista->next;
        free(lista);
    }
}

double calcularMediaFinal(Aluno aluno) {
    // 1. Verifica se a nota da PO é maior que a nota da P1 ou P2
    aluno.p1 = aluno.po > aluno.p1 && aluno.po <= aluno.p2 ? aluno.po : aluno.p1;
    aluno.p2 = aluno.po > aluno.p2 && aluno.po <= aluno.p1 ? aluno.po : aluno.p2;

    // 2. Calcula e retorna a média final
    // MF = 0,35 * P1 + 0,35 * P2 + 0,3 * T,
    return (aluno.p1 * 0.35) + (aluno.p2 * 0.35) + (aluno.t * 0.3);
}

void imprimir(AlunoList *&lista) {
    AlunoList *prox;

    for (prox = lista; prox != nullptr; prox = prox->next) {
        printf("\n%s Nome: %-31s | RA: %-8d | Situacao: %-9s", APP_PREFIX, prox->aluno.nome, prox->aluno.ra, (calcularMediaFinal(prox->aluno) >= 6 ? "Aprovado" : "Reprovado"));
    }
}
