//EDSON YUDI TOMA 9791305

#include "item.h"
#include <stdlib.h>
#include <stdio.h>

ITEM *criar_item(int row, int col, int valor) {
   ITEM *item = (ITEM *)malloc(sizeof(ITEM));
   if(item != NULL) {
      item->row = row;
      item->col = col;
      item->valor = valor;
   }
   return item;
}

void apagar_item(ITEM **item) {
   if(item != NULL && *item != NULL) {
      free(*item);
      *item = NULL;
   }
}

void imprimir_item(ITEM *item) {
   if(item != NULL) {
      printf("%d %d %d\n", item->row, item->col, item->valor);
 }
}
