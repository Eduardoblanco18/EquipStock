#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "BibliotecaLista.h"
#include <ctype.h>
#include <string.h>

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main()
{
    setlocale(LC_ALL, "portuguese");

    Lista *Labs = CriaLista();
    Lista *Urgencia = CriaLista();
    Equip novo;
    int resposta, codigo, prioridade;

    if (Labs == NULL)
    {
        printf("overleap\n");
        return 1;
    }

    do
    {
        system("cls");
        printf("\n1 - Inserir lista.\n");
        printf("2 - Remover solicitação.\n");
        printf("3 - Exibir todas as solicitações.\n");
        printf("4 - Alterar prioridade/periodo.\n");
        printf("5 - Eixibir lista de urgência.\n"); //novo
        printf("6 - Consultar solicitação.\n"); //novo
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
            if(scanf("%d", &novo.codigoS) != 1)
            {
               limpar_buffer();
                printf("Digite número");
                break;
            }
            if (novo.codigoS < 1000 || novo.codigoS > 9999)
            {
              printf("Digite um número de 1000 a 9999.\n");
              system("pause");
              break;
            }
    short cont = 1;
            do
            {
                          printf("Codigo do equipamento: ");
            char name[7];
             limpar_buffer();
             fgets(name,sizeof(name),stdin);
             name[strcspn(name, "\n")] = '\0';
             strcpy(novo.codigoE, name);

            for (int i = 0; novo.codigoE[i] != '\0'; i++)
                {
                    printf("%c", novo.codigoE[i]);
                    if (novo.codigoE[i] == ' ')
                    {
                        printf("Não deve haver espaços no código");
                        cont = 0;
                        system("pause");
                        limpar_buffer();
                    }
                }
            }while (!cont);





            printf("Nome do equipamento: ");

            scanf("%s", novo.nomeEquip);char str[123];
                for (int i = 0; str[i] != '\0'; i++)
                {
                    if (isblank((novo.nomeEquip)!=1))
                    {
                        printf("Digite apenas letras");
                        system("pause");
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
                          system("pause");
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
                          system("pause");
                          break;
                    }
                }


            adicionarNaLista(Labs, novo);
            printf("\nItem adicionado com sucesso");
            system("pause");
            break;

        case 2:
            do
            {
                cont =1;
                printf("Codigo da solicitação a remover: ");
                if ((scanf("%d", &codigo))!=1) 
                {
                    limpar_buffer();
                    printf("Digite um número válido.\n");
                    cont=0;
                    system("pause");

                }else
                    if (codigo < 1000 || codigo > 9999)
                    {
                        printf("Digite um código de 1000 a 9999.\n");
                        cont=0;
                        
                    }


            }while (!cont);//


            removerDaLista(Labs, codigo); //se codigo nao existe tenta remover e crasha
            printf("\nRemovido com sucesso");
            system("pause");
            break;

        case 3:
            imprimirLista(Labs);
            system("pause");
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
