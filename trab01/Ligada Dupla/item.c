//EDSON YUDI TOMA 9791305

#include "item.h"
#include <stdlib.h>
#include <stdio.h>

/*
nao ha chave pois a busca e feita em relacao ao cpf
*/
ITEM *criar_item(char *n1, char *n2, char *cpf, char *tel) {
   ITEM *item = (ITEM *)malloc(sizeof(ITEM));

   if (item != NULL){
      item->primeiro_nome = n1;
      item->ultimo_nome = n2;
      item->cpf = cpf;
      item->telefone = tel;
   }
   return item;
}

void apagar_item(ITEM *item) {
   if (item != NULL) {
      free(item->primeiro_nome);
      free(item->ultimo_nome);
      free(item->cpf);
      free(item->telefone);
      free(item);
   }
}

void imprimir_item(ITEM *item) {
   if (item != NULL) {
      printf("Primeiro Nome: %s\n", item->primeiro_nome);
      printf("Ultimo Nome: %s\n", item->ultimo_nome);
      printf("CPF: %s\n", item->cpf);
      printf("Telefone: %s\n", item->telefone);
      printf("-----------------------------\n");
   }
}
