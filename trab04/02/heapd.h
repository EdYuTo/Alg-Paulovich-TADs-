//EDSON YUDI TOMA --- 9791305
#ifndef HEAPD_H
#define HEAPD_H

#include "item.h"

typedef struct NO {
   ITEM *item;
   struct NO *pai;
   struct NO *filho_esq;//filho da heap
   struct NO *filho_dir;//filho da heap
   struct NO *filho_esq_huff;//filho da arv de huff
   struct NO *filho_dir_huff;//filho da arv de huff
} NO;

NO *criarNO(ITEM *item);
int apagarNO(NO *no);

typedef struct heapd HEAPD;

HEAPD *criarHeap();
int apagarHeap(HEAPD *heap);

int vazia(HEAPD *heapd);
int tamanho(HEAPD *heapd);
int altura(HEAPD *heapd);

void imprimir(HEAPD *heapd);

int inserir(HEAPD *heapd, NO *no);
NO *remover(HEAPD *heapd);

#endif
