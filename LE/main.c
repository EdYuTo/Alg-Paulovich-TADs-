#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;
  LISTA_LIGADA *lista = criar_lista();

  for(i=0; i < 15; i++) {
    inserir_item(lista, criar_item(i,i));
  }

  printf("tamanho: %d\n", tamanho(lista));
  printf("---\n");

  for(i=0; i < 10; i++) {
    remover_item(lista, i);
  }

  printf("tamanho: %d\n", tamanho(lista));
  printf("---\n");

  imprimir(lista);
   
  imprimir_item(retornar_item(lista, 12));

  apagar_lista(lista);

  return 0;
}
