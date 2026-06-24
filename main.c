#include <stdio.h>
#include <string.h>

#define MAX 5

// estrutura do cliente
typedef struct {
    int codigo;
    char nome[100];
    char cpf[20];
    char email[100];
    char telefone[20];
    char cidade[60];
} Cliente;

// estrutura do produto
typedef struct {
    int codigo;
    char nome[100];
    char categoria[60];
    char marca[60];
    float preco;
    int quantidadeEstoque;
} Produto;

// estrutura da venda
typedef struct {
    int codigoVenda;
    int codigoCliente;
    int codigoProduto;
    int quantidade;
    char data[11];
    float valorTotal;
    char formaPagamento[30];
} Venda;

// prototipos das funcoes
void menuClientes(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas);
void menuProdutos(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas);
void menuVendas(Venda vendas[], int *totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos);
void listarClientes(Cliente clientes[], int totalClientes);
void listarProdutos(Produto produtos[], int totalProdutos);
void listarVendas(Venda vendas[], int totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos);

int main() {
    Cliente clientes[MAX];
    Produto produtos[MAX];
    Venda vendas[MAX];
    int totalClientes = 0, totalProdutos = 0, totalVendas = 0;
    int opcao;

    do {
        printf("\n--- SISTEMA DE VENDAS - HARDWARE E INFORMATICA ---\n");
        printf("1 - Gerenciar Clientes\n");
        printf("2 - Gerenciar Produtos\n");
        printf("3 - Gerenciar Vendas\n");
        printf("4 - Listar Clientes\n");
        printf("5 - Listar Produtos\n");
        printf("6 - Listar Vendas\n");
        printf("0 - Sair\n");
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
            case 6:
                listarVendas(vendas, totalVendas, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
