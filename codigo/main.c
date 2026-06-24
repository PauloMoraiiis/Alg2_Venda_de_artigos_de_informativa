#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

void menuClientes(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas);
void menuProdutos(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas);
void menuVendas(Venda vendas[], int *totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos);
void listarClientes(Cliente clientes[], int totalClientes);
void listarProdutos(Produto produtos[], int totalProdutos);

int  carregarClientes(Cliente clientes[]);
void salvarClientes(Cliente clientes[], int totalClientes);
int  carregarProdutos(Produto produtos[]);
void salvarProdutos(Produto produtos[], int totalProdutos);
int  carregarVendas(Venda vendas[]);
void salvarVendas(Venda vendas[], int totalVendas);

int main() {
    Cliente clientes[MAX];
    Produto produtos[MAX];
    Venda vendas[MAX];
    int totalClientes = 0;
    int totalProdutos = 0;
    int totalVendas = 0;
    int opcao;

    totalClientes = carregarClientes(clientes);
    totalProdutos = carregarProdutos(produtos);
    totalVendas   = carregarVendas(vendas);

    do {
        printf("\nSISTEMA DE VENDAS - HARDWARE & TI\n");
        printf("1. Gerenciar Clientes\n");
        printf("2. Gerenciar Produtos\n");
        printf("3. Gerenciar Vendas\n");
        printf("4. Listar Clientes\n");
        printf("5. Listar Produtos\n");
        printf("0. Salvar e Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                menuClientes(clientes, &totalClientes, vendas, totalVendas);
                break;
            case 2:
                menuProdutos(produtos, &totalProdutos, vendas, totalVendas);
                break;
            case 3:
                menuVendas(vendas, &totalVendas, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 4:
                listarClientes(clientes, totalClientes);
                break;
            case 5:
                listarProdutos(produtos, totalProdutos);
                break;
            case 0:
                salvarClientes(clientes, totalClientes);
                salvarProdutos(produtos, totalProdutos);
                salvarVendas(vendas, totalVendas);
                printf("Dados salvos. Encerrando.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
