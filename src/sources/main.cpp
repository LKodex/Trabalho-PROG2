#include <stdio.h>
#include <stdlib.h>
#include "../headers/alunos.h"

int main(int argc, char* argv[]) {

    AlunoList *listaAlunos = nullptr;
    char arquivo[MAX_CHAR];
    char busca[MAX_CHAR];
    int opcao;

    while (opcao != 7) {
        printf("\n%s 1.\tCadastrar novo(a) aluno(a)", APP_PREFIX);
        printf("\n%s 2.\tBuscar aluno(a)", APP_PREFIX);
        printf("\n%s 3.\tLer arquivo com listagem de alunos", APP_PREFIX);
        printf("\n%s 4.\tGerar arquivo com alunos aprovados", APP_PREFIX);
        printf("\n%s 5.\tGerar arquivo com alunos reprovados", APP_PREFIX);
        printf("\n%s 6.\tVisualizar todos alunos cadastrados", APP_PREFIX);
        printf("\n%s 7.\tSAIR", APP_PREFIX);

        printf("\n\nOpção:\t");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                /* Cadastar um novo aluno */
                Aluno tempAluno;

                printf("\n%-17s", "Nome:");
                scanf(" %[^\n]", &tempAluno.nome);

                printf("%-17s", "RA:");
                scanf("%d", &tempAluno.ra);

                printf("%-17s", "Prova 1:");
                scanf("%lf", &tempAluno.p1);

                printf("%-17s", "Prova 2:");
                scanf("%lf", &tempAluno.p2);

                printf("%-17s", "Trabalho:");
                scanf("%lf", &tempAluno.t);

                printf("%-17s", "Prova Optativa:");
                scanf("%lf", &tempAluno.po);

                cadastrarAluno(listaAlunos, tempAluno);
                break;
            case 2:
                /* Buscar alunos */
                if(!listaAlunos) {
                    printf("\n%s Não existe alunos cadastrados na lista!", APP_PREFIX);
                } else {
                    printf("\nNome do aluno:\t");
                    scanf(" %[^\n]", &busca);

                    buscarAluno(listaAlunos, busca);
                }
                break;
            case 3:
                /* Ler arquivo com listagem de alunos */
                printf("\nNome do arquivo:\t");
                scanf("%s", arquivo);
                desalocar(listaAlunos);
                listaAlunos = lerArquivo(arquivo);
                if (!listaAlunos) {
                    printf("\n\n%s ERRO! Houve um erro ao ler o arquivo <%s>!\n", APP_PREFIX, arquivo);
                } else {
                    printf("\n%s Arquivo lido com sucesso!\n", APP_PREFIX);
                }
                break;
            case 4:
                /* Gerar arquivo com dados de alunos aprovados */
                salvarAprovados(listaAlunos);
                break;
            case 5:
                /* Gerar arquivo com dados de alunos reprovados */
                salvarReprovados(listaAlunos);
                break;
            case 6:
                /* Mostrar todos alunos cadastrados na memória */
                imprimir(listaAlunos);
                printf("\n");
                break;
            case 7:
                /* Salvar e sair do programa */
                salvarAtual(listaAlunos);
                desalocar(listaAlunos);
                printf("\n%s Saindo do programa...\n", APP_PREFIX);
                break;
            default:
                printf("\n%s Por favor selecione uma opção de 1 a 7\n", APP_PREFIX);
        }
    }
    printf("\nPrograma finalizado! Até breve\n");

    return 0;
}
