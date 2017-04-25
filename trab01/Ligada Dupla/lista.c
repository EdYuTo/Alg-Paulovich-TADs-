//EDSON YUDI TOMA 9791305

#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct no {
   ITEM *item;
   struct no *proximo;
   struct no *anterior;
} NO;

struct lista_ligada {
   NO *cabeca;
   NO *ultimo;
   int tamanho;
};

/*a funcao criar_lista cria a lista e aloca um no 'vazio' para servir
de sentinela, ele sera usada como ponto de parada nas funcoes de busca
e remocao (colocando-se o valor a ser buscado nele, garantindo que
ocorra parada!)
*/
LISTA_LIGADA *criar_lista() {
   LISTA_LIGADA *lista = (LISTA_LIGADA *)malloc(sizeof(LISTA_LIGADA));

   if (lista != NULL) {
      lista->cabeca = (NO *)malloc(sizeof(NO));
     
      if (lista->cabeca != NULL) {
         lista->cabeca->item = criar_item(NULL,NULL,NULL,NULL);
         lista->cabeca->proximo = lista->cabeca;
         lista->cabeca->anterior = lista->cabeca;
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

/*
a funcao apagar lista comeca pelo segundo no (exceto a cabeca), e um
ponteiro de remocao garante que o ponteiro anterior ao auxiliar seja
apagado... lembrando que se a lista possuir 0 elementos (só a sentinela)
os proximos elementos serao ela mesma, nao cehgando a passar pelo while
*/
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

/*
aponta-se o novo item para a sentinela (cabeca) e para o ultimo da 
lista (seu anterior), faz-se o ultimo elemento apontar para o novo, 
o novo elemento ser o ultimo da lista e incrementa-se o tamanho da lista!
*/
int inserir_item(LISTA_LIGADA *lista, ITEM *item) {
   if (lista != NULL) {
      NO *novo = (NO *)malloc(sizeof(NO));
   
      if (novo !=  NULL) {
         novo->item = item;
         novo->proximo = lista->cabeca;
         novo->anterior = lista->ultimo;
         lista->ultimo->proximo = novo;
         lista->ultimo = novo;
         lista->cabeca->anterior = novo;
         lista->tamanho++;
         return 1;
      }
   }
   return 0;
}

/*
comecando-se pelo 1 no, busca-se o no que deseja ser retirado, quando
encontrado checa-se se ele e um no valido ou a cabeca (que recebeu o
valor procurado para servir como ponto de parada), caso ele seja um
no valido, o auxiliar sera removido e o tamanho da lista e decrementado
*/
int remover_item(LISTA_LIGADA *lista, char *cpf) {
   if (lista != NULL) {
      NO *auxiliar = lista->cabeca->proximo;
   
      if (lista->cabeca->item->cpf == NULL)  
         lista->cabeca->item->cpf = (char *)malloc(16);

      strcpy(lista->cabeca->item->cpf, cpf);
      
      while (strcmp(auxiliar->item->cpf,cpf))
         auxiliar = auxiliar->proximo;
      
      if (auxiliar == lista->cabeca)
         return 0;
      else {
         auxiliar->proximo->anterior = auxiliar->anterior;
         auxiliar->anterior->proximo = auxiliar->proximo;
         apagar_no(auxiliar);
         lista->tamanho--;
         return 1;    
      }
   }
   return 0;
}
/*
semelhante a funcao de remocao, mas , inves de remover, retorna-se um
item que estava sendo buscado
*/
ITEM *retornar_item(LISTA_LIGADA *lista, char *cpf) {
   if (lista != NULL) {
      NO *auxiliar = lista->cabeca->proximo;
      
      if (lista->cabeca->item->cpf == NULL)  
         lista->cabeca->item->cpf = (char *)malloc(16);

      strcpy(lista->cabeca->item->cpf, cpf);
     
      while (strcmp(auxiliar->item->cpf, cpf))
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
/*
imprime a lista ate chegar na cabeca!
*/
void imprimir(LISTA_LIGADA *lista) {
   if (lista != NULL) {
      NO *auxiliar = lista->cabeca->proximo;
      
      while (auxiliar != lista->cabeca) {
         imprimir_item(auxiliar->item);
         auxiliar = auxiliar->proximo;
      }
   }
}
