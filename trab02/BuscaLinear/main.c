#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main (int argc, char *argv[ ]) {
   char *operation = (char *)malloc(sizeof(char)*10);
   ArrayList *arraylist = new_arrayList();

   do {
      read(&operation);
      functions(arraylist, operation);
   } while (!finish(operation));

   free(operation);
   destroy_arrayList(arraylist);
   return 0;
}
