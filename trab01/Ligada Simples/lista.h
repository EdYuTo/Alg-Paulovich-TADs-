//EDSON YUDI TOMA 9791305

#ifndef LISTA_H
#define LISTA_H

#include "item.h"

typedef struct lista_ligada LISTA_LIGADA;

LISTA_LIGADA *criar_lista();
void apagar_lista(LISTA_LIGADA *lista);

int inserir_item(LISTA_LIGADA *lista, ITEM *item);
int remover_item(LISTA_LIGADA *lista, char *cpf);
ITEM *retornar_item(LISTA_LIGADA *lista, char *cpf);

int vazia(LISTA_LIGADA *lista);
int tamanho(LISTA_LIGADA *lista);
void imprimir(LISTA_LIGADA *lista);

#endif
