//EDSON YUDI TOMA 9791305

#include "mtesparsa.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[ ]) {
   ESPARSA *m1 = criarMT(10, 10);
   ESPARSA *m2 = criarMT(10, 10);
   ESPARSA *m3;

//   for (int i = 0; i < 11; i++)
//      for (int j = 0; j < 11; j++) {
//         insert(m1, i, j, i+j);
//         insert(m2, i, j, i+j);
//      }

   m3 = add(m1, m2);

   printMT(m3);
//   for (int i = 1; i < 100; i++)
//      imprimir_item(get(m1, i,i));

   apagarMT(m1);
   apagarMT(m2);
   apagarMT(m3);
   return 0;
}
