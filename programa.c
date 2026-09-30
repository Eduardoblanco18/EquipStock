#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "BibliotecaLista.h"
#include <ctype.h>

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    Lista *Labs = CriaLista();
    Equip novo;
    int resposta, codigo, prioridade;

    if (Labs == NULL)
    {
        printf("overleap\n");
        return 1;
    }

    do
    {
        printf("\n1 - Inserir lista.\n");
        printf("2 - Remover código da lista.\n");
        printf("3 - Printar lista.\n");
        printf("4 - Alterar prioridade.\n");
        printf("0 - Sair.\n");
        printf("Escolha: ");
        scanf("%d", &resposta);
        if (resposta > 4 || resposta < 0)
        {
            printf("Entrada inválida. Encerrando.\n");
            break;
        }

        switch (resposta)
        {
        case 1:
            printf("Codigo da solicitacao: ");
            scanf("%d", &novo.codigoS);
             if (isdigit(novo.codigoS))
                    {
                        if (novo.codigoS < 1000 || novo.codigoS > 9999)
                        {
                          printf("Digite um número de 1000 a 9999.\n");
                          break;
                        }
                    }



            printf("Codigo do equipamento: ");
            scanf("%s", novo.codigoE);
            char str[123];
            for (int i = 0; str[i] != '\0'; i++)
                {
                    if (isspace((unsigned char)str[i]))
                    {
                        printf("Não deve haver espaços no código");
                        break;
                    }
                }



            printf("Nome do equipamento: ");
            scanf("%s", novo.nomeEquip);
                for (int i = 0; str[i] != '\0'; i++)
                {
                    if (isdigit((unsigned char)str[i]))
                    {
                        printf("Digite apenas letras");
                        break;
                    }
                }




            printf("Qual é a prioridade: ");
            scanf("%d", &novo.prioridade);
                if (isdigit(novo.prioridade))
                    {
                        if (novo.prioridade < 1 || novo.prioridade > 3)
                        {
                          printf("O nível de prioridade deve estar entre 1 (mínimo) e 3 (máximo)");
                          break;
                        }
                    }


            printf("Período em dias: ");
            scanf("%d", &novo.periodo);

                if (isdigit(novo.periodo))
                {
                    if (novo.periodo < 1 || novo.periodo > 20)
                    {
                          printf("O período de dias deve estar entre 1 e 20 ");
                          break;
                    }
                }


            adicionarNaLista(Labs, novo);
            break;

        case 2:
            printf("Codigo da solicitação a remover: ");
            scanf("%d", &codigo);
            if (isdigit(codigo))
                    {
                        if (codigo < 1000 || codigo > 9999)
                        {
                          printf("Digite um número de 1000 a 9999.\n");
                          break;
                        }
                    }
                else
                {
                    printf("Digite apenas números");
                    break;
                }
            removerDaLista(Labs, codigo);
            break;

        case 3:
            imprimirLista(Labs);
            break;

        case 4:
            printf("Codigo da solicitacao: ");
            scanf("%d", &codigo);
            if (isdigit(codigo))
                    {
                        if (codigo < 1000 || codigo > 9999)
                        {
                          printf("Digite um número de 1000 a 9999.\n");
                          break;
                        }
                    }
                else
                {
                    printf("Digite apenas números");
                    break;
                }

            printf("Digite a nova prioridade: ");
            scanf("%d", &prioridade);
            if (isdigit(prioridade))
                    {
                        if (novo.prioridade < 1 || novo.prioridade > 3)
                        {
                          printf("O nível de prioridade deve estar entre 1 (mínimo) e 3 (máximo)");
                          break;
                        }
                    }
                else
                {
                    printf("Digite apenas números");
                        break;
                }

            alterarprioridade(Labs, codigo, prioridade);
            break;

        case 0:
            printf("Você decidiu sair.\n");
            break;

        default:
            printf("Não existe tal opção...\n");
        }
    } while (resposta != 0);

    liberarLista(Labs);
    return 0;
}
