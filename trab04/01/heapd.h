/*
#-------------------ESTRUTURA HEAP--------------------#
#  heap maximo ---> maior valor sempre esta na raiz!  #
#  heap minimo ---> menor valor sempre esta na raiz!  #
#  consiste em uma arvore binaria completa!           #
#-----------------------------------------------------#
*/
#ifndef HEAPD_H
#define HEAPD_H

#include "item.h"

typedef struct heapd HEAPD;

HEAPD *criarHeap();
int apagarHeap(HEAPD *heap);

int vazia(HEAPD *heapd);
int tamanho(HEAPD *heapd);
int altura(HEAPD *heapd);

void imprimir(HEAPD *heapd);

int inserir(HEAPD *heapd, ITEM *item);
ITEM *remover(HEAPD *heapd);

#endif
