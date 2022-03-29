#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void inserirProduto(int codigo, int *produtos);

// REGISTRO 10 - Mestre do estabelecimento
void geraRegistro10() {
  FILE *ptrEmpresa;
  FILE *ptrSintegra;

  char cnpj[15] = "";
  char inscricaoEstadual[15] = "";
  char nomeContribuinte[36] = "";
  char municipio[31] = "";
  char uf[3] = "";
  char fax[11] = "0000000000";
  char dataInicial[9] = "20220201";
  char dataFinal[9] = "20220228";
  char codigoConvenio[2] = "2";
  char codigoOperacoes[2] = "3";
  char codigoFinalidade[2] = "1";

  ptrEmpresa = fopen("arq_empresa.txt", "r");
  ptrSintegra = fopen("arq_SINTEGRA.txt", "w");

  if (ptrEmpresa == NULL || ptrSintegra == NULL) {
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }

  // Lê a linha de cabecalho
  char linha[200];
  fgets(linha, 200, ptrEmpresa);

  fscanf(ptrEmpresa, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]", 
    cnpj, inscricaoEstadual, nomeContribuinte, municipio, uf);
  
  fprintf(ptrSintegra, "10%s%-14s%-35s%-30s%s%s%s%s%s%s%s\n", 
    cnpj, inscricaoEstadual, nomeContribuinte, municipio, uf, 
    fax, dataInicial, dataFinal, codigoConvenio, codigoOperacoes, 
    codigoFinalidade); 
    
  fclose(ptrEmpresa);
  fclose(ptrSintegra);
}

// REGISTRO 11 - Dados complementares do informante
void geraRegistro11() {
  FILE *ptrComplemento;
  FILE *ptrSintegra;

  char logradouro[36] = "";
  char numero[6] = "";
  char complemento[23] = "";
  char bairro[16] = "";
  char cep[9] = "";
  char contato[29] = "";
  char telefone[13] = "";

  ptrComplemento = fopen("arq_complemento.txt", "r");
  ptrSintegra = fopen("arq_SINTEGRA.txt", "a");

  if (ptrComplemento == NULL || ptrSintegra == NULL) {
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }
  
  // Lê a linha de cabecalho
  char linha[200];
  fgets(linha, 200, ptrComplemento);

  fscanf(ptrComplemento, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]", 
    logradouro, numero, complemento, bairro, cep, contato, telefone);
    
  // Preencher com zeros à esquerda
  sprintf(numero, "%05d", atoi(numero));
  sprintf(telefone, "%012ld", atol(telefone));
  
  fprintf(ptrSintegra, "11%-34s%s%-22s%-15s%s%-28s%s\n", 
    logradouro, numero, complemento, bairro, cep, contato, telefone);
  
  fclose(ptrComplemento);
  fclose(ptrSintegra);
}

// REGISTRO 50 - Notas fiscais de compras e vendas
void geraRegistro50() {
  FILE *ptrNota;
  FILE *ptrSintegra;

  char cnpj[15] = "";
  char inscricaoEstadual[15] = "";
  char data[9] = "20220211";
  char uf[3] = "";
  char modelo[3] = "00";
  char serie[4] = "";
  char numero[7] = "";
  char cfop[5] = "0000";
  char emitente[2] = "";
  char valorTotal[14] = "";
  char baseCalculoICMS[14] = ""; // valor total da nota
  char valorICMS[14] = "0000000000000";
  char isentaNaoTributada[14] = "0000000000000";
  char outras[14] = "0000000000000";
  char aliquota[5] = "0000";
  char situacao[2] = "N";

  // Nota
  int tipo = 0;
  char endereco[100] = "";
  
  ptrNota = fopen("arq_notas.txt", "r");
  ptrSintegra = fopen("arq_SINTEGRA.txt", "a");

  if (ptrNota == NULL || ptrSintegra == NULL) {
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }
  
  // Lê a linha de cabecalho
  char linha[200];
  fgets(linha, 200, ptrNota);

  while (fscanf(ptrNota, "%s%d%[^|]|%s%s%s", numero, 
    &tipo, endereco, uf, valorTotal, cnpj) != EOF) {

    // Preencher com zeros à esquerda
    sprintf(numero, "%06d", atoi(numero));
    sprintf(valorTotal, "%013ld", atol(valorTotal)*100);
        
    strcpy(baseCalculoICMS, valorTotal);

    if (tipo == 1) strcpy(emitente, "P"); // Venda
    if (tipo == 2) strcpy(emitente, "T"); // Compra
    
    fprintf(ptrSintegra, "50%s%-14s%s%-2s%s%-3s%s%s%s%s%s%s%s%s%s%s\n", 
      cnpj, inscricaoEstadual, data, uf, modelo, serie, numero, cfop, 
      emitente, valorTotal, baseCalculoICMS, valorICMS, isentaNaoTributada, 
      outras, aliquota, situacao);
  }  
  
  fclose(ptrNota);
  fclose(ptrSintegra);
}

// REGISTRO 54 - Itens das notas fiscais
void geraRegistro54() {
  FILE *ptrNota;
  FILE *ptrOperacao;
  FILE *ptrSintegra;

  char cnpj[15] = "";
  char modelo[3] = "00";
  char serie[4] = "";
  char numero[7] = "";
  char cfop[5] = "0000";
  char cst[4] = "";
  char numeroItem[4] = "";
  char codigoProduto[15] = "";
  char quantidade[12] = "";
  char valorProduto[13] = ""; // valor unitario x quantidade
  char valorDesconto[13] = "000000000000";
  char baseCalculoICMS[13] = ""; // valor total da nota
  char baseCalculoICMSSubstituicao[13] = "000000000000";
  char valorIPI[13] = "000000000000";
  char aliquotaICMS[5] = "0000";

  // Nota
  int tipo = 0;
  char endereco[100] = "";
  char uf[3] = "";
  char valorTotal[14] = "";
  char numeroNota[7] = "";

  // Produto
  float valorUnitario = 0;

  int countItem = 1;
 
  ptrNota = fopen("arq_notas.txt", "r");
  ptrSintegra = fopen("arq_SINTEGRA.txt", "a");
  
  if (ptrNota == NULL || ptrSintegra == NULL) {
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }
  
  // Lê a linha de cabecalho
  char linha[200];
  fgets(linha, 200, ptrNota);
  
  while (fscanf(ptrNota, "%s%d%[^|]|%s%s%s", numero, 
    &tipo, endereco, uf, valorTotal, cnpj) != EOF) {
    
    if (tipo == 1) ptrOperacao = fopen("arq_vendas.txt", "r");
    if (tipo == 2) ptrOperacao = fopen("arq_compras.txt", "r");

    if (ptrOperacao == NULL) {
      printf("\n>>> Erro ao abrir o arquivo.\n\n");
      return;
    }
        
    // Lê a linha de cabecalho
    fgets(linha, 200, ptrOperacao);
      
    while (fscanf(ptrOperacao, "%s%s%f%s%s", numeroNota, 
      codigoProduto, &valorUnitario, quantidade, valorProduto) != EOF) { 
      // Verificar se o produto pertence à nota lida
      if (atoi(numero) == atoi(numeroNota)) {  
        // Preencher com zeros à esquerda
        sprintf(numero, "%06d", atoi(numero));
        sprintf(numeroItem, "%03d", countItem);
        sprintf(quantidade, "%011ld", atol(quantidade)*1000);
        sprintf(valorProduto, "%012ld", atol(valorProduto)*100);

        strcpy(baseCalculoICMS, valorProduto);
          
        fprintf(ptrSintegra, "54%s%s%-3s%s%s%-3s%s%-14s%s%s%s%s%s%s%s\n", 
          cnpj, modelo, serie, numero, cfop, cst, numeroItem, codigoProduto, 
          quantidade, valorProduto, valorDesconto, baseCalculoICMS, 
          baseCalculoICMSSubstituicao, valorIPI, aliquotaICMS);

        countItem++;
      }  
    }
    fclose(ptrOperacao);
    countItem = 1; // Redefinir o contador de ordem do produto na nota
  }  
    
  fclose(ptrNota);
  fclose(ptrSintegra);
}

// REGISTRO 74 - Registro de inventário
void geraRegistro74() {
  FILE *ptrEmpresa;
  FILE *ptrProduto;
  FILE *ptrSintegra;

  char dataInventario[9] = "20220215";
  char codigoProduto[15] = "";
  char quantidade[14] = "";
  char valorProduto[14] = ""; // valor unitario x quantidade
  char codigoPosse[2] = "1";
  char cnpj[15] = "";
  char inscricaoEstadual[15] = "";
  char uf[3] = "";
  char brancos[46] = "";

  // Empresa
  char nomeContribuinte[36] = "";
  char municipio[31] = "";
  
  // Produto
  int codigo = 0;
  char nome[50] = "";
  float valorUnitario;

  ptrEmpresa = fopen("arq_empresa.txt", "r");
  ptrProduto = fopen("arq_produtos.txt", "r");
  ptrSintegra = fopen("arq_SINTEGRA.txt", "a");

  if (ptrEmpresa == NULL || ptrProduto == NULL || ptrSintegra == NULL) {
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }

  // Lê a linha de cabecalho
  char linha[200];
  fgets(linha, 200, ptrEmpresa);
  fgets(linha, 200, ptrProduto);

  fscanf(ptrEmpresa, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]", 
    cnpj, inscricaoEstadual, nomeContribuinte, municipio, uf);

  while (fscanf(ptrProduto, "%d|%[^|]|%[^|]|%f", &codigo, nome, 
    quantidade, &valorUnitario) != EOF) {
    // Preencher com zeros à esquerda
    sprintf(codigoProduto, "%d", codigo); 
    sprintf(quantidade, "%013ld", atol(quantidade));    
    sprintf(valorProduto, "%013ld", (long) (atol(quantidade)*valorUnitario*100));
    
    fprintf(ptrSintegra, "74%s%-14s%s%s%-1s%s%-14s%-2s%-45s\n", 
      dataInventario, codigoProduto, quantidade, valorProduto, 
      codigoPosse, cnpj, inscricaoEstadual, uf, brancos);
  }  
  
  fclose(ptrEmpresa);
  fclose(ptrProduto);
  fclose(ptrSintegra);
}

// REGISTRO 75 - Código de produtos ou serviços
void geraRegistro75() {
  FILE *ptrProduto;
  FILE *ptrVenda;
  FILE *ptrCompra;
  FILE *ptrSintegra;

  char dataInicial[9] = "20220201";
  char dataFinal[9] = "20220228";
  char codigoProduto[15] = "";
  char codigoNCM[9] = "";
  char descricao[54] = "";
  char unidadeMedida[7] = "UN";
  char aliquotaIPI[6] = "00000";
  char aliquotaICMS[5] = "0000";
  char reducaoBaseICMS[6] = "00000";
  char baseCalculoICMSSubstituicao[14] = "0000000000000";
    
  // Produto
  int codigo = 0;
  int quantidade = 0;
  float valorUnitario = 0;

  // Venda | Compra
  int numeroNota = 0;
  float valor = 0;

  // Produtos que foram comercializados
  int produtos[100] = {0};

  ptrProduto = fopen("arq_produtos.txt", "r");
  ptrVenda = fopen("arq_vendas.txt", "r");
  ptrCompra = fopen("arq_compras.txt", "r");
  ptrSintegra = fopen("arq_SINTEGRA.txt", "a");

  if (ptrProduto == NULL || ptrVenda == NULL 
    || ptrCompra == NULL || ptrSintegra == NULL) {
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }

  // Lê a linha de cabecalho
  char linha[200];
  fgets(linha, 200, ptrProduto);
  fgets(linha, 200, ptrVenda);
  fgets(linha, 200, ptrCompra);

  // Ler produtos das vendas
  while (fscanf(ptrVenda, "%d%d%f%d%f", &numeroNota, 
      &codigo, &valorUnitario, &quantidade, &valor) != EOF) { 
    inserirProduto(codigo, produtos);
  }

  // Ler produtos das compras
  while (fscanf(ptrCompra, "%d%d%f%d%f", &numeroNota, 
      &codigo, &valorUnitario, &quantidade, &valor) != EOF) { 
    inserirProduto(codigo, produtos);
  }
  
  while (fscanf(ptrProduto, "%d|%[^|]|%d|%f", &codigo, descricao, 
    &quantidade, &valorUnitario) != EOF) {
    if (arrayHas(codigo, produtos)) {
      // Preencher com zeros à esquerda
      sprintf(codigoProduto, "%d", codigo);    
      
      fprintf(ptrSintegra, "75%s%s%-14s%-8s%-53s%-6s%s%s%s%s\n", 
        dataInicial, dataFinal, codigoProduto, codigoNCM, 
        descricao, unidadeMedida, aliquotaIPI, aliquotaICMS, 
        reducaoBaseICMS, baseCalculoICMSSubstituicao);
    }
  }

  fclose(ptrProduto);
  fclose(ptrVenda);
  fclose(ptrCompra);
  fclose(ptrSintegra);
}

void gerarSintegra(int opcao) {
  geraRegistro10();
  geraRegistro11();
  geraRegistro50();
  geraRegistro54();
  if (opcao == 1) geraRegistro74();
  geraRegistro75();
  printf("\nSintegra gerado com sucesso!\n");
}

// Insere o código de um produto no array
void inserirProduto(int codigo, int *produtos) {
  int i, size = length(produtos); 
  for (i = 0; i < size; i++) {
    if (codigo == produtos[i]) return;
  }
  produtos[size] = codigo;
}
