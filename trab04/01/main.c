#include "heapd.h"
#include <stdio.h>

int main (int argc, char *argv[ ]) {
   HEAPD *heap = criarHeap();
   ITEM *aux;

   for (int i = 5; i > 0; i--)
   inserir(heap, criar_item(i,i));
   for (int i = 10; i > 5; i--)
   inserir(heap, criar_item(i,i));

   printf("tamanho = [%d]\n", tamanho(heap));
   printf("vazia? [%d]\n", vazia(heap));
   printf("altura = [%d]\n", altura(heap));
   imprimir(heap);

   for (int i = 0; i < 500; i++) {
      aux = remover(heap);
      apagar_item(&aux);
   }
   for (int i = 15; i < 20; i++)
   inserir(heap, criar_item(i, i));
   imprimir(heap);

   apagarHeap(heap);

   return 0;
}
