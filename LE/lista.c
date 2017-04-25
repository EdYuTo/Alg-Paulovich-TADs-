#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct no {
   ITEM *item;
   struct no *proximo;
} NO;

struct lista_ligada {
   NO *cabeca;
   NO *ultimo;
   int tamanho;
};

LISTA_LIGADA *criar_lista() {
   LISTA_LIGADA *lista = (LISTA_LIGADA *)malloc(sizeof(LISTA_LIGADA));

   if (lista != NULL) {
      lista->cabeca = (NO *)malloc(sizeof(NO));
     
      if (lista->cabeca != NULL) {
         lista->cabeca->item = criar_item(-1,-1);
         lista->cabeca->proximo = lista->cabeca;
         lista->tamanho = 0;
         lista->ultimo = lista->cabeca; 
      }
   }
   return lista;
}

void apagar_no (NO *no) {
   if (no != NULL)
      apagar_item(no->item);
   free(no);
}

void apagar_lista(LISTA_LIGADA *lista) {
   if (lista != NULL) {
      NO *auxiliar = lista->cabeca->proximo->proximo;
      NO *prem = lista->cabeca->proximo;
      
      while (prem != lista->cabeca) {
         apagar_no(prem);
         prem = auxiliar;
         auxiliar = auxiliar->proximo;
      }
   apagar_no(prem);
   free(lista);
   }
}

int inserir_item(LISTA_LIGADA *lista, ITEM *item) {
   if (lista != NULL) {
      NO *novo = (NO *)malloc(sizeof(NO));
   
      if (novo !=  NULL) {
         novo->item = item;
         novo->proximo = lista->cabeca;
         lista->ultimo->proximo = novo;
         lista->ultimo = novo;
         lista->tamanho++;
         return 1;
      }
   }
   return 0;
}

int remover_item(LISTA_LIGADA *lista, int chave) {
   if (lista != NULL) {
      NO *prem = lista->cabeca->proximo;
      NO *auxiliar = lista->cabeca;
      
      lista->cabeca->item->chave = chave;
      
      while (prem->item->chave != chave) {
         auxiliar = prem;
         prem = prem->proximo;
      }
      if (prem == lista->cabeca)
         return 0;
      else {
         auxiliar->proximo = prem->proximo;
         apagar_no(prem);
         lista->tamanho--;     
      }
   }
   return 0;
}

ITEM *retornar_item(LISTA_LIGADA *lista, int chave) {
   if (lista != NULL) {
      NO *auxiliar = lista->cabeca->proximo;
      lista->cabeca->item->chave = chave;
     
      while (auxiliar->item->chave != chave)
         auxiliar = auxiliar->proximo;
   
      return auxiliar == lista->cabeca ? NULL : auxiliar->item;
   }
   return NULL;
}

int vazia(LISTA_LIGADA *lista) {
   if (lista != NULL)
      return (lista->cabeca == lista->cabeca->proximo);
}

int tamanho(LISTA_LIGADA *lista) {
   if (lista != NULL)
      return lista->tamanho;
}

void imprimir(LISTA_LIGADA *lista) {
   if (lista != NULL) {
      NO *auxiliar = lista->cabeca->proximo;
      
      while (auxiliar != lista->cabeca) {
         imprimir_item(auxiliar->item);
         auxiliar = auxiliar->proximo;
      }
   }
}
