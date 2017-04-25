#include "mtesparsa.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[ ]) {
   char c;
   int row, col;
   int value;
   ESPARSA *m1, *m2, *m3;

   scanf("%c", &c);
  
   scanf("%d %d %d", &value, &row, &col);
   m1 = criarMT(row, col);
   while (row != -1) {
      scanf("%d %d %d", &row, &col, &value);
      insert(m1, row, col, value);
   }
  
   m2 = criarMT(col, (int)value);
   while (scanf("%d %d %d", &row, &col, &value) != EOF) {
      insert(m2, row, col, value);
   }

   if (c == 'A')
      m3 = add(m1, m2);
   else if (c == 'M')
      m3 = mult(m1, m2);

   printMT(m3);

   apagarMT(m1);
   apagarMT(m2);
   apagarMT(m3);

   return 0;
}
