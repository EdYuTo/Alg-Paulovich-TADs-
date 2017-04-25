//EDSON YUDI TOMA --- 9791305
#include "item.h"
#include "heapd.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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
      no->filho_esq_huff =  NULL;
      no->filho_dir_huff = NULL;
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
      NO *noaux;
      ITEM *aux;
      if (last != heapd->raiz && last != NULL) {
         while (last->pai != NULL && last->item->frequencia < last->pai->item->frequencia) {//menor acima sempre!
            aux = last->pai->item;
            last->pai->item = last->item;
            last->item = aux;
            
            noaux = last->pai->filho_esq_huff;               //
            last->pai->filho_esq_huff = last->filho_esq_huff;//-->lembrar de trocar os filhos da arv!
            last->filho_esq_huff = noaux;                    //

            noaux = last->pai->filho_dir_huff;               //
            last->pai->filho_dir_huff = last->filho_dir_huff;//-->lembrar de trocar os filhos da arv!
            last->filho_dir_huff = noaux;                    //

            last = last->pai;
         }
      }
      return 1;
   }
   return 0;
}

int inserir (HEAPD *heapd, NO *no) {
   if (heapd != NULL && no != NULL) {
      if (heapd->raiz == NULL) {//simplesmente poe na raiz!
         heapd->raiz = no;
         heapd->last = no;
      }
      else {
         int pos = heapd->tamanho+1, i = (int)floor(log2(pos)), j = i;
         int *caminho = (int *)malloc(sizeof(int)*i);//decide o caminho a ser tomado!
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
   if (heapd != NULL && !(vazia(heapd))) {
      NO *aux = heapd->raiz;
      NO *trocaux;
      ITEM *troca;
      aux->pai = NULL;
      while (aux->filho_esq != NULL) {
         if (aux->filho_dir != NULL && aux->filho_dir->item->frequencia < aux->item->frequencia && 
               aux->filho_dir->item->frequencia < aux->filho_esq->item->frequencia) {//troca o pai com o menor dos filhos!
            troca = aux->item;
            aux->item = aux->filho_dir->item;
            aux->filho_dir->item = troca;

            trocaux = aux->filho_esq_huff;                       //
            aux->filho_esq_huff = aux->filho_dir->filho_esq_huff;//-->lembrar de trocar os filhos da arv!
            aux->filho_dir->filho_esq_huff = trocaux;            //

            trocaux = aux->filho_dir_huff;                       //
            aux->filho_dir_huff = aux->filho_dir->filho_dir_huff;//-->lembrar de trocar os filhos da arv!
            aux->filho_dir->filho_dir_huff = trocaux;            //

            aux = aux->filho_dir;
         }
         else if (aux->filho_esq->item->frequencia < aux->item->frequencia) {
            troca = aux->item;
            aux->item = aux->filho_esq->item;
            aux->filho_esq->item = troca;

            trocaux = aux->filho_esq_huff;                       //
            aux->filho_esq_huff = aux->filho_esq->filho_esq_huff;//-->lembrar de trocar os filhos da arv!
            aux->filho_esq->filho_esq_huff = trocaux;            //

            trocaux = aux->filho_dir_huff;                       //
            aux->filho_dir_huff = aux->filho_esq->filho_dir_huff;//-->lembrar de trocar os filhos da arv!
            aux->filho_esq->filho_dir_huff = trocaux;            //

            aux = aux->filho_esq;
         }
         else break;//no esta no seu devido lugar!
      }
      return 1;
   }   
   return 0;
}

NO *remover (HEAPD *heapd) {
   if (heapd != NULL && !(vazia(heapd))) {
      NO *noaux, *ret = heapd->last;
      ITEM *aux;
   
      if (heapd->last->pai != NULL && heapd->last->pai->filho_dir == NULL)
          heapd->last->pai->filho_esq = NULL;//apontar para null---filho e jogado no 1 no da heap
      else if (heapd->last->pai != NULL)
          heapd->last->pai->filho_dir = NULL;//apontar para null---filho e jogado no 1 no da heap

      aux = heapd->last->item;              //
      heapd->last->item = heapd->raiz->item;//-->troca o começo da heap com o ultimo!
      heapd->raiz->item = aux;              //
                  
      noaux = heapd->last->filho_esq_huff;                      //
      heapd->last->filho_esq_huff = heapd->raiz->filho_esq_huff;//lembrar de trocar o no da arv!
      heapd->raiz->filho_esq_huff = noaux;                      //

      noaux = heapd->last->filho_dir_huff;                      //
      heapd->last->filho_dir_huff = heapd->raiz->filho_dir_huff;//-->lembrar de trocar o no da arv!
      heapd->raiz->filho_dir_huff = noaux;                      //

      if (heapd->tamanho > 2) {
         int pos = heapd->tamanho-1, i = (int)floor(log2(pos)), j = i;
         int *caminho = (int *)malloc(sizeof(int)*i);//escolhe o caminho ate o fim
         while (pos != 1) {
            caminho[--i] = pos%2;
            pos/=2;
         }
         NO *auxd = heapd->raiz;
         for (i = 0; i < j-1; i++) {
            if (caminho[i])
               auxd = auxd->filho_dir;
            else
               auxd = auxd->filho_esq;
         }
         if (caminho[i])
            heapd->last = auxd->filho_dir;//fim e o filho dir
         else
            heapd->last = auxd->filho_esq;//fim e o filho esq
         free(caminho);
      }
      else if (heapd->tamanho == 2){//so sobra a raiz!
         heapd->last = heapd->raiz;
      }
      else {//nao sobra nada!
         heapd->last = NULL;
         heapd->raiz = NULL;
      }
      fixdown(heapd);//arruma a heap
      heapd->tamanho--;//decrementa o tamanho!
      return ret;
   }
   return NULL;
}
