//EDSON YUDI TOMA --- 9791305
#include "arvorebinaria.h"
#include <stdlib.h>
#include <stdio.h>

ARVORE_BINARIA *criar_arvore () {
   ARVORE_BINARIA *arv = (ARVORE_BINARIA *)malloc(sizeof(ARVORE_BINARIA));
   if (arv != NULL)
      arv->raiz = NULL;
   return arv;
}

NO *criar_raiz (ARVORE_BINARIA *arv, NO *no) {
   arv->raiz = no;
   return arv->raiz;
}

void apagar_arvore_aux (NO *raiz) {
   if (raiz != NULL) {
      apagar_arvore_aux(raiz->filho_esq_huff);
      apagar_arvore_aux(raiz->filho_dir_huff);
      apagarNO(raiz);
   }
}

void apagar_arvore (ARVORE_BINARIA **arv) {
   if (arv != NULL && *arv != NULL) {
      apagar_arvore_aux((*arv)->raiz);
      free(*arv);
      *arv = NULL;
   }
}
