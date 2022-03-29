#include <stdio.h>

// Retorna o tamanho do array
int length(int *arr) {
  int i = 0, length = 0;
  while (arr[i] != 0) {
    i++; 
    length++;
  }
  return length;
}

// Retorna se o array contém o elemento dado
int arrayHas(int n, int *arr) {
  int i, size = length(arr);
  for (i = 0; i < size; i++) {
    if (n == arr[i]) return 1;
  }
  return 0;
}
