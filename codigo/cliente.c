#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define MAX 5

int buscarCliente(Cliente clientes[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (clientes[i].codigo == codigo)
            return i;
    }
    return -1;
}

void salvarClientes(Cliente clientes[], int totalClientes) {
    FILE *arq = fopen("clientes.bin", "wb");
    if (arq == NULL) {
        printf("Erro ao salvar clientes.\n");
        return;
    }
    fwrite(&totalClientes, sizeof(int), 1, arq);
    fwrite(clientes, sizeof(Cliente), totalClientes, arq);
    fclose(arq);
}

int carregarClientes(Cliente clientes[]) {
    int total = 0;
    FILE *arq = fopen("clientes.bin", "rb");
    if (arq == NULL)
        return 0;
    fread(&total, sizeof(int), 1, arq);
    fread(clientes, sizeof(Cliente), total, arq);
    fclose(arq);
    return total;
}

void cadastrarCliente(Cliente clientes[], int *totalClientes) {
    int codigo;
    if (*totalClientes >= MAX) {
        printf("Limite de clientes atingido.\n");
        return;
    }
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    if (buscarCliente(clientes, *totalClientes, codigo) != -1) {
        printf("Codigo ja cadastrado.\n");
        return;
    }
    clientes[*totalClientes].codigo = codigo;
    printf("Nome: ");
    fgets(clientes[*totalClientes].nome, 100, stdin);
    clientes[*totalClientes].nome[strcspn(clientes[*totalClientes].nome, "\n")] = '\0';
    printf("CPF: ");
    fgets(clientes[*totalClientes].cpf, 15, stdin);
    clientes[*totalClientes].cpf[strcspn(clientes[*totalClientes].cpf, "\n")] = '\0';
    printf("Email: ");
    fgets(clientes[*totalClientes].email, 100, stdin);
    clientes[*totalClientes].email[strcspn(clientes[*totalClientes].email, "\n")] = '\0';
    printf("Telefone: ");
    fgets(clientes[*totalClientes].telefone, 20, stdin);
    clientes[*totalClientes].telefone[strcspn(clientes[*totalClientes].telefone, "\n")] = '\0';
    printf("Cidade: ");
    fgets(clientes[*totalClientes].cidade, 60, stdin);
    clientes[*totalClientes].cidade[strcspn(clientes[*totalClientes].cidade, "\n")] = '\0';
    (*totalClientes)++;
    printf("Cliente cadastrado com sucesso.\n");
}

void consultarCliente(Cliente clientes[], int totalClientes) {
    int codigo, pos;
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarCliente(clientes, totalClientes, codigo);
    if (pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    printf("Codigo  : %d\n", clientes[pos].codigo);
    printf("Nome    : %s\n", clientes[pos].nome);
    printf("CPF     : %s\n", clientes[pos].cpf);
    printf("Email   : %s\n", clientes[pos].email);
    printf("Telefone: %s\n", clientes[pos].telefone);
    printf("Cidade  : %s\n", clientes[pos].cidade);
}

void alterarCliente(Cliente clientes[], int totalClientes) {
    int codigo, pos, campo;
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarCliente(clientes, totalClientes, codigo);
    if (pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    printf("1. Nome\n2. CPF\n3. Email\n4. Telefone\n5. Cidade\nCampo: ");
    scanf("%d", &campo);
    getchar();
    switch (campo) {
        case 1:
            printf("Novo nome: ");
            fgets(clientes[pos].nome, 100, stdin);
            clientes[pos].nome[strcspn(clientes[pos].nome, "\n")] = '\0';
            break;
        case 2:
            printf("Novo CPF: ");
            fgets(clientes[pos].cpf, 15, stdin);
            clientes[pos].cpf[strcspn(clientes[pos].cpf, "\n")] = '\0';
            break;
        case 3:
            printf("Novo email: ");
            fgets(clientes[pos].email, 100, stdin);
            clientes[pos].email[strcspn(clientes[pos].email, "\n")] = '\0';
            break;
        case 4:
            printf("Novo telefone: ");
            fgets(clientes[pos].telefone, 20, stdin);
            clientes[pos].telefone[strcspn(clientes[pos].telefone, "\n")] = '\0';
            break;
        case 5:
            printf("Nova cidade: ");
            fgets(clientes[pos].cidade, 60, stdin);
            clientes[pos].cidade[strcspn(clientes[pos].cidade, "\n")] = '\0';
            break;
        default:
            printf("Campo invalido.\n");
            return;
    }
    printf("Cliente alterado com sucesso.\n");
}

void removerCliente(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas) {
    int codigo, pos, i;
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarCliente(clientes, *totalClientes, codigo);
    if (pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    for (i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoCliente == codigo) {
            printf("Cliente possui vendas e nao pode ser removido.\n");
            return;
        }
    }
    for (i = pos; i < *totalClientes - 1; i++)
        clientes[i] = clientes[i + 1];
    (*totalClientes)--;
    printf("Cliente removido com sucesso.\n");
}

void listarClientes(Cliente clientes[], int totalClientes) {
    int i;
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    for (i = 0; i < totalClientes; i++) {
        printf("----------------------------\n");
        printf("Codigo  : %d\n", clientes[i].codigo);
        printf("Nome    : %s\n", clientes[i].nome);
        printf("CPF     : %s\n", clientes[i].cpf);
        printf("Email   : %s\n", clientes[i].email);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Cidade  : %s\n", clientes[i].cidade);
    }
}

void menuClientes(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas) {
    int opcao;
    do {
        printf("\n--- CLIENTES ---\n");
        printf("1. Cadastrar\n2. Consultar\n3. Alterar\n4. Remover\n0. Voltar\nOpcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1: cadastrarCliente(clientes, totalClientes);                       break;
            case 2: consultarCliente(clientes, *totalClientes);                      break;
            case 3: alterarCliente(clientes, *totalClientes);                        break;
            case 4: removerCliente(clientes, totalClientes, vendas, totalVendas);    break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}
