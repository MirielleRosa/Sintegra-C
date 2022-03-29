#include <stdio.h>
#include "geraSintegra.h"
#include "cadastroProduto.h"
#include "inserirCabecalho.h"
#include "registrarOperacao.h"

void opcoes();

void menu() {
  int opcao;

  inserirCabecalhoArquivos();
  
  do {
    opcao = 0;

    opcoes();
    
    do {
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 9);

    switch (opcao) {
      case 1:
        cadastrarProduto();
        break;
      case 2:
        registrarOperacao(1);
        break;
      case 3:
        registrarOperacao(2);
        break;
      case 4:
        gerarSintegra(1);
        break;
      case 5:
        gerarSintegra(2);
        break;
      case 0: 
        printf("\n>>> Programa encerrado.");
    } 

    printf("\n");
  } while (opcao != 0);
}

void opcoes() {
  printf("*------------------------------------*\n");
  printf("| 1. Cadastrar Produto               |\n");
  printf("| 2. Registrar Venda                 |\n");
  printf("| 3. Registrar Compra                |\n");
  printf("| 4. Gerar Sintegra                  |\n");
  printf("| 5. Gerar Sintegra - Exceto Reg. 74 |\n");
  printf("| 0. Sair                            |\n");
  printf("*------------------------------------*\n");
}
