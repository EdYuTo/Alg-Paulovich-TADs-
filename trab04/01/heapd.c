#include "item.h"
#include "heapd.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct NO {
   ITEM *item;
   struct NO *pai;
   struct NO *filho_esq;
   struct NO *filho_dir;
} NO;

struct heapd {
   NO *raiz;
   NO *last;//ultimo elemento inserido!
   int tamanho;
};

NO *criarNO (ITEM *item) {
   NO *no = (NO *)malloc(sizeof(NO));
   
   if (no != NULL) {
      no->item = item;
      no->pai = NULL;
      no->filho_esq = NULL;
      no->filho_dir = NULL;
   }
   return no;
}

int apagarNO (NO *no) {
   if (no != NULL) {
      apagar_item(&(no->item));
      no->pai = NULL;
      no->filho_esq = NULL;
      no->filho_dir = NULL;
      free(no);
      return 1;
   }
   return 0;
}

HEAPD *criarHeap () {
   HEAPD *heapd = (HEAPD *)malloc(sizeof(HEAPD));
   if (heapd != NULL) {
      heapd->raiz = NULL;
      heapd->last = NULL;
      heapd->tamanho = 0;
   }
   return heapd;
}

void aux_apagarHeap (NO *no) {
   if (no != NULL) {
      aux_apagarHeap (no->filho_esq);
      aux_apagarHeap (no->filho_dir);
      apagarNO(no);
   }
/*
Quando o ultimo no visitado for null, a funcao retorna e vai para o filho da direita, se este tb for null, a funcao retorna e o no que esta sendo avaliado no momento eh o ultimo, apaga-o. Assim, recursivamente se apagam todos os nos!
*/
}

int apagarHeap (HEAPD *heapd) {
   if (heapd != NULL) {
      aux_apagarHeap(heapd->raiz);
      free(heapd);
      return 1;
   }
   return 0;
}

int vazia (HEAPD *heapd) {
   if (heapd != NULL)
      return heapd->raiz == NULL;
   return -1;//erro, a estrutura nao existe (heapd == NULL)
}

int tamanho (HEAPD *heapd) {
   if (heapd != NULL)
      return heapd->tamanho;
   return -1;//erro, a estrutura nao existe (heapd == NULL)
}

int altura (HEAPD*heapd) {
   if (!vazia(heapd)) {
      return (int)floor(log2(heapd->tamanho)); 
   }
   return -1;//erro, a estrutura nao existe (heapd == NULL)
}

void aux_imprimir (NO *no) {
   if (no != NULL) {
      printf("{");
      imprimir_item(no->item);
      aux_imprimir(no->filho_esq);
      aux_imprimir(no->filho_dir);
      printf("}");
   }
}

void imprimir (HEAPD *heapd) {
   if (heapd != NULL)
      aux_imprimir(heapd->raiz);
   printf("\n");
}

int fixup (HEAPD *heapd) {
   if (heapd != NULL) {
      NO *last = heapd->last;
      ITEM *aux;
      if (last != heapd->raiz && last != NULL) {
         while (last->pai != NULL && last->item->frequencia < last->pai->item->frequencia) {
            aux = last->pai->item;
            last->pai->item = last->item;
            last->item = aux;
            last = last->pai;
         }
      }
      return 1;
   }
   return 0;
}

int inserir (HEAPD *heapd, ITEM *item) {
   NO *no = criarNO(item);
   if (heapd != NULL && no != NULL) {
      if (heapd->raiz == NULL) {//simplesmente poe na raiz!
         heapd->raiz = no;
         heapd->last = no;
      }
      else {
         int pos = heapd->tamanho+1, i = (int)floor(log2(pos)), j = i;
         int *caminho = (int *)malloc(sizeof(int)*i);
         while (pos != 1) {
            caminho[--i] = pos%2;
            pos/=2;
         }
         NO *aux = heapd->raiz;
         for (i = 0; i < j-1; i++) {
            if (caminho[i])
               aux = aux->filho_dir;
            else
               aux = aux->filho_esq;
         }
         if (caminho[i])
            aux->filho_dir = no;//poe no filho dir
         else
            aux->filho_esq = no;//poe no filho esq
         no->pai = aux;//lembrar de apontar para o pai!
         heapd->last = no;
         fixup(heapd);//arruma-se a heap!
         free(caminho);
      }
      heapd->tamanho++;//aumentou o tamanho
      return 1;
   }
   return 0;
}

int fixdown (HEAPD *heapd) {
   if (heapd != NULL && heapd->raiz != NULL) {
      NO *raiz = heapd->raiz;
      ITEM *aux;
      while (raiz->filho_esq != NULL && raiz->filho_dir != NULL && 
      (raiz->item->frequencia > raiz->filho_esq->item->frequencia ||//checa ate nenhum filho ser maior... 
      raiz->item->frequencia > raiz->filho_dir->item->frequencia)) {//...ou nao ter filhos!
         if (raiz->filho_esq->item->frequencia < raiz->filho_dir->item->frequencia) {//troca com o maior
            aux = raiz->item;
            raiz->item = raiz->filho_esq->item;
            raiz->filho_esq->item = aux;
            raiz = raiz->filho_esq;
         }
         else {//ou com o outro maior...
            aux = raiz->item;
            raiz->item = raiz->filho_dir->item;
            raiz->filho_dir->item = aux;
            raiz = raiz->filho_dir;
         }
      }
      return 1;
   }
   return 0;
}

ITEM *remover (HEAPD *heapd) {
   if (heapd != NULL && heapd->raiz != NULL) {//if (!vazia(heapd))
      NO *last = heapd->last;
      ITEM *aux = heapd->raiz->item;
      if (last != heapd->raiz) {
         heapd->raiz->item = last->item;
         int pos = heapd->tamanho-1, i = (int)floor(log2(pos)), j = i;
         int *caminho = (int *)malloc(sizeof(int)*i);
         while (pos != 1) {
            caminho[--i] = pos%2;
            pos/=2;
         }
         NO *auxD = heapd->raiz;
         for (i = 0; i < j-1; i++) {
            if (caminho[i])
               auxD = auxD->filho_dir;
            else
               auxD = auxD->filho_esq;
         }
         if (caminho[i]) {
            last->pai->filho_esq = NULL;//lembrar de parar de apontar para o deslocado!
            heapd->last = auxD->filho_dir;
         }
         else {
            auxD->filho_dir = NULL;//lembrar de parar de apontar para o desocado!
            heapd->last = auxD->filho_esq;
         }
         free(caminho);
         fixdown(heapd);         
      }
      else
         heapd->raiz = NULL;//fica vazia...
      free(last);
      heapd->tamanho--;//decrementar o tamanho
      return aux;
   }
   return NULL;
}
