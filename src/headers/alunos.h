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

// App

void cadastrarAluno(AlunoList *&lista, Aluno aluno);

AlunoList *buscarAluno(AlunoList *&lista, char nome[MAX_CHAR]);

// Files

AlunoList *lerArquivo(char fileName[MAX_CHAR]);

void salvarAprovados(AlunoList *&lista);
void salvarReprovados(AlunoList *&lista);
void salvarAtual(AlunoList *&lista);

// Utils

double calcularMediaFinal(Aluno aluno);
void desalocar(AlunoList *&lista);

// DEBUG

void imprimir(AlunoList *&lista);
