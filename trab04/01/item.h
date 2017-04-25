#ifndef ITEM_H
#define ITEM_H

typedef struct ITEM {
   int frequencia;
   char simbolo;
} ITEM;

ITEM *criar_item(int frequencia, char simbolo);
void apagar_item(ITEM **item);
void imprimir_item(ITEM *item);

#endif
