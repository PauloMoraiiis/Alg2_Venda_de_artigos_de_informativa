#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

void menuCliente(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas);
void menuProduto(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas);
void menuVenda(Venda vendas[], int *totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos);

int main() {
    Cliente clientes[MAX];
    Produto produtos[MAX];
    Venda vendas[MAX];
    int totalClientes = 0;
    int totalProdutos = 0;
    int totalVendas = 0;

  int opcao;
    do {
        printf("SISTEMA DE VENDAS DE ARTIGOS DE INFORMÁTICA\n");
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Produtos\n");
        printf("3. Gerenciar Vendas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuCliente(clientes, &totalClientes, vendas, totalVendas);
                break;
            case 2:
                menuProduto(produtos, &totalProdutos, vendas, totalVendas);
                break;
            case 3:
                menuVenda(vendas, &totalVendas, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}
