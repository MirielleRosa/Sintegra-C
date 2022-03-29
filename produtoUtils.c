#include <stdio.h>

// Retorna o valor unitário de um produto
// Se o produto não foi cadastrado, retorna -1
float valorUnitario(int codigoProduto) {
  FILE *ptrProduto;
  
  int codigo = 0;
  char nome[50] = "";
  int quantidade = 0;
  float valor = 0;
  
  ptrProduto = fopen("arq_produtos.txt", "r");
  
  if (ptrProduto == NULL){
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return -1;
  }
  
  // Lê a linha de cabecalho do arquivo
  char linha[200];
  fgets(linha, 200, ptrProduto);
  
  while (fscanf(ptrProduto, "%d|%[^|]|%d|%f", &codigo, nome, 
    &quantidade, &valor) != EOF) {
    if (codigo == codigoProduto) {
      fclose(ptrProduto);
      return valor;
    }
  }  
  
  fclose(ptrProduto);
  
  return -1;
}

// Retorna a quantidade em estoque de um produto
int quantidadeEstoque(int codigoProduto) {
  FILE *ptrProduto;
  
  int codigo = 0;
  char nome[50] = "";
  int quantidade = 0;
  float valor = 0;
  
  ptrProduto = fopen("arq_produtos.txt", "r");
  
  if (ptrProduto == NULL){
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return 0;
  }
  
  // Lê a linha de cabecalho do arquivo
  char linha[200];
  fgets(linha, 200, ptrProduto);
  
  while (fscanf(ptrProduto, "%d|%[^|]|%d|%f", &codigo, nome, 
    &quantidade, &valor) != EOF) {
    if (codigo == codigoProduto) {
      fclose(ptrProduto);
      return quantidade;
    }
  }  

  return 0;
}

// Atualiza a quantidade em estoque
void atualizarEstoque(int codigoProduto, int qtd) {
  FILE *ptrProdutoLeitura;
  FILE *ptrProdutoEscrita;
  
  int codigo = 0;
  char nome[50] = "";
  int quantidade = 0;
  float valor = 0;

  fpos_t position;
  
  ptrProdutoLeitura = fopen("arq_produtos.txt", "r");

  // Cria um novo arquivo temporário
  ptrProdutoEscrita = fopen("arq_produtos_tmp.txt", "w");

  if (ptrProdutoEscrita == NULL || ptrProdutoLeitura == NULL){
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }

  // Insere o cabeçalho no arquivo temporário
  fprintf(ptrProdutoEscrita, "%s\n", "Codigo|Nome|Quantidade|Valor");

  // Lê a linha de cabecalho do arquivo
  char linha[200];
  fgets(linha, 200, ptrProdutoLeitura);

  // Reescreve os dados atualizados em um novo arquivo
  while (fscanf(ptrProdutoLeitura, "%d|%[^|]|%d|%f", &codigo, nome, 
    &quantidade, &valor) != EOF) {
    if (codigo == codigoProduto) {
      int novaQuantidade = quantidade + qtd;
      fprintf(ptrProdutoEscrita, "%d|%s|%d|%.2f\n", codigo, nome, 
        novaQuantidade, valor);
    } else {
      fprintf(ptrProdutoEscrita, "%d|%s|%d|%.2f\n", codigo, nome, 
        quantidade, valor);   
    }
  }  

  fclose(ptrProdutoLeitura);
  fclose(ptrProdutoEscrita);

  // Renomeia o arquivo temporário para o nome original
  rename("arq_produtos_tmp.txt", "arq_produtos.txt");
}
