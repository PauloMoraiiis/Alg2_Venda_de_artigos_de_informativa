#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    int codigo;
    char nome[100];
    char cpf[20];
    char email[100];
    char telefone[20];
    char cidade[60];
} Cliente;

typedef struct {
    int codigo;
    char nome[100];
    char categoria[60];
    char marca[60];
    float preco;
    int quantidadeEstoque;
} Produto;

typedef struct {
    int codigoVenda;
    int codigoCliente;
    int codigoProduto;
    int quantidade;
    char data[11];
    float valorTotal;
    char formaPagamento[30];
} Venda;

int buscarCliente(Cliente clientes[], int total, int codigo);
int buscarProduto(Produto produtos[], int total, int codigo);

// busca venda pelo codigo
int buscarVenda(Venda vendas[], int total, int codigoVenda) {
    int i;
    for (i = 0; i < total; i++) {
        if (vendas[i].codigoVenda == codigoVenda)
            return i;
    }
    return -1;
}

// cadastra uma venda
void cadastrarVenda(Venda vendas[], int *totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos) {
    int codigoVenda, codigoCliente, codigoProduto;
    if (*totalVendas >= MAX) {
        printf("Limite de vendas atingido!\n");
        return;
    }
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    if (buscarVenda(vendas, *totalVendas, codigoVenda) != -1) {
        printf("Esse codigo ja existe!\n");
        return;
    }
    printf("Codigo do cliente: ");
    scanf("%d", &codigoCliente);
    getchar();
    if (buscarCliente(clientes, totalClientes, codigoCliente) == -1) {
        printf("Cliente nao encontrado!\n");
        return;
    }
    printf("Codigo do produto: ");
    scanf("%d", &codigoProduto);
    getchar();
    if (buscarProduto(produtos, totalProdutos, codigoProduto) == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    vendas[*totalVendas].codigoVenda = codigoVenda;
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
    printf("Venda cadastrada com sucesso!\n");
}

// consulta uma venda pelo codigo
void consultarVenda(Venda vendas[], int totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos) {
    int codigoVenda, pos, p;
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    pos = buscarVenda(vendas, totalVendas, codigoVenda);
    if (pos == -1) {
        printf("Venda nao encontrada!\n");
        return;
    }
    printf("Codigo da venda: %d\n", vendas[pos].codigoVenda);
    printf("Data: %s\n", vendas[pos].data);
    printf("Quantidade: %d\n", vendas[pos].quantidade);
    printf("Valor total: %.2f\n", vendas[pos].valorTotal);
    printf("Pagamento: %s\n", vendas[pos].formaPagamento);
    p = buscarCliente(clientes, totalClientes, vendas[pos].codigoCliente);
    if (p != -1)
        printf("Cliente: %s\n", clientes[p].nome);
    p = buscarProduto(produtos, totalProdutos, vendas[pos].codigoProduto);
    if (p != -1)
        printf("Produto: %s\n", produtos[p].nome);
}

// altera dados de uma venda
void alterarVenda(Venda vendas[], int totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos) {
    int codigoVenda, pos, campo, novoCod;
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    pos = buscarVenda(vendas, totalVendas, codigoVenda);
    if (pos == -1) {
        printf("Venda nao encontrada!\n");
        return;
    }
    printf("Qual campo alterar?\n");
    printf("1-Quantidade 2-Data 3-Valor 4-Pagamento 5-Cliente 6-Produto\n");
    printf("Opcao: ");
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
        case 5:
            printf("Novo codigo do cliente: ");
            scanf("%d", &novoCod);
            getchar();
            if (buscarCliente(clientes, totalClientes, novoCod) == -1) {
                printf("Cliente nao encontrado!\n");
                return;
            }
            vendas[pos].codigoCliente = novoCod;
            break;
        case 6:
            printf("Novo codigo do produto: ");
            scanf("%d", &novoCod);
            getchar();
            if (buscarProduto(produtos, totalProdutos, novoCod) == -1) {
                printf("Produto nao encontrado!\n");
                return;
            }
            vendas[pos].codigoProduto = novoCod;
            break;
        default:
            printf("Campo invalido!\n");
            return;
    }
    printf("Venda alterada!\n");
}

// remove uma venda do vetor
void removerVenda(Venda vendas[], int *totalVendas) {
    int codigoVenda, pos, i;
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    getchar();
    pos = buscarVenda(vendas, *totalVendas, codigoVenda);
    if (pos == -1) {
        printf("Venda nao encontrada!\n");
        return;
    }
    for (i = pos; i < *totalVendas - 1; i++)
        vendas[i] = vendas[i + 1];
    (*totalVendas)--;
    printf("Venda removida!\n");
}

// lista todas as vendas
void listarVendas(Venda vendas[], int totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos) {
    int i, p;
    if (totalVendas == 0) {
        printf("Nenhuma venda cadastrada.\n");
        return;
    }
    for (i = 0; i < totalVendas; i++) {
        printf("\nCodigo da venda: %d\n", vendas[i].codigoVenda);
        printf("Data: %s\n", vendas[i].data);
        printf("Quantidade: %d\n", vendas[i].quantidade);
        printf("Valor total: %.2f\n", vendas[i].valorTotal);
        printf("Pagamento: %s\n", vendas[i].formaPagamento);
        p = buscarCliente(clientes, totalClientes, vendas[i].codigoCliente);
        if (p != -1)
            printf("Cliente: %s\n", clientes[p].nome);
        p = buscarProduto(produtos, totalProdutos, vendas[i].codigoProduto);
        if (p != -1)
            printf("Produto: %s\n", produtos[p].nome);
    }
}

// menu de vendas
void menuVendas(Venda vendas[], int *totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos) {
    int opcao;
    do {
        printf("\n-- VENDAS --\n");
        printf("1-Cadastrar 2-Consultar 3-Alterar 4-Remover 5-Listar 0-Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1:
                cadastrarVenda(vendas, totalVendas, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 2:
                consultarVenda(vendas, *totalVendas, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 3:
                alterarVenda(vendas, *totalVendas, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 4:
                removerVenda(vendas, totalVendas);
                break;
            case 5:
                listarVendas(vendas, *totalVendas, clientes, totalClientes, produtos, totalProdutos);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
