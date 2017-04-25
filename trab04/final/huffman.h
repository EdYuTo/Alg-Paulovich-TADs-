//EDSON YUDI TOMA -- 9791305
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heapdinamica.h"
#include "arvorebinaria.h"

typedef struct huffman TABELA_HUFFMAN;

TABELA_HUFFMAN *criarTabelaHuffman();
void liberarTabelaHuffman(TABELA_HUFFMAN **huffman);

int criar_arv (TABELA_HUFFMAN *huffman, char *msg);
void criar_codigo (TABELA_HUFFMAN *huffman);
void imprimirCodigo (TABELA_HUFFMAN* huffman);

int compactarHuffman(char *msg, char **compac, TABELA_HUFFMAN **huffman);
char *descompactarHuffman(char *msg, int size, TABELA_HUFFMAN *huffman);

#endif
