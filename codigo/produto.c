#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

int buscarProduto(Produto produtos[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo)
            return i;
    }
    return -1;
}

void salvarProdutos(Produto produtos[], int totalProdutos) {
    FILE *arq = fopen("produtos.bin", "wb");
    if (arq == NULL) {
        printf("Erro ao salvar produtos.\n");
        return;
    }
    fwrite(&totalProdutos, sizeof(int), 1, arq);
    fwrite(produtos, sizeof(Produto), totalProdutos, arq);
    fclose(arq);
}

int carregarProdutos(Produto produtos[]) {
    int total = 0;
    FILE *arq = fopen("produtos.bin", "rb");
    if (arq == NULL)
        return 0;
    fread(&total, sizeof(int), 1, arq);
    fread(produtos, sizeof(Produto), total, arq);
    fclose(arq);
    return total;
}

void cadastrarProduto(Produto produtos[], int *totalProdutos) {
    int codigo;
    if (*totalProdutos >= MAX) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    if (buscarProduto(produtos, *totalProdutos, codigo) != -1) {
        printf("Codigo ja cadastrado.\n");
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
    printf("Produto cadastrado com sucesso.\n");
}

void consultarProduto(Produto produtos[], int totalProdutos) {
    int codigo, pos;
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarProduto(produtos, totalProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }
    printf("Codigo   : %d\n",      produtos[pos].codigo);
    printf("Nome     : %s\n",      produtos[pos].nome);
    printf("Categoria: %s\n",      produtos[pos].categoria);
    printf("Marca    : %s\n",      produtos[pos].marca);
    printf("Preco    : R$ %.2f\n", produtos[pos].preco);
    printf("Estoque  : %d\n",      produtos[pos].quantidadeEstoque);
}

void alterarProduto(Produto produtos[], int totalProdutos) {
    int codigo, pos, campo;
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarProduto(produtos, totalProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }
    printf("1. Nome\n2. Categoria\n3. Marca\n4. Preco\n5. Estoque\nCampo: ");
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
            printf("Novo estoque: ");
            scanf("%d", &produtos[pos].quantidadeEstoque);
            getchar();
            break;
        default:
            printf("Campo invalido.\n");
            return;
    }
    printf("Produto alterado com sucesso.\n");
}

void removerProduto(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas) {
    int codigo, pos, i;
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarProduto(produtos, *totalProdutos, codigo);
    if (pos == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }
    for (i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoProduto == codigo) {
            printf("Produto possui vendas e nao pode ser removido.\n");
            return;
        }
    }
    for (i = pos; i < *totalProdutos - 1; i++)
        produtos[i] = produtos[i + 1];
    (*totalProdutos)--;
    printf("Produto removido com sucesso.\n");
}

void listarProdutos(Produto produtos[], int totalProdutos) {
    int i;
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (i = 0; i < totalProdutos; i++) {
        printf("Codigo   : %d\n",      produtos[i].codigo);
        printf("Nome     : %s\n",      produtos[i].nome);
        printf("Categoria: %s\n",      produtos[i].categoria);
        printf("Marca    : %s\n",      produtos[i].marca);
        printf("Preco    : R$ %.2f\n", produtos[i].preco);
        printf("Estoque  : %d\n",      produtos[i].quantidadeEstoque);
    }
}

void menuProdutos(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas) {
    int opcao;
    do {
        printf("\nPRODUTOS\n");
        printf("1. Cadastrar\n2. Consultar\n3. Alterar\n4. Remover\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1: cadastrarProduto(produtos, totalProdutos);                       break;
            case 2: consultarProduto(produtos, *totalProdutos);                      break;
            case 3: alterarProduto(produtos, *totalProdutos);                        break;
            case 4: removerProduto(produtos, totalProdutos, vendas, totalVendas);    break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}
