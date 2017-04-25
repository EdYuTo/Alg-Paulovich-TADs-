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
   arvore->raiz = no;
   return arvore->raiz;
}

NO *criar_no (ITEM *item) {
   NO *no = (NO *)malloc(sizeof(NO));
   if (no != NULL) {
      no->item = item;
      no->filhoesq = NULL;
      no->filhodir = NULL;
   }
   return no;
}

int inserirArv (ARVORE_BINARIA *arvore, NO *no) {
   if (arvore != NULL && no != NULL) {
      if (arvore->raiz == NULL)
         criar_raiz(arvore, no);
      else {
         NO *aux = arvore->raiz;
         while (true) {
            if (aux->item->frequencia > no->item->frequencia) {
               if (aux->filhoesq != NULL)
                  aux = aux->filhoesq;
               else {
                  aux->filhoesq = no;
                  return 1;
               }
            }
            else {
               if (aux->filhodir != NULL)
                  aux = aux->filhodir;
               else {
                  aux->filhodir = no;
                  return 1;
               }
            }
         }
      }
   }
   return 0;
}

void apagar_no (NO *no) {
   if (no != NULL) {
      apagar_item(&(no->item));
      no->filho_esq = NULL;
      no->filho_dir = NULL;
      free(no);
   }
}

void apagar_arvore_aux (NO *raiz) {
   if (raiz != NULL) {
      apagar_arvore_aux(raiz->filho_esq);
      apagar_arvore_aux(raiz->filho_dir);
      apagar_no(raiz);
   }
}

void apagar_arvore (ARVORE_BINARIA **arv) {
   if (arv != NULL && *arv != NULL) {
      apagar_arvore_aux((*arv)->raiz);
      free(*arv);
      *arv = NULL;
   }
}
