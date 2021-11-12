#include <stdio.h> // Files
#include <stdlib.h> // Memory (Chained Lists)
#include <string.h> // String comparations

#include "../headers/alunos.h"

#define ATUAL "atual.txt"
#define APROVADOS "aprovados.txt"
#define REPROVADOS "reprovados.txt"

/**
 *  Tive que refatorar esse código antes do que eu esperava :(
 */
void cadastrarAluno(AlunoList *&lista, Aluno aluno) {
    AlunoList *novo = nullptr;
    AlunoList *prev = nullptr;
    AlunoList *celula = lista;

    novo = (AlunoList *)(malloc(sizeof(AlunoList)));
    novo->aluno = aluno;
    novo->next = nullptr;

    // Inicializa a lista se ela estiver vazia
    if(!lista){
        lista = novo;
        return;
    }

    // Insere o aluno na primeira posição caso seja o primeiro na ordem lexicografica
    if (strcmp(novo->aluno.nome, celula->aluno.nome) == -1) {
        novo->next = celula;
        lista = novo;
        return;
    }

    // Avança as células até ???
    while(celula != nullptr) {
        if (strcmp(novo->aluno.nome, celula->aluno.nome) == 1) {
            prev = celula;
            celula = celula->next;
        } else {
            break;
        }
    }
    
    // Insere na ordem numérica do RA
    while(celula != nullptr) {
        if (strcmp(novo->aluno.nome, celula->aluno.nome) == 0 && novo->aluno.ra > celula->aluno.ra) {
            prev = celula;
            celula = celula->next;
        } else {
            break;
        }
    }
    // FUNCIONA PARA LEXICOGRAFICAMENTE MAIOR E ORDENADO POR RA
    novo->next = celula;
    prev->next = novo;
}

AlunoList *buscarAluno(AlunoList *&lista, char nome[MAX_CHAR]) {
    AlunoList *listaCelula = nullptr;
    AlunoList *busca = nullptr;
    AlunoList *buscaCelula = nullptr;
    int count = 0;

    listaCelula = lista;

    while (listaCelula != nullptr) {
        if (strcmp(listaCelula->aluno.nome, nome) != 0) {
            count++;
            buscaCelula = (AlunoList *)(malloc(sizeof(AlunoList)));

            // Guarda a referência da lista para ser retornada depois
            if (busca == nullptr) {
                busca = (AlunoList *)(malloc(sizeof(AlunoList)));
                busca->aluno = listaCelula->aluno;
                buscaCelula = busca;
            } else {
                // Guarda os próximos elementos conforme necessário
                buscaCelula->next = (AlunoList *)(malloc(sizeof(AlunoList)));
                buscaCelula = buscaCelula->next;
                buscaCelula->aluno = listaCelula->aluno;
            }
        }
    }
    return busca;
}

// Files
AlunoList *lerArquivo(char fileName[MAX_CHAR]) {
    FILE *arquivo = nullptr;
    AlunoList *lista = nullptr;
    Aluno aluno;
    int aux = 0;
    int count = 0;

    // Caso não seja digitado o nome do arquivo ele escolhe o arquivo atual.txt por padrão
    if (strcmp(fileName, "") == 0) {
        printf("\n>>> Arquivo não específicado, utilizando o arquivo padrão [%s]", ATUAL);
        strcpy(fileName, ATUAL);
    }

    arquivo = fopen(fileName, "r");
    // Se o arquivo falhar em abrir é retornado um null pointer
    if (!arquivo){
        // MSG ERRO
        return nullptr;
    }

    while(feof(arquivo) == 0) {
        fscanf(arquivo, "%[^0-9] %d %lf %lf %lf %lf", &aluno.nome, &aluno.ra, &aluno.p1, &aluno.p2, &aluno.t, &aluno.po);
        aux = 0;
        while(aluno.nome[aux] != '\0') {
            aux++;
        }
        aluno.nome[--aux] = '\0';
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
    FILE *arquivo = nullptr;
    AlunoList *celula = nullptr;
    double mediaFinal = 0;
    int count = 0;

    arquivo = fopen(APROVADOS, "w");

    if (!arquivo) {
        printf("\n%s ERRO! Houve um erro ao salvar lista de aprovados!\n", APP_PREFIX);
        return;
    }
    
    for (celula = lista; celula != nullptr; celula = celula->next) {
        mediaFinal = calcularMediaFinal(celula->aluno);
        if (mediaFinal >= 6){
            fprintf(arquivo, "%-30s %d\t%.1lf\n", celula->aluno.nome, celula->aluno.ra, mediaFinal);
            count++;
        }
    }
    fprintf(arquivo, "Total: %d", count);
    fclose(arquivo);
    printf("\n%s %d alunos aprovados salvo no arquivo <%s>\n", APP_PREFIX, count, APROVADOS);
}

void salvarReprovados(AlunoList *&lista) {
    FILE *arquivo = nullptr;
    AlunoList *celula = nullptr;
    double mediaFinal = 0;
    int count = 0;

    arquivo = fopen(REPROVADOS, "w");

    if (!arquivo) {
        printf("\n%s ERRO! Houve um erro ao salvar lista de reprovados!\n", APP_PREFIX);
        return;
    }

    for (celula = lista; celula != nullptr; celula = celula->next) {
        mediaFinal = calcularMediaFinal(celula->aluno);
        if (mediaFinal < 6){
            fprintf(arquivo, "%-30s %d\t%.1lf\n", celula->aluno.nome, celula->aluno.ra, mediaFinal);
            count++;
        }
    }
    fprintf(arquivo, "Total: %d", count);
    fclose(arquivo);
    printf("\n%s %d alunos reprovados salvo no arquivo <%s>\n", APP_PREFIX, count, REPROVADOS);
}

void salvarAtual(AlunoList *&lista) {
    FILE *arquivo = nullptr;
    AlunoList *celula = nullptr;

    celula = lista;
    arquivo = fopen(ATUAL, "w");
    // Se o arquivo falhar em abrir é retornado false para indicar a falha ao salvar os dados
    if (!arquivo){
        printf("\n%s ERRO! Houve um erro ao salvar lista dos alunos atualmente cadastrados na memória!\n", APP_PREFIX);
        return;
    }

    while(celula != nullptr) {
        fprintf(arquivo, "%s %d %.1f %.1f %.1f %.1f", celula->aluno.nome, celula->aluno.ra, celula->aluno.p1, celula->aluno.p2, celula->aluno.t, celula->aluno.po);
        if (celula->next != nullptr){ fprintf(arquivo, "\n"); }
        
        celula = celula->next;
    }
    fclose(arquivo);
    printf("\n%s Todos alunos salvos na memória foram cadastrados no arquivo <%s>\n", APP_PREFIX, ATUAL);
}

// Utils
double calcularMediaFinal(Aluno aluno) {
    // 1. Verifica se a nota da PO é maior que a nota da P1 ou P2
    if (aluno.po > aluno.p1 || aluno.po > aluno.p2) {
        if (aluno.po > aluno.p1) {
            aluno.p1 = aluno.po;
        } else {
            aluno.p2 = aluno.po;
        }
    }
    
    // 2. Calcula e retorna a média final
    // MF = 0,35 * P1 + 0,35 * P2 + 0,3 * T,
    return (aluno.p1 * 0.35) + (aluno.p2 * 0.35) + (aluno.t * 0.3);
}

void desalocar(AlunoList *&lista) {
    AlunoList *prox = lista;

    while (prox != nullptr) {
        lista = prox;
        prox = lista->next;
        free(lista);
    }
}

// DEBUG
void imprimir(AlunoList *&lista) {
    AlunoList *prox = lista;

    while (prox != nullptr) {
        printf("\nNome: %-31s | RA:%7d | P1:%7.1f | P2:%7.1f | T:%7.1f | PO:%7.1f", prox->aluno.nome, prox->aluno.ra, prox->aluno.p1, prox->aluno.p2, prox->aluno.t, prox->aluno.po);
        prox = prox->next;
    }
}
