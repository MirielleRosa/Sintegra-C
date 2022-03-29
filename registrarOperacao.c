#include <stdio.h>
#include "validarCnpj.h"
#include "produtoUtils.h"

int numeroNota = 1;

void registrarOperacao(int tipo) {
  FILE *ptrNota;
  FILE *ptrEmpresa;
  FILE *ptrOperacao;
  
  int codigo;
  int quantidade;
  char endereco[100];
  char uf[2];
  char cnpj[14];

  // Quantos produtos foram informados
  int qtdProdutos = 0;

  char *tipoOperacao;

  // Tipo 1 - Venda
  if (tipo == 1) {
    ptrOperacao = fopen("arq_vendas.txt", "a");
    tipoOperacao = "Venda";
  }

  // Tipo 2 - Compra
  if (tipo == 2) {
    ptrOperacao = fopen("arq_compras.txt", "a");
    tipoOperacao = "Compra";
  }
  
  ptrNota = fopen("arq_notas.txt", "a");
  ptrEmpresa = fopen("arq_empresa.txt", "r");

  if (ptrOperacao == NULL || ptrNota == NULL || ptrEmpresa == NULL) { 
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }

  printf("\n------- Registro de %s -------\n", tipoOperacao);

  float total = 0;
  float totalItem = 0;
  
  printf("Codigo do Produto (0 para finalizar): ");
  scanf("%d", &codigo);
  
  while (codigo != 0) {
    float valorProduto = valorUnitario(codigo);
    
    if (valorProduto == -1) {
      printf("Produto nao encontrado.\n\n");
      printf("Codigo do Produto (0 para finalizar): ");
      scanf("%d", &codigo);
      continue;
    }

    int qtdEstoque = quantidadeEstoque(codigo);

    if (tipo == 1 && qtdEstoque == 0) {
      printf("Produto sem estoque.\n\n");
      printf("Codigo do Produto (0 para finalizar): ");
      scanf("%d", &codigo);
      continue;
    }
    
    printf("Quantidade: ");
    scanf("%d", &quantidade);
  
    if (tipo == 1) {
      while (quantidade <= 0 || quantidade > qtdEstoque) {
        printf("Quantidade invalida ou insuficiente! Digite novamente.\n\n");
        printf("Quantidade: ");
        scanf("%d", &quantidade);
      }
    }
    
    if (tipo == 2) {
      while (quantidade <= 0) {
        printf("Quantidade invalida! Digite novamente.\n\n");
        printf("Quantidade: ");
        scanf("%d", &quantidade);
      }
    }
    
    totalItem = quantidade * valorProduto;
    total += totalItem;
    
    if (tipo == 1) atualizarEstoque(codigo, -quantidade);
    if (tipo == 2) atualizarEstoque(codigo, quantidade);
    
    fprintf(ptrOperacao, "%d%5d%10.2f%10d%10.2f\n", 
      numeroNota, codigo, valorProduto, quantidade, totalItem);
      
    qtdProdutos++;
    
    printf("\nCodigo do Produto (0 para finalizar): ");
    scanf("%d", &codigo);
  }
  
  // Caso nao haja produtos informados 
  // o registro da operacao nao prossegue
  if (qtdProdutos > 0) {
    printf("\nEndereco: ");
    getchar();
    scanf("%[^\n]s", endereco);

    printf("UF: ");
    scanf("%s", uf);
    
    fprintf(ptrNota, "%d%5d%30s|%4s%15.2f", numeroNota, tipo, 
      endereco, uf, total);
    
    if (tipo == 1) {
      // Lê a linha de cabecalho
      char linha[200];
      fgets(linha, 200, ptrEmpresa);
      fscanf(ptrEmpresa, "%[^|]", cnpj);
    }
    
    if (tipo == 2) {
      printf("CNPJ (apenas numeros): ");
      scanf("%14s", cnpj);
            
      while (!validarCnpj(cnpj)) {
        printf("CNPJ invalido! Digite novamente.\n\n");
        printf("CNPJ (apenas numeros): ");
        scanf("%14s", cnpj);
      }
    }
    
    fprintf(ptrNota, "%20s\n", cnpj);
    
    numeroNota++;
  }
  
  fclose(ptrNota);
  fclose(ptrEmpresa);
  fclose(ptrOperacao);
}
