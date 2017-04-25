//EDSON YUDI TOMA 9791305

#ifndef ITEM_H
#define ITEM_H

typedef struct ITEM {
   int row;
   int col;
   float valor;
} ITEM;

ITEM *criar_item(int row, int col, float valor);
void apagar_item(ITEM **item);
void imprimir_item(ITEM *item);

#endif
