//EDSON YUDO TOMA --- 9791305
#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H
#include "item.h"
#include "heapd.h"

typedef struct ARVORE_BINARIA {
   NO *raiz;
} ARVORE_BINARIA;

ARVORE_BINARIA *criar_arvore();
void apagar_arvore(ARVORE_BINARIA **arv);
NO *criar_raiz(ARVORE_BINARIA *arv, NO *no);

#endif
