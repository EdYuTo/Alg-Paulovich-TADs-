#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "arraylist.h"
#include "functions.h"

void read(char **string) {
   char c;
   int i = 0;

   do {
      c = fgetc(stdin);
      *(*string+i++) = c;
   } while (c != '\n' && c != ' ' && c != EOF);//terminar em enter, espaco ou fim de arquivo!
   *(*string+i-1) = '\0';
}

int finish(char *op) {//1 termina!
   return strcmp(op, "sair") == 0;
}

void functions(ArrayList *arraylist, char *op) {
   if(strcmp(op, "add") == 0) { 
      int chave, valor;
      scanf("%d %d", &chave, &valor);
      add_arrayList(arraylist, criar_item(chave, valor));
   }
   else if(strcmp(op, "remover") == 0) {
      int pos;
      scanf("%d", &pos);
      remove_arrayList(arraylist, pos);
   }
   else if(strcmp(op, "sub") == 0) { 
      ArrayList *sub;
      int beginIndex, endIndex;
      scanf("%d %d", &beginIndex, &endIndex);
      sub = subArray_arrayList(arraylist, beginIndex, endIndex);
      print_arrayList(sub);
      destroy_arrayList(sub);
   }
   else if(strcmp(op, "set") == 0) {
      int pos, chave, valor;
      scanf("%d %d %d", &pos, &chave, &valor);
      set_arrayList(arraylist, pos, criar_item(chave, valor));
   }
   else if(strcmp(op, "print") == 0) {
      print_arrayList(arraylist);
   }
   else if(strcmp(op, "tamanho") == 0) {
      printf("%d\n", size_arrayList(arraylist));
   }
   else if(strcmp(op, "indice") == 0) {
      int chave;
      scanf("%d", &chave);
      int indice = indexOf_arrayList(arraylist, chave);
      if (indice != -1)
         printf("%d\n", indice);
   }
   else if(strcmp(op, "get") == 0) {
      int pos;
      scanf("%d", &pos);
      imprimir_item(get_arrayList(arraylist, pos));
   }
   else if(strcmp(op, "contem") == 0) {
      int chave;
      scanf("%d", &chave);
      printf("%d\n", contains_arrayList(arraylist, chave));
   }
   else if(strcmp(op, "vazia") == 0) {
      printf("%d\n", isEmpty_arrayList(arraylist));
   }
}
