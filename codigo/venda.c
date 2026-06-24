#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

void salvarVendas(Venda vendas[], int totalVendas) {
    FILE *arq = fopen("vendas.bin", "wb");
    if (arq == NULL) {
        printf("Erro ao salvar vendas.\n");
        return;
    }
    fwrite(&totalVendas, sizeof(int), 1, arq);
    fwrite(vendas, sizeof(Venda), totalVendas, arq);
    fclose(arq);
}

int carregarVendas(Venda vendas[]) {
    int total = 0;
    FILE *arq = fopen("vendas.bin", "rb");
    if (arq == NULL)
        return 0;
    fread(&total, sizeof(int), 1, arq);
    fread(vendas, sizeof(Venda), total, arq);
    fclose(arq);
    return total;
}

int buscarVenda(Venda vendas[], int total, int codigoVenda) {
    int i;
    for (i = 0; i < total; i++) {
        if (vendas[i].codigoVenda == codigoVenda)
            return i;
    }
    return -1;
}

int buscarCliente(Cliente clientes[], int total, int codigo);
int buscarProduto(Produto produtos[], int total, int codigo);

void cadastrarVenda(Venda vendas[], int *totalVendas,
                    Cliente clientes[], int totalClientes,
                    Produto produtos[], int totalProdutos) {
    int codigoVenda, codigoCliente, codigoProduto;
    if (*totalVendas >= MAX) {
        printf("Limite de vendas atingido.\n");
        return;
    }
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    if (buscarVenda(vendas, *totalVendas, codigoVenda) != -1) {
        printf("Codigo ja cadastrado.\n");
        return;
    }
    printf("Codigo do cliente: ");
    scanf("%d", &codigoCliente);
    getchar();
    if (buscarCliente(clientes, totalClientes, codigoCliente) == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    printf("Codigo do produto: ");
    scanf("%d", &codigoProduto);
    getchar();
    if (buscarProduto(produtos, totalProdutos, codigoProduto) == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }
    vendas[*totalVendas].codigoVenda   = codigoVenda;
    vendas[*totalVendas].codigoCliente = codigoCliente;
    vendas[*totalVendas].codigoProduto = codigoProduto;
    printf("Quantidade: ");
    scanf("%d", &vendas[*totalVendas].quantidade);
    getchar();
    printf("Data (DD/MM/AAAA): ");
    fgets(vendas[*totalVendas].data, 11, stdin);
    vendas[*totalVendas].data[strcspn(vendas[*totalVendas].data, "\n")] = '\0';
    printf("Valor total: ");
    scanf("%f", &vendas[*totalVendas].valorTotal);
    getchar();
    printf("Forma de pagamento: ");
    fgets(vendas[*totalVendas].formaPagamento, 30, stdin);
    vendas[*totalVendas].formaPagamento[strcspn(vendas[*totalVendas].formaPagamento, "\n")] = '\0';
    (*totalVendas)++;
    printf("Venda cadastrada com sucesso.\n");
}

void consultarVenda(Venda vendas[], int totalVendas,
                    Cliente clientes[], int totalClientes,
                    Produto produtos[], int totalProdutos) {
    int codigoVenda, pos, posC, posP;
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    pos = buscarVenda(vendas, totalVendas, codigoVenda);
    if (pos == -1) {
        printf("Venda nao encontrada.\n");
        return;
    }
    printf("Cod.Venda  : %d\n",      vendas[pos].codigoVenda);
    printf("Data       : %s\n",      vendas[pos].data);
    printf("Quantidade : %d\n",      vendas[pos].quantidade);
    printf("Valor total: R$ %.2f\n", vendas[pos].valorTotal);
    printf("Pagamento  : %s\n",      vendas[pos].formaPagamento);
    posC = buscarCliente(clientes, totalClientes, vendas[pos].codigoCliente);
    if (posC != -1)
        printf("Cliente    : %s\n", clientes[posC].nome);
    posP = buscarProduto(produtos, totalProdutos, vendas[pos].codigoProduto);
    if (posP != -1)
        printf("Produto    : %s\n", produtos[posP].nome);
}

void alterarVenda(Venda vendas[], int totalVendas,
                  Cliente clientes[], int totalClientes,
                  Produto produtos[], int totalProdutos) {
    int codigoVenda, pos, campo;
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    pos = buscarVenda(vendas, totalVendas, codigoVenda);
    if (pos == -1) {
        printf("Venda nao encontrada.\n");
        return;
    }
    printf("1. Quantidade\n2. Data\n3. Valor total\n4. Forma de pagamento\n5. Cliente\n6. Produto\nCampo: ");
    scanf("%d", &campo);
    getchar();
    switch (campo) {
        case 1:
            printf("Nova quantidade: ");
            scanf("%d", &vendas[pos].quantidade);
            getchar();
            break;
        case 2:
            printf("Nova data (DD/MM/AAAA): ");
            fgets(vendas[pos].data, 11, stdin);
            vendas[pos].data[strcspn(vendas[pos].data, "\n")] = '\0';
            break;
        case 3:
            printf("Novo valor total: ");
            scanf("%f", &vendas[pos].valorTotal);
            getchar();
            break;
        case 4:
            printf("Nova forma de pagamento: ");
            fgets(vendas[pos].formaPagamento, 30, stdin);
            vendas[pos].formaPagamento[strcspn(vendas[pos].formaPagamento, "\n")] = '\0';
            break;
        case 5: {
            int novoCod;
            printf("Novo codigo do cliente: ");
            scanf("%d", &novoCod);
            getchar();
            if (buscarCliente(clientes, totalClientes, novoCod) == -1) {
                printf("Cliente nao encontrado.\n");
                return;
            }
            vendas[pos].codigoCliente = novoCod;
            break;
        }
        case 6: {
            int novoCod;
            printf("Novo codigo do produto: ");
            scanf("%d", &novoCod);
            getchar();
            if (buscarProduto(produtos, totalProdutos, novoCod) == -1) {
                printf("Produto nao encontrado.\n");
                return;
            }
            vendas[pos].codigoProduto = novoCod;
            break;
        }
        default:
            printf("Campo invalido.\n");
            return;
    }
    printf("Venda alterada com sucesso.\n");
}

void removerVenda(Venda vendas[], int *totalVendas) {
    int codigoVenda, pos, i;
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    pos = buscarVenda(vendas, *totalVendas, codigoVenda);
    if (pos == -1) {
        printf("Venda nao encontrada.\n");
        return;
    }
    for (i = pos; i < *totalVendas - 1; i++)
        vendas[i] = vendas[i + 1];
    (*totalVendas)--;
    printf("Venda removida com sucesso.\n");
}

void menuVendas(Venda vendas[], int *totalVendas,
                Cliente clientes[], int totalClientes,
                Produto produtos[], int totalProdutos) {
    int opcao;
    do {
        printf("\nVENDAS\n");
        printf("1. Cadastrar\n2. Consultar\n3. Alterar\n4. Remover\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1: cadastrarVenda(vendas, totalVendas, clientes, totalClientes, produtos, totalProdutos); break;
            case 2: consultarVenda(vendas, *totalVendas, clientes, totalClientes, produtos, totalProdutos); break;
            case 3: alterarVenda(vendas, *totalVendas, clientes, totalClientes, produtos, totalProdutos);   break;
            case 4: removerVenda(vendas, totalVendas);                                                      break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}
