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

    int modo_qa = 0;

    if (entrada_qa != NULL && saida_qa != NULL)
    {
        arquivo_qa = fopen(saida_qa, "w");

        if (arquivo_qa == NULL)
        {
            perror("Nao foi possivel criar saida.txt");
            return 1;
        }

        if (freopen(entrada_qa, "r", stdin) == NULL)
        {
            perror("Nao foi possivel abrir entrada.txt");
            fclose(arquivo_qa);
            return 1;
        }

#ifdef _WIN32

        if (freopen("CONOUT$", "w", stdout) == NULL)
        {
            perror("Nao foi possivel abrir console");
            fclose(arquivo_qa);
            return 1;
        }

        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        SetConsoleTitleA("EquipStock - QA");

#endif

        setvbuf(stdout, NULL, _IONBF, 0);

        modo_qa = 1;
    }

    Lista *Labs = CriaLista();

    Equip novo;

    int resposta;
    int codigo;
    int prioridade;

    if (Labs == NULL)
    {
        printf("Erro ao criar lista.\n");

        if (arquivo_qa != NULL)
            fclose(arquivo_qa);

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
            if (modo_qa && feof(stdin))
            {
#ifdef _WIN32

                clearerr(stdin);

                if (freopen("CONIN$", "r", stdin) == NULL)
                {
                    perror("Nao foi possivel voltar para o teclado");
                    break;
                }

#else

                clearerr(stdin);

                if (freopen("/dev/tty", "r", stdin) == NULL)
                {
                    perror("Nao foi possivel voltar para o teclado");
                    break;
                }

#endif

                modo_qa = 0;

                continue;
            }

            printf("\nEntrada invalida.\n");

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

            if (scanf("%d", &novo.codigoS) != 1)
            {
                printf("Codigo invalido.\n");
                break;
            }

            if (novo.codigoS < 1000 || novo.codigoS > 9999)
            {
                printf(
                    "Digite um número de 1000 a 9999.\n"
                );

                break;
            }

            printf("Codigo do equipamento: ");

            if (scanf("%6s", novo.codigoE) != 1)
            {
                printf(
                    "Codigo do equipamento invalido.\n"
                );

                break;
            }

            printf("Nome do equipamento: ");

            if (scanf("%20s", novo.nomeEquip) != 1)
            {
                printf(
                    "Nome do equipamento invalido.\n"
                );

                break;
            }

            printf("Qual é a prioridade: ");

            if (scanf("%d", &novo.prioridade) != 1)
            {
                printf("Prioridade invalida.\n");
                break;
            }

            if (
                novo.prioridade < 1 ||
                novo.prioridade > 3
            )
            {
                printf(
                    "O nível de prioridade deve estar entre 1 e 3.\n"
                );

                break;
            }

            printf("Período em dias: ");

            if (scanf("%d", &novo.periodo) != 1)
            {
                printf("Periodo invalido.\n");

                break;
            }

            if (
                novo.periodo < 1 ||
                novo.periodo > 20
            )
            {
                printf(
                    "O período de dias deve estar entre 1 e 20.\n"
                );

                break;
            }

            adicionarNaLista(
                Labs,
                novo
            );

            break;

        case 2:

            printf(
                "Codigo da solicitação a remover: "
            );

            if (scanf("%d", &codigo) != 1)
            {
                printf("Codigo invalido.\n");

                break;
            }

            if (
                codigo < 1000 ||
                codigo > 9999
            )
            {
                printf(
                    "Digite um número de 1000 a 9999.\n"
                );

                break;
            }

            removerDaLista(
                Labs,
                codigo
            );

            break;

        case 3:

            imprimirLista(
                Labs
            );

            break;

        case 4:

            printf(
                "Codigo da solicitacao: "
            );

            if (scanf("%d", &codigo) != 1)
            {
                printf(
                    "Codigo invalido.\n"
                );

                break;
            }

            if (
                codigo < 1000 ||
                codigo > 9999
            )
            {
                printf(
                    "Digite um número de 1000 a 9999.\n"
                );

                break;
            }

            printf(
                "Digite a nova prioridade: "
            );

            if (scanf("%d", &prioridade) != 1)
            {
                printf(
                    "Prioridade invalida.\n"
                );

                break;
            }

            if (
                prioridade < 1 ||
                prioridade > 3
            )
            {
                printf(
                    "O nível de prioridade deve estar entre 1 e 3.\n"
                );

                break;
            }

            alterarprioridade(
                Labs,
                codigo,
                prioridade
            );

            break;

        case 0:

            printf(
                "Você decidiu sair.\n"
            );

            break;

        default:

            printf(
                "Não existe tal opção...\n"
            );

            break;
        }

    } while (resposta != 0);

    liberarLista(
        Labs
    );

    if (arquivo_qa != NULL)
    {
        fclose(
            arquivo_qa
        );
    }

    return 0;
}
