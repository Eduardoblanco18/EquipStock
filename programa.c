#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "BibliotecaLista.h"

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    Lista *Coco = CriaLista();
    Equip novo;
    int resposta, codigo, prioridade;

    if (Coco == NULL)
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

            if (novo.codigoS < 1000 || novo.codigoS > 9999)
            {
                printf("Digite um número de 1000 a 9999.\n");
                break;
            }

            //Ulisses quero que mexa com as bibliotecas de string para
            //tratamento de erros aqui.
            printf("Codigo do equipamento: ");
            scanf("%s", novo.codigoE);
            

            printf("Nome do equipamento: ");
            scanf("%s", novo.nomeEquip);
                

            printf("Qual é a prioridade: ");
            scanf("%d", &novo.prioridade);
                if (novo.prioridade < 1 || novo.prioridade > 3)
                {
                    //ulisses
                    break;
                }

            printf("Período em dias: ");
            scanf("%d", &novo.periodo);
            if (novo.periodo < 1 || novo.periodo > 20)
            {
                //ulisses
                break;
            }
                

            adicionarNaLista(Coco, novo);
            break;

        case 2:
            printf("Codigo da solicitação a remover: ");
            scanf("%d", &codigo);

            if (codigo < 1000 || codigo > 9999)
            {
                printf("Digite um número de 1000 a 9999.\n");
                break;
            }
            removerDaLista(Coco, codigo);
            break;

        case 3:
            imprimirLista(Coco);
            break;

        case 4:
            printf("Codigo da solicitacao: ");
            scanf("%d", &codigo);
            if (codigo < 1000 || codigo > 9999)
            {
                printf("Digite um número de 1000 a 9999.\n");
                break;
            }                

            printf("Digite a nova prioridade: ");
            scanf("%d", &prioridade);
            if (prioridade < 1 || prioridade > 3)
            {
                printf("Prioridade inválida! as opções vão de 1 a 3.");
                break;
            }

            alterarprioridade(Coco, codigo, prioridade);
            break;

        case 0:
            printf("Você decidiu sair.\n");
            break;

        default:
            printf("Não existe tal opção...\n");
        }
    } while (resposta != 0);

    liberarLista(Coco);
    return 0;
}
