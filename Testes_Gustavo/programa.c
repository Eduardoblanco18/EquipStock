#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BibliotecaLista.h" 


//ESSE PROGRAMA FOI FEITO POR IA PARA TESTAR A PARTE
// DO RUST , NAO ENVIE ISSO, EU MUDO O RUST CONFORME NOSSO
// PROGRAMA PRINCIPAL FOR SENDO FEITO, NAO SE PREOCUPE.

void exibirLista(Lista *L) {
    if (listaVazia(L)) {
        printf("A lista de solicitacoes esta vazia.\n");
        return;
    }
    No *aux = L->inicio;
    printf("\n--- Solicitacoes de Manutencao ---\n");
    while (aux != NULL) {
        printf("Cod. Solicitacao: %d | Cod. Equip.: %s | Nome: %s | Prioridade: %d | Periodo: %d dias\n",
               aux->info.codigoS, aux->info.codigoE, aux->info.nomeEquip, aux->info.prioridade, aux->info.periodo);
        aux = aux->prox;
    }
    printf("----------------------------------\n");
}

int main() {
    Lista *minhaLista = CriaLista();
    int controle = 1;
    int opcao;
    Equip novoEquip;
    int codRemover;

    while (controle) {
        printf("\n1 - Inserir uma Solicitacao de Manutencao\n");
        printf("2 - Remover uma Solicitacao\n");
        printf("3 - Consultar uma Solicitacao\n");
        printf("4 - Alterar a prioridade e/ou periodo\n");
        printf("5 - Exibir a ordem da realizacao\n");
        printf("6 - Exibir todas as solicitacoes\n");
        printf("0 - Finalizar\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Codigo da Solicitacao: ");
                scanf("%d", &novoEquip.codigoS);
                printf("Codigo do Equipamento (Ex: OSC023): ");
                scanf("%s", novoEquip.codigoE);
                printf("Nome do Equipamento: ");
                scanf("%20s", novoEquip.nomeEquip);
                printf("Prioridade (1, 2 ou 3): ");
                scanf("%d", &novoEquip.prioridade);
                printf("Periodo (dias): ");
                scanf("%d", &novoEquip.periodo);
                
                adicionarNaLista(minhaLista, novoEquip);
                printf("Solicitacao inserida com sucesso!\n");
                break;
                
            case 2:
                printf("Digite o Codigo da Solicitacao a ser removida: ");
                scanf("%d", &codRemover);
                removerDaLista(minhaLista, codRemover);
                break;
                
            case 3:
                printf("Funcao de consultar ainda nao implementada no main.\n");
                break;
                
            case 4:
                printf("Funcao de alterar ainda nao implementada no main.\n");
                break;
                
            case 5:
                printf("Funcao de exibir ordem ainda nao implementada no main.\n");
                break;
                
            case 6:
                exibirLista(minhaLista);
                break;
                
            case 0:
                printf("Finalizando o sistema...\n");
                controle = 0;
                break;
                
            default:
                printf("Opcao invalida!\n");
                controle = 0; 
                break;
        }
    }

    liberarLista(minhaLista);
    return 0;
}