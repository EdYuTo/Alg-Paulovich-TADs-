//EDSON YUDI TOMA 9791305

#ifndef MTESPARSA_H
#define MTESPARSA_H
#include "item.h"
typedef struct ESPARSA ESPARSA;

ESPARSA *criarMT(int rows, int cols);
void printMT (ESPARSA *matrix);
int apagarMT(ESPARSA *matrix);

int insert(ESPARSA *matrix, int row, int col, int value);
ITEM *get(ESPARSA *matrix, int row, int col);

ESPARSA *add(ESPARSA *m1, ESPARSA *m2);
ESPARSA *mult(ESPARSA *m1, ESPARSA *m2);

#endif
