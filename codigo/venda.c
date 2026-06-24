#include <stdio.h>
#include "estruturas.h"

#define MAX 5

void menuVenda(Venda vendas[], int *totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos) {
    int opcao;
    do {
        printf("\n--- MENU VENDAS ---\n");
        printf("1. Registrar Nova Venda\n");
        printf("2. Consultar Venda\n");
        printf("3. Alterar Venda\n");
        printf("4. Cancelar/Remover Venda\n");
        printf("5. Listar Todas as Vendas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Funcao Registrar Venda em desenvolvimento...\n");
                break;
            case 2:
                printf("Funcao Consultar Venda em desenvolvimento...\n");
                break;
            case 3:
                printf("Funcao Alterar Venda em desenvolvimento...\n");
                break;
            case 4:
                printf("Funcao Remover Venda em desenvolvimento...\n");
                break;
            case 5:
                printf("Funcao Listar Vendas em desenvolvimento...\n");
                break;
            case 0:
                printf("\nVoltando ao Menu Principal...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);
}