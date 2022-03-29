#include <stdio.h>
#include "produtoUtils.h"

void cadastrarProduto() {
  FILE *ptrProduto;

  int codigo;
  char nome[50];
  int quantidade;
  float valor;

  ptrProduto = fopen("arq_produtos.txt", "a");

  if (ptrProduto == NULL) { 
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }

  printf("\n------- Cadastro de Produtos -------\n");

  printf("Codigo: ");
  scanf("%d", &codigo);

  while (codigo <= 0 || valorUnitario(codigo) != -1) {
    printf("Codigo invalido ou ja registrado! Digite novamente.\n\n");
    printf("Codigo: ");
    scanf("%d", &codigo);
  }
   
  printf("Nome: ");
  getchar();
  scanf("%[^\n]s", nome);
  
  do {
    printf("Quantidade: ");
    scanf("%d", &quantidade);
  } while (quantidade <= 0);
  
  do {
    printf("Valor: ");
    scanf("%f", &valor);
  } while (valor <= 0);

  fprintf(ptrProduto, "%d|%s|%d|%.2f\n", codigo, nome, quantidade, valor);
  
  fclose(ptrProduto);
}