//EDSON YUDI TOMA 9791305

#include "mtesparsa.h"
#include "item.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct NO {
   ITEM *item;//valores
   struct NO *right;//proximo para a direita
   struct NO *down;//proximo para baixo
} NO;

struct ESPARSA {
   NO *head;//no base da matriz
//   NO **indexrow;-->|
//   NO **indexcol;-->|__ver se auxiliam em algo nessa merda...
   NO *lastrow;//ultima linha modificada
   NO *lastcol;//ultima coluna modificada
   int rows;//numero de linhas
   int cols;//numero de colunas
};

NO *criarNO (int row, int col, float value) {
   NO *no = (NO *)malloc(sizeof(NO));

   if (no != NULL) {
      no->item = criar_item(row, col, value);
      no->right = no;
      no->down = no;
   }
   return no;
}

int apagarNO (NO *no) {
   if (no != NULL) {
      apagar_item(&(no->item));
      no->right = NULL;
      no->down = NULL;
      free(no);
      return 1;
   }
   return 0;
}

ESPARSA *criarMT (int rows, int cols) {
   ESPARSA *matrix = (ESPARSA*)malloc(sizeof(ESPARSA));

   if (matrix != NULL) {
      matrix->rows = rows;//linhas
      matrix->cols = cols;//colunas
      matrix->head = criarNO(0, 0, 0);//cria um no cabeca com um item na pos (0,0)
      if (matrix->head != NULL) {
         NO *aux = matrix->head;
         for (int i = 1; i <= cols; i++) {
            aux->right = criarNO(0, i, 0);//declara as colunas
            aux = aux->right;
         }
         aux->right = matrix->head;
         aux = matrix->head;
         for (int i = 1; i <= rows; i++) {
            aux->down = criarNO(i, 0, 0);//declara as linhas
            aux = aux->down;
         }
         aux->down = matrix->head;
         matrix->lastrow = matrix->head;//|
         matrix->lastcol = matrix->head;//|__auxiliares...
      }
   }
   return matrix;
}

int apagarMT (ESPARSA *matrix) {
   if (matrix != NULL) {
      NO *prem = matrix->head->down;
      NO *paux = matrix->head->down->down;
      NO *apagar;
      NO *proximo;

      while (prem != matrix->head) {//linha por linha
         apagar = prem->right;
         proximo = prem->right->right;
         while (apagar != prem) {//coluna por coluna
            apagarNO(apagar);//apaga-se o no
            apagar = proximo;
            proximo = proximo->right;
         }
         apagarNO(prem);//apaga-se o no q indica a linha(coluna 0)
         prem = paux;
         paux = paux->down;
      }
      prem = matrix->head->right;
      paux = matrix->head->right->right;
      while (prem != matrix->head) {//apagar a 1 linha
         apagarNO(prem);
         prem = paux;
         paux = paux->right;
      }
      apagarNO(matrix->head);
      free(matrix);//free final
      return 1;
   }
   return 0;
}

void printMT (ESPARSA *matrix) {//fazer direito...
   if (matrix != NULL) {
      NO *rowprint = matrix->head->down;
      NO *rowaux = matrix->head->down->down;
      NO *colprint;
      NO *colaux;

      while (rowprint != matrix->head) {
         colprint = rowprint->right;
         colaux = rowprint->right->right;
         while (colprint != rowprint) {
            imprimir_item(colprint->item);
            colprint = colaux;
            colaux = colaux->right;
         }
         rowprint = rowaux;
         rowaux = rowaux->down;
      }
   }
}

int insert(ESPARSA *matrix, int row, int col, float value) {//considera a insercao ja ordenada!------->LEMBRAR DE REVER O LOOP!!
   if (matrix != NULL && row != 0 && col != 0 &&matrix->rows >= row && matrix->cols >= col) {
      NO *auxROW = matrix->lastrow;//ultima linha usada!
      NO *auxCOL = matrix->lastcol;//ultima coluna usada!
      NO *set = criarNO(row, col, value);      
 
      if (set != NULL) {
         while (auxROW->item->row < row)
            auxROW = auxROW->down;//desce nas linhas ate a linha desejada

         while (auxCOL->item->col < col)
            auxCOL = auxCOL->right;//continua para a direita ate a coluna desejada

         matrix->lastrow = auxROW;//|
         matrix->lastcol = auxCOL;//|__->salvar ultima linha e coluna para agilizar!

         if (auxROW->item->row == row && auxCOL->item->col == col) {
            NO *auxSET = auxROW;
            while (auxSET->right != auxROW)
               auxSET = auxSET->right;//na linha, vai para a direita ate o ultimo elemento!
            auxSET->right = set;
            set->right = auxROW;//apontar o elemento adicionado para o comeco da linha... 
            
            auxSET = auxCOL;
            while (auxSET->down != auxCOL)
               auxSET = auxSET->down;//na coluna, desce ate o ultimo elemento!
            auxSET->down = set;
            set->down = auxCOL;//apontar o elemento adicionado para o comeco da coluna...
         }
         else {
            apagarNO(set);//se der errado apaga-se o elemento
            return 0;
         }
         return 1;//deu certo!
      }
   }
   return 0;//deu errado!
}

ITEM *get(ESPARSA *matrix, int row, int col) {
   if (matrix != NULL && matrix->rows >= row && matrix->cols >= col) {
      if (row >= col) {//tentar ir por um caminho menor
         NO *auxCOL = matrix->head->right;
         NO *parada;
         while (auxCOL->item->col < col)//vai ate a coluna e para
            auxCOL = auxCOL->right;
         parada = auxCOL;

         while (auxCOL != parada && auxCOL->item->row < row)//vai ate a linha ou uma linha a mais
            auxCOL = auxCOL->down;

         if (auxCOL->item->row == row)//se for a linha desejada, retorna-se o item
            return auxCOL->item;
      }
      else {
         NO *auxROW = matrix->head->down;
         NO *parada;
         while (auxROW->item->row < row)//vai ate a linha e para
            auxROW = auxROW->down;
         parada = auxROW;

         while (auxROW != parada && auxROW->item->col < col)//vai ate a coluna ou uma coluna a mais
            auxROW = auxROW->right;

         if (auxROW->item->col == col)//se for a coluna desejada, retorna-se o item
            return auxROW->item;
      }
   }
   return NULL;//nao encontrou!
}

ESPARSA *add(ESPARSA *m1, ESPARSA *m2);
ESPARSA *mult(ESPARSA *m1, ESPARSA *m2);

