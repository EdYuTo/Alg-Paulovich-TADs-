#include "huffman.h"
#include <stdio.h>

int main (int argc, char *argv[ ]) {
   HEAPD *heap = criarHeap();
   NO *aux;

   for (int i = 65; i < 75; i++)
      inserir(heap, criarNO(criar_item(i, i)));
imprimir(heap);
   for (int i = 60; i < 70; i++) {
      aux = remover(heap);
      if (aux != NULL)
         imprimir_item(aux->item);
      printf("%d\n", tamanho(heap));
      apagarNO(aux);
      inserir(heap, criarNO(criar_item(i, i)));
   }
imprimir(heap);
   printf("\n");
   apagarHeap(heap);

   return 0;
}
