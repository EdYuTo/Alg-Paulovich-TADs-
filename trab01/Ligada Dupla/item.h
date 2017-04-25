//EDSON YUDI TOMA 9791305

#ifndef ITEM_H
#define ITEM_H

typedef struct {
   char *primeiro_nome;
   char *ultimo_nome;
   char *cpf;
   char *telefone;
} ITEM;

ITEM *criar_item(char *n1, char *n2, char *cpf, char *tel);
void apagar_item(ITEM *item);
void imprimir_item(ITEM *item);

#endif
