#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>

#define NR_SIMBOLOS 256

struct huffman {
   ARVORE_BINARIA *arvore;
   char codigo[NR_SIMBOLOS][NR_SIMBOLOS];
};

TABELA_HUFFMAN *criarTabelaHuffman () {
   TABELA_HUFFMAN *huffman = (TABELA_HUFFMAN *)malloc(sizoef(TABELA_HUFFMAN));
   if (huffman != NULL) {
      for (int i = 0; i < NR_SIMBOLOS; i++)
         huffman->codigo[i][0] = '\0';
      huffman->arvore = NULL;
   }
   return huffman;
}

void liberarTabelaHuffman (TABELA_HUFFMAN **huffman) {
   if (huffman != NULL && *huffman != NULL) {
      apagar_arvore(&((*huffman)->arvore));
      free(*huffman);
      *huffman = NULL;
   }
}

void contagem_frequencia (int *freq, char *msg) {
   for (int i = 0; i < NR_SIMBOLOS; i++) 
      freq[i] = 0;
   for (int i = 0; msg[i] != '\0'; i++)
      freq[(int)msg[i]]++;
}

int criar_arv (TABELA_HUFFMAN *huffman, char *msg) {
   if (huffman != NULL && msg != NULL) {
      int freq[NR_SIMBOLOS];
      contagem_frequencia(freq, msg);
   
      HEAPD *heap = criarHeap();

      if (heap != NULL) {
         for (int i = 0; i < NR_SIMBOLOS; i++) {
            if (freq[i] > 0)
               inserir_heap(heap, criar_item(freq[i], i));
         }
         huffman->arvore = criar_arvore();
         int sum;
         while (tamanho(heap) > 1) {
            ITEM *esq = remover(heap);
            ITEM *dir = remover(heap);
            sum = esq->frequencia + dir->frequencia;
            NO *no = criar_no(criar_item(sum, '#'));
            no->filhoesq = criar_no(esq);
            no->filhodir = criar_no(dir);
            inserirArv(huffman->arvore, no);
         }
         apagarHeap(heap);
         return 1;
      }
   }
   return 0;
}

void criar_codigo_aux(TABELA_HUFFMAN *huffman, NO *no, char *cod, int fim) {
   if (no != NULL) {
      if (no->filhoesq == NULL && no->filhodir == NULL) {
         int i;
         for (i = 0; i <= fim; i++) {
            huffman->codigo[(int) no->simbolo][i] = cod[i];
         }
         huffman->codigo[(int) no->simbolo][fim + 1] = '\0';
      } else {
         if (no->filhoesq != NULL) {
            fim++;
            cod[fim] = '0';
            criar_codigo_aux(huffman, no->filhoesq, cod, fim);
            fim--;
         }
         if (no->filhodir != NULL) {
            fim++;
            cod[fim] = '1';
            criar_codigo_aux(huffman, no->filhodir, cod, fim);
            fim--;
         }
      }
   }
}

void criar_codigo (TABELA_HUFFMAN *huffman) {
   char codigo[NR_SIMBOLOS];
   criar_codigo_aux(huffman, huffman->arvore->raiz, codigo, -1);
}


