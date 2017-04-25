#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heapd.h"
#include "arvorebinaria.h"

typedef struct huffman TABELA_HUFFMAN;

TABELA_HUFFMAN *criarTabelaHuffman();
void liberarTabelaHuffman(TABELA_HUFFMAN **huffman);

int compactar(TABELA_HUFFMAN *huffman, char *msg);
int descompactar(TABELA_HUFFMAN *huffman, char *comp, char *msg);

#endif
