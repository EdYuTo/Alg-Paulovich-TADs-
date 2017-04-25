#include "huffman.h"
#include <stdio.h>

int main (int argc, char *argv[ ]) {
   char *p = "SUSIE SAYS IT IS EASY";
   TABELA_HUFFMAN *tabela = criarTabelaHuffman();
   
   criar_arv(tabela, p);
   criar_codigo(tabela);

   imprimirCodigo(tabela);

   liberarTabelaHuffman(&tabela);
   return 0;
}
