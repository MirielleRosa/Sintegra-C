#include <stdio.h>
#include <stdlib.h>

int validarCnpj(char *cnpj) {
  long cnpjLong = atol(cnpj);
  long cnpjAux = cnpjLong / 100;
    
  int digitoUm = 0;
  int digitoDois = 0;
  
  int somaDigitoUm = 0;
  int somaDigitoDois = 0;

  int i;
  for (i = 2; i <= 9; i++) {
    int num = cnpjAux % 10;
    
    somaDigitoUm += num * i;
    
    if (i < 9) {
      somaDigitoDois += num * (i + 1);
    } else {
      somaDigitoDois += num * 2;
    }
    
    cnpjAux /= 10;
  }
  
  for (i = 2; i <= 5; i++) {
    int num = cnpjAux % 10;
    
    somaDigitoUm += num * i;
    somaDigitoDois += num * (i + 1);
    
    cnpjAux /= 10;
  }
    
  digitoUm = 11 - (somaDigitoUm % 11);
  digitoUm = (digitoUm >= 10 ? 0 : digitoUm);

  somaDigitoDois += digitoUm * 2;
  
  digitoDois = 11 - (somaDigitoDois % 11);
  digitoDois = (digitoDois >= 10 ? 0 : digitoDois);

  int digitoVerificador = cnpjLong % 100;
  
  if ((digitoUm * 10 + digitoDois) == digitoVerificador) return 1;
  
  return 0;
}
