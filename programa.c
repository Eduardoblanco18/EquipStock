#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "BibliotecaLista.h"
#include <ctype.h>
#include <string.h>

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    setlocale(LC_ALL, "portuguese");

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
        system("cls");
        printf("\n1 - Inserir lista.\n");
        printf("2 - Remover solicita��o.\n");
        printf("3 - Exibir todas as solicita��es.\n");
        printf("4 - Alterar prioridade/periodo.\n");
        printf("5 - Eixibir lista de urg�ncia.\n"); // novo
        printf("6 - Consultar solicita��o.\n");     // novo
        printf("0 - Sair.\n");
        printf("Escolha: ");
        scanf("%d", &resposta);
        if (resposta > 6 || resposta < 0)
        {
            printf("Entrada inv�lida. Encerrando.\n");
            break;
        }

        switch (resposta)
        {
        case 1:
            printf("Codigo da solicitacao: ");
            if (scanf("%d", &novo.codigoS) != 1)
            {
                limpar_buffer();
                printf("Digite n�mero");
                break;
            }
            if (novo.codigoS < 1000 || novo.codigoS > 9999)
            {
                printf("Digite um n�mero de 1000 a 9999.\n");
                system("pause");
                break;
            }
            short cont = 1;
            short naosei = 1;
            do
            {
                printf("Codigo do equipamento: ");
                char name[7];
                limpar_buffer();

                memset(name, 0, sizeof(name)); // deixa todo o array com zeros
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                naosei = 1;

                if (naosei == 1)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (isblank(name[i]) == 1 || isdigit(name[i]) == 1)
                        {
                            printf("N�o deve haver espa�os ou n�meros nos 3 primeiros caracteres do c�digo\n");
                            cont = 0;
                            system("pause");
                            memset(name, 0, sizeof(name));
                            limpar_buffer();
                            naosei = 0;
                            break;
                        }
                    }
                }
                if (naosei == 1)
                {
                    for (int i = 3; i < 6; i++)
                    {
                        if (isblank(name[i]) == 1 || isalpha(name[i]) == 1)
                        {
                            printf("N�o deve haver espa�os ou letras nos �ltimos 3 caracteres do c�digo\n");
                            cont = 0;
                            system("pause");
                            memset(name, 0, sizeof(name));
                            limpar_buffer();
                            naosei = 0;
                            break;
                        }
                    }
                }

                strcpy(novo.codigoE, name);
                limpar_buffer();
                if (naosei)
                    cont = 1;
            } while (cont == 0);

            printf("Nome do equipamento: ");

            scanf("%s", novo.nomeEquip);
            char str[123];
            for (int i = 0; str[i] != '\0'; i++)
            {
                if (isblank((novo.nomeEquip[i]) != 1))
                {
                    printf("Digite apenas letras");
                    system("pause");
                    break;
                }
            }

            printf("Qual � a prioridade: ");
            scanf("%d", &novo.prioridade);
            if (isdigit(novo.prioridade))
            {
                if (novo.prioridade < 1 || novo.prioridade > 3)
                {
                    printf("O n�vel de prioridade deve estar entre 1 (m�nimo) e 3 (m�ximo)");
                    system("pause");
                    break;
                }
            }

            int controle = 1;
            do
            {
                printf("Periodo em dias: ");

                if (scanf("%d", &novo.periodo) != 1)
                {
                    limpar_buffer();
                    printf("Digite apenas numeros.\n");
                }
                else if (!periodovalido(novo.prioridade, novo.periodo))
                {
                    printf("Periodo invalido para essa prioridade.\n");

                    if (novo.prioridade == 1)
                    {
                        printf("O periodo deve estar entre 1 e 7 dias.\n");
                    }
                    else if (novo.prioridade == 2)
                    {
                        printf("O periodo deve estar entre 1 e 15 dias.\n");
                    }
                    else if (novo.prioridade == 3)
                    {
                        printf("O periodo deve estar entre 1 e 20 dias.\n");
                    }
                }
                else
                {
                    controle = 0;
                }

            } while (controle == 1);

            adicionarNaLista(Labs, novo);
            printf("\nItem adicionado com sucesso");
            system("pause");
            break;

        case 2:
            do
            {
                cont = 1;
                printf("Codigo da solicita��o a remover: ");
                if ((scanf("%d", &codigo)) != 1)
                {
                    limpar_buffer();
                    printf("Digite um n�mero v�lido.\n");
                    cont = 0;
                    system("pause");
                }
                else if (codigo < 1000 || codigo > 9999)
                {
                    printf("Digite um c�digo de 1000 a 9999.\n");
                    cont = 0;
                }

            } while (!cont); //

            removerDaLista(Labs, codigo); // se codigo nao existe tenta remover e crasha
            printf("\nRemovido com sucesso");
            system("pause");
            break;

        case 3:
            imprimirLista(Labs);
            system("pause");
            break;

        case 4:

            controle = 1;

            do
            {
                printf("Codigo da solicitacao: ");

                if (scanf("%d", &codigo) != 1)
                {
                    limpar_buffer();
                    printf("Digite apenas numeros.\n");
                }
                else if (codigo < 1000 || codigo > 9999)
                {
                    printf("Digite um codigo de 1000 a 9999.\n");
                }
                else
                {
                    controle = 0;
                }

            } while (controle == 1);

            if (!existeCodigo(Labs, codigo))
            {
                printf("\nEssa solicitacao nao existe.\n");
                system("pause");
                break;
            }

            controle = 1;
            int entrada, periodo;
            do
            {
                printf("\nO que deseja alterar?");
                printf("\n1-Somente alterar a prioridade do produto.");
                printf("\n2-Somente alterar o periodo do produto.");
                printf("\n3-Alterar a prioridade E o periodo do produto.");
                printf("\nOpcao: ");

                if (scanf("%d", &entrada) != 1)
                {
                    limpar_buffer();
                    printf("\nDigite apenas numeros.\n");
                }
                else if (entrada < 1 || entrada > 3)
                {
                    printf("\nOpcao invalida!\n");
                }
                else
                {
                    controle = 0;
                }

            } while (controle == 1);

            if (entrada == 1)
            {
                controle = 1;

                do
                {
                    printf("\nDigite a nova prioridade: ");

                    if (scanf("%d", &prioridade) != 1)
                    {
                        limpar_buffer();
                        printf("Digite apenas numeros.\n");
                    }
                    else if (prioridade < 1 || prioridade > 3)
                    {
                        printf("A prioridade deve estar entre 1 e 3.\n");
                    }
                    else
                    {
                        controle = 0;
                    }

                } while (controle == 1);

                alterarprioridade(Labs, codigo, prioridade);
            }
            else if (entrada == 2)
            {
                controle = 1;

                do
                {
                    printf("\nDigite o novo periodo: ");

                    if (scanf("%d", &periodo) != 1)
                    {
                        limpar_buffer();
                        printf("Digite apenas numeros.\n");
                    }
                    else
                    {
                        controle = 0;
                    }

                } while (controle == 1);

                alterarurgencia(Labs, codigo, periodo);
            }
            else
            {
                controle = 1;

                do
                {
                    printf("\nDigite a nova prioridade: ");

                    if (scanf("%d", &prioridade) != 1)
                    {
                        limpar_buffer();
                        printf("Digite apenas numeros.\n");
                    }
                    else if (prioridade < 1 || prioridade > 3)
                    {
                        printf("A prioridade deve estar entre 1 e 3.\n");
                    }
                    else
                    {
                        controle = 0;
                    }

                } while (controle == 1);

                controle = 1;

                do
                {
                    printf("Digite o novo periodo: ");

                    if (scanf("%d", &periodo) != 1)
                    {
                        limpar_buffer();
                        printf("Digite apenas numeros.\n");
                    }
                    else if (!periodovalido(prioridade, periodo))
                    {
                        printf("Periodo invalido para essa prioridade.\n");

                        if (prioridade == 1)
                        {
                            printf("O periodo deve estar entre 1 e 7 dias.\n");
                        }
                        else if (prioridade == 2)
                        {
                            printf("O periodo deve estar entre 1 e 15 dias.\n");
                        }
                        else
                        {
                            printf("O periodo deve estar entre 1 e 20 dias.\n");
                        }
                    }
                    else
                    {
                        controle = 0;
                    }

                } while (controle == 1);

                alterarprioridadeperiodo(Labs, codigo, prioridade, periodo);
            }

            system("pause");
            break;
        case 5:
        {
            Lista *Urgencia = criarListaUrgencia(Labs);

            printf("\nOrdem de manutencao:\n");

            imprimirLista(Urgencia);

            liberarLista(Urgencia);

            system("pause");
            break;
        }

        case 0:
            printf("Voc� decidiu sair.\n");
            break;

        default:
            printf("N�o existe tal op��o...\n");
        }
    } while (resposta != 0);

    liberarLista(Labs);
    return 0;
}
