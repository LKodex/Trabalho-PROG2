#include <stdio.h>
#include <stdlib.h>
#include "../headers/alunos.h"


int main(int argc, char* argv[]) {

    AlunoList *listaAlunos = nullptr;
    Aluno tempAluno;
    char arquivo[MAX_CHAR] = "";
    int opcao;
    char os;

    while (opcao != 6) {
        printf("\n%s 1.\tCadastar novo aluno", APP_PREFIX);
        printf("\n%s 2.\tBuscar aluno", APP_PREFIX);
        printf("\n%s 3.\tLer arquivo com listagem de alunos", APP_PREFIX);
        printf("\n%s 4.\tGerar arquivo com dados de alunos aprovados", APP_PREFIX);
        printf("\n%s 5.\tGerar arquivo com dados de alunos reprovados", APP_PREFIX);
        printf("\n%s 6.\tFechar programa", APP_PREFIX);

        printf("\n\nOpção:\t");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                /* Cadastar um novo aluno */
                printf("\n%-15s", "Nome:");
                scanf(" %[^\n]", &tempAluno.nome);

                printf("%-15s", "RA:");
                scanf("%d", &tempAluno.ra);

                printf("%-15s", "Prova 1:");
                scanf("%lf", &tempAluno.p1);

                printf("%-15s", "Prova 2:");
                scanf("%lf", &tempAluno.p2);

                printf("%-15s", "Trabalho:");
                scanf("%lf", &tempAluno.t);

                printf("%-15s", "Prova Optativa:");
                scanf("%lf", &tempAluno.po);

                cadastrarAluno(listaAlunos, tempAluno);
                break;
            case 2:
                /* Buscar alunos */
                if(!listaAlunos) {
                    printf("\n%s Nenhum aluno encontrado. Não existe alunos cadastrados na lista!", APP_PREFIX);
                } else {
                    // BUSCA
                }
                break;
            case 3:
                /* Ler arquivo com listagem de alunos */
                printf("\n(Ex.: entrada.txt):\nNome do arquivo:\t");
                scanf("%s", arquivo);
                desalocar(listaAlunos);
                listaAlunos = lerArquivo(arquivo);
                if (!listaAlunos) {
                    printf("\n\n%s ERRO! Falha ao ler o arquivo!\n", APP_PREFIX);
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
                salvarAtual(listaAlunos);
                desalocar(listaAlunos);
                
                printf("\n%s Saindo do programa...\n", APP_PREFIX);
                break;
            case 777:
                printf("\nDEBUG");
                imprimir(listaAlunos);
                printf("\nDEBUG\n");
            default:
                printf("\n%s Por favor selecione uma opção de 1 a 6\n", APP_PREFIX);
        }
    }

    printf("\nTenha um bom dia, até breve :)\n");

    return 0;
}
