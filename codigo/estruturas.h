#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct {
    int  codigo;          /* Identificador único do cliente      */
    char nome[100];       /* Nome completo                       */
    char cpf[15];         /* CPF no formato 000.000.000-00       */
    char email[100];      /* Endereço de e-mail                  */
    char telefone[20];    /* Telefone com DDD                    */
    char cidade[60];      /* Cidade de residência                */
} Cliente;

typedef struct {
    int   codigo;             /* Identificador único do produto  */
    char  nome[100];          /* Nome/descrição do produto       */
    char  categoria[60];      /* Categoria (ex: Memória, SSD…)  */
    char  marca[60];          /* Fabricante/marca                */
    float preco;              /* Preço unitário de venda (R$)    */
    int   quantidadeEstoque;  /* Quantidade disponível em estoque*/
} Produto;

typedef struct {
    int   codigoVenda;        /* Identificador único da venda    */
    int   codigoCliente;      /* FK → Cliente.codigo             */
    int   codigoProduto;      /* FK → Produto.codigo             */
    int   quantidade;         /* Quantidade de itens vendidos    */
    char  data[11];           /* Data da venda  DD/MM/AAAA       */
    float valorTotal;         /* Valor total da venda (R$)       */
    char  formaPagamento[30]; /* Ex: Dinheiro, Cartão, Pix…      */
} Venda;

void menuCliente(Cliente clientes[], int *totalClientes, Venda vendas[], int totalVendas);
void menuProduto(Produto produtos[], int *totalProdutos, Venda vendas[], int totalVendas);
void menuVenda(Venda vendas[], int *totalVendas, Cliente clientes[], int totalClientes, Produto produtos[], int totalProdutos);

#endif /* ESTRUTURAS_H */
