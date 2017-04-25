//EDSON YUDI TOMA --- 9791305
#include "item.h"
#include <stdlib.h>
#include <stdio.h>

ITEM *criar_item(int frequencia, char simbolo) {
   ITEM *item = (ITEM *)malloc(sizeof(ITEM));
   if(item != NULL) {
      item->frequencia = frequencia;
      item->simbolo = simbolo;
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
      printf("%c", item->simbolo);
   }
}
