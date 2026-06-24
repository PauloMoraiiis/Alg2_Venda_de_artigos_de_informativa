#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

void menuCliente(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas) {
    int opcao;
    do {
        printf("\nMENU CLIENTES\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Consultar Cliente\n");
        printf("3. Alterar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("5. Listar Todos os Clientes\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                // cadastrarCliente(clientes, totalClientes);
                printf("Funcao Cadastrar em desenvolvimento...\n");
                break;
            case 2:
                // consultarCliente(clientes, *totalClientes);
                printf("Funcao Consultar em desenvolvimento...\n");
                break;
            case 3:
                // alterarCliente(clientes, *totalClientes);
                printf("Funcao Alterar em desenvolvimento...\n");
                break;
            case 4:
                // removerCliente(clientes, totalClientes, vendas, totalVendas);
                printf("Funcao Remover em desenvolvimento...\n");
                break;
            case 5:
                // listarClientes(clientes, *totalClientes);
                printf("Funcao Listar em desenvolvimento...\n");
                break;
            case 0:
                printf("\nVoltando...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }
    } while(opcao != 0);
}
