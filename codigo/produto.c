#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

void menuProduto(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas) {
    int opcao;
    do {
        printf("\nMENU PRODUTOS\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Alterar Produto\n");
        printf("4. Remover Produto\n");
        printf("5. Listar Todos os Produtos\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Funcao Cadastrar Produto em desenvolvimento...\n");
                break;
            case 2:
                printf("Funcao Consultar Produto em desenvolvimento...\n");
                break;
            case 3:
                printf("Funcao Alterar Produto em desenvolvimento...\n");
                break;
            case 4:
                printf("Funcao Remover Produto em desenvolvimento...\n");
                break;
            case 5:
                printf("Funcao Listar Produtos em desenvolvimento...\n");
                break;
            case 0:
                printf("\nVoltando ao Menu Principal...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);
}