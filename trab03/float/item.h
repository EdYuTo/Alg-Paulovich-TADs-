//EDSON YUDI TOMA 9791305

#ifndef ITEM_H
#define ITEM_H

typedef struct ITEM {
   int row;
   int col;
   float valor;//o valor foi colocado como float, pois o pdf cita insercao de numeros reais...
} ITEM;

ITEM *criar_item(int row, int col, float valor);
void apagar_item(ITEM **item);
void imprimir_item(ITEM *item);

#endif
