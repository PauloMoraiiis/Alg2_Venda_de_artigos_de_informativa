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
    int codigoVenda;
    int codigoCliente;
    int codigoProduto;
    int quantidade;
    char data[11];
    float valorTotal;
    char formaPagamento[30];
} Venda;

// funcao que busca um cliente pelo codigo e retorna a posicao no vetor
int buscarCliente(Cliente clientes[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (clientes[i].codigo == codigo)
            return i;
    }
    return -1;
}

// funcao para cadastrar um novo cliente
void cadastrarCliente(Cliente clientes[], int *totalClientes) {
    int codigo;
    if (*totalClientes >= MAX) {
        printf("Limite de clientes atingido!\n");
        return;
    }
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    if (buscarCliente(clientes, *totalClientes, codigo) != -1) {
        printf("Esse codigo ja existe!\n");
        return;
    }
    clientes[*totalClientes].codigo = codigo;
    printf("Nome: ");
    fgets(clientes[*totalClientes].nome, 100, stdin);
    clientes[*totalClientes].nome[strcspn(clientes[*totalClientes].nome, "\n")] = '\0';
    printf("CPF: ");
    fgets(clientes[*totalClientes].cpf, 20, stdin);
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
    printf("Cliente cadastrado com sucesso!\n");
}

// funcao para consultar um cliente pelo codigo
void consultarCliente(Cliente clientes[], int totalClientes) {
    int codigo, pos;
    printf("Codigo do cliente: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarCliente(clientes, totalClientes, codigo);
    if (pos == -1) {
        printf("Cliente nao encontrado!\n");
        return;
    }
    printf("Codigo: %d\n", clientes[pos].codigo);
    printf("Nome: %s\n", clientes[pos].nome);
    printf("CPF: %s\n", clientes[pos].cpf);
    printf("Email: %s\n", clientes[pos].email);
    printf("Telefone: %s\n", clientes[pos].telefone);
    printf("Cidade: %s\n", clientes[pos].cidade);
}

// funcao para alterar os dados de um cliente
void alterarCliente(Cliente clientes[], int totalClientes) {
    int codigo, pos, campo;
    printf("Codigo do cliente: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarCliente(clientes, totalClientes, codigo);
    if (pos == -1) {
        printf("Cliente nao encontrado!\n");
        return;
    }
    printf("Qual campo alterar?\n");
    printf("1-Nome 2-CPF 3-Email 4-Telefone 5-Cidade\n");
    printf("Opcao: ");
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
            fgets(clientes[pos].cpf, 20, stdin);
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
            printf("Campo invalido!\n");
            return;
    }
    printf("Cliente alterado!\n");
}

// funcao para remover um cliente
void removerCliente(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas) {
    int codigo, pos, i;
    printf("Codigo do cliente: ");
    scanf("%d", &codigo);
    getchar();
    pos = buscarCliente(clientes, *totalClientes, codigo);
    if (pos == -1) {
        printf("Cliente nao encontrado!\n");
        return;
    }
    // verifica se o cliente tem vendas
    for (i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoCliente == codigo) {
            printf("Cliente tem vendas, nao pode remover!\n");
            return;
        }
    }
    // desloca os elementos do vetor
    for (i = pos; i < *totalClientes - 1; i++)
        clientes[i] = clientes[i + 1];
    (*totalClientes)--;
    printf("Cliente removido!\n");
}

// funcao para listar todos os clientes
void listarClientes(Cliente clientes[], int totalClientes) {
    int i;
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    for (i = 0; i < totalClientes; i++) {
        printf("\nCodigo: %d\n", clientes[i].codigo);
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Email: %s\n", clientes[i].email);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Cidade: %s\n", clientes[i].cidade);
    }
}

// menu de clientes
void menuClientes(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas) {
    int opcao;
    do {
        printf("\n-- CLIENTES --\n");
        printf("1-Cadastrar 2-Consultar 3-Alterar 4-Remover 5-Listar 0-Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 1:
                cadastrarCliente(clientes, totalClientes);
                break;
            case 2:
                consultarCliente(clientes, *totalClientes);
                break;
            case 3:
                alterarCliente(clientes, *totalClientes);
                break;
            case 4:
                removerCliente(clientes, totalClientes, vendas, totalVendas);
                break;
            case 5:
                listarClientes(clientes, *totalClientes);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}
