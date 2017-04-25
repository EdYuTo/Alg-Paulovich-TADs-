#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H
#include "item.h"

typedef struct NO {
   ITEM *item;
   struct NO *filhoesq;
   struct NO *filhodir;
} NO;

typedef struct ARVORE_BINARIA {
   NO *raiz;
} ARVORE_BINARIA;

ARVORE_BINARIA *criar_arvore();
int inserirArv(ARVORE_BINARIA *arvore, NO *no);
void apagar_arvore(ARVORE_BINARIA **arv);

NO *criar_raiz(ARVORE_BINARIA *arv, NO *no);
NO *criar_no(ITEM *item);

#endif
