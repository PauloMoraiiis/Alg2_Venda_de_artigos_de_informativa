#include <stdio.h>
#include <string.h>

#define MAX 5

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

// busca produto pelo codigo
int buscarProduto(Produto produtos[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo)
            return i;
    }
    return -1;
}

// cadastra um produto novo
void cadastrarProduto(Produto produtos[], int *totalProdutos) {
    int codigo;
    if (*totalProdutos >= MAX) {
        printf("Limite de produtos atingido!\n");
        return;
    }
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    if (buscarProduto(produtos, *totalProdutos, codigo) != -1) {
        printf("Esse codigo ja existe!\n");
        return;
    }
    produtos[*totalProdutos].codigo = codigo;
    printf("Nome: ");
    fgets(produtos[*totalProdutos].nome, 100, stdin);
    produtos[*totalProdutos].nome[strcspn(produtos[*totalProdutos].nome, "\n")] = '\0';
    printf("Categoria: ");
    fgets(produtos[*totalProdutos].categoria, 60, stdin);
    produtos[*totalProdutos].categoria[strcspn(produtos[*totalProdutos].categoria, "\n")] = '\0';
    printf("Marca: ");
    fgets(produtos[*totalProdutos].marca, 60, stdin);
    produtos[*totalProdutos].marca[strcspn(produtos[*totalProdutos].marca, "\n")] = '\0';
    printf("Preco: ");
    scanf("%f", &produtos[*totalProdutos].preco);
    getchar();
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[*totalProdutos].quantidadeEstoque);
    getchar();
    (*totalProdutos)++;
    printf("Produto cadastrado com sucesso!\n");
}

// consulta um produto pelo codigo
void consultarProduto(Produto produtos[], int totalProdutos) {
    int codigo, pos;
    printf("Codigo do produto: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarProduto(produtos, totalProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    printf("Codigo: %d\n", produtos[pos].codigo);
    printf("Nome: %s\n", produtos[pos].nome);
    printf("Categoria: %s\n", produtos[pos].categoria);
    printf("Marca: %s\n", produtos[pos].marca);
    printf("Preco: %.2f\n", produtos[pos].preco);
    printf("Estoque: %d\n", produtos[pos].quantidadeEstoque);
}

// altera dados de um produto
void alterarProduto(Produto produtos[], int totalProdutos) {
    int codigo, pos, campo;
    printf("Codigo do produto: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarProduto(produtos, totalProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    printf("Qual campo alterar?\n");
    printf("1-Nome 2-Categoria 3-Marca 4-Preco 5-Estoque\n");
    printf("Opcao: ");
    scanf("%d", &campo);
    getchar();
    switch (campo) {
        case 1:
            printf("Novo nome: ");
            fgets(produtos[pos].nome, 100, stdin);
            produtos[pos].nome[strcspn(produtos[pos].nome, "\n")] = '\0';
            break;
        case 2:
            printf("Nova categoria: ");
            fgets(produtos[pos].categoria, 60, stdin);
            produtos[pos].categoria[strcspn(produtos[pos].categoria, "\n")] = '\0';
            break;
        case 3:
            printf("Nova marca: ");
            fgets(produtos[pos].marca, 60, stdin);
            produtos[pos].marca[strcspn(produtos[pos].marca, "\n")] = '\0';
            break;
        case 4:
            printf("Novo preco: ");
            scanf("%f", &produtos[pos].preco);
            getchar();
            break;
        case 5:
            printf("Nova quantidade: ");
            scanf("%d", &produtos[pos].quantidadeEstoque);
            getchar();
            break;
        default:
            printf("Campo invalido!\n");
            return;
    }
    printf("Produto alterado!\n");
}

// remove um produto do vetor
void removerProduto(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas) {
    int codigo, pos, i;
    printf("Codigo do produto: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarProduto(produtos, *totalProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    // verifica se tem venda com esse produto
    for (i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoProduto == codigo) {
            printf("Produto tem vendas, nao pode remover!\n");
            return;
        }
    }
    for (i = pos; i < *totalProdutos - 1; i++)
        produtos[i] = produtos[i + 1];
    (*totalProdutos)--;
    printf("Produto removido!\n");
}

// lista todos os produtos
void listarProdutos(Produto produtos[], int totalProdutos) {
    int i;
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (i = 0; i < totalProdutos; i++) {
        printf("\nCodigo: %d\n", produtos[i].codigo);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Categoria: %s\n", produtos[i].categoria);
        printf("Marca: %s\n", produtos[i].marca);
        printf("Preco: %.2f\n", produtos[i].preco);
        printf("Estoque: %d\n", produtos[i].quantidadeEstoque);
    }
}

// menu de produtos
void menuProdutos(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas) {
    int opcao;
    do {
        printf("\n-- PRODUTOS --\n");
        printf("1-Cadastrar 2-Consultar 3-Alterar 4-Remover 5-Listar 0-Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, totalProdutos);
                break;
            case 2:
                consultarProduto(produtos, *totalProdutos);
                break;
            case 3:
                alterarProduto(produtos, *totalProdutos);
                break;
            case 4:
                removerProduto(produtos, totalProdutos, vendas, totalVendas);
                break;
            case 5:
                listarProdutos(produtos, *totalProdutos);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
