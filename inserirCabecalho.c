#include <stdio.h>

// Insere as colunas identificadoras do cabeçalho nos arquivos
void inserirCabecalhoArquivos() {
  FILE *ptrNota;
  FILE *ptrVenda;
  FILE *ptrCompra;
  FILE *ptrProdutos;
  
  ptrNota = fopen("arq_notas.txt", "w");
  ptrVenda = fopen("arq_vendas.txt", "w");
  ptrCompra = fopen("arq_compras.txt", "w");
  ptrProdutos = fopen("arq_produtos.txt", "w");

  if (ptrProdutos == NULL || ptrNota == NULL 
    || ptrVenda == NULL || ptrCompra == NULL) {
    printf("\n>>> Erro ao abrir o arquivo.\n\n");
    return;
  }
  
  fprintf(ptrProdutos, "%s\n", "Codigo|Nome|Quantidade|Valor");
  fprintf(ptrNota, "%s\n", "Numero|Tipo|Endereco|UF|Total|CNPJ");
  fprintf(ptrVenda, "%s\n", "Nota|Produto|Preco|Quantidade|Total"); 
  fprintf(ptrCompra, "%s\n", "Nota|Produto|Preco|Quantidade|Total");
  
  fclose(ptrNota);
  fclose(ptrVenda);
  fclose(ptrCompra);
  fclose(ptrProdutos);
}
