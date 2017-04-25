#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include "item.h"

typedef struct ArrayList ArrayList;
ArrayList *clone_arrayList(ArrayList *arraylist);

ArrayList *new_arrayList();
int add_arrayList(ArrayList *arrayList, ITEM *element);
int contains_arrayList(ArrayList *arrayList, int chave);
ITEM *get_arrayList(ArrayList *arrayList, int pos);

int indexOf_arrayList(ArrayList *arrayList, int chave);
int isEmpty_arrayList(ArrayList *arrayList);
int remove_arrayList(ArrayList *arrayList, int pos);
int set_arrayList(ArrayList *arrayList, int pos, ITEM *element);
int size_arrayList(ArrayList *arrayList);
int destroy_arrayList(ArrayList *arrayList);
void print_arrayList(ArrayList *arrayList);

ArrayList *subArray_arrayList(ArrayList *arrayList, int beginIndex, int endIndex);

#endif
