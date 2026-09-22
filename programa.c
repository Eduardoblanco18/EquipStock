#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdarg.h>
#ifdef _WIN32
#include <windows.h>
#endif

FILE *arquivo_qa = NULL;

int imprimirQA(const char *formato, ...)
{
    va_list args, copia;
    va_start(args, formato);
    va_copy(copia, args);
    int retorno = vprintf(formato, args);
    if (arquivo_qa != NULL)
    {
        vfprintf(arquivo_qa, formato, copia);
        fflush(arquivo_qa);
    }
    va_end(copia);
    va_end(args);
    return retorno;
}

#define printf imprimirQA
#include "BibliotecaLista.h"

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    setvbuf(stdout, NULL, _IONBF, 0);

    char *entrada_qa = getenv("EQUIPSTOCK_QA_ENTRADA");
    char *saida_qa = getenv("EQUIPSTOCK_QA_SAIDA");
    if (entrada_qa != NULL && saida_qa != NULL)
    {
        arquivo_qa = fopen(saida_qa, "w");
        if (arquivo_qa == NULL || freopen(entrada_qa, "r", stdin) == NULL)
        {
            perror("Nao foi possivel iniciar o teste");
            return 1;
        }
#ifdef _WIN32
        if (freopen("CONOUT$", "w", stdout) == NULL)
        {
            perror("Nao foi possivel abrir a janela do programa");
            return 1;
        }
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        SetConsoleTitleA("EquipStock - programa.exe");
#endif
        setvbuf(stdout, NULL, _IONBF, 0);
    }

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
        if (scanf("%d", &resposta) != 1)
        {
            if (entrada_qa != NULL && saida_qa != NULL && feof(stdin))
            {
#ifdef _WIN32
                if (freopen("CONIN$", "r", stdin) == NULL)
#else
                if (freopen("/dev/tty", "r", stdin) == NULL)
#endif
                {
                    perror("Nao foi possivel ler o teclado");
                    break;
                }
                entrada_qa = NULL;
                continue;
            }
            break;
        }
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
    if (arquivo_qa != NULL)
    {
        fclose(arquivo_qa);
    }
    return 0;
}
