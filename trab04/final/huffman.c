//EDSON YUDI TOMA --- 9791305
#include "huffman.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NR_SIMBOLOS 256

struct huffman {
   ARVORE_BINARIA *arvore;
   char codigo[NR_SIMBOLOS][NR_SIMBOLOS];
};

TABELA_HUFFMAN *criarTabelaHuffman () {
   TABELA_HUFFMAN *huffman = (TABELA_HUFFMAN *)malloc(sizeof(TABELA_HUFFMAN));//aloca
   if (huffman != NULL) {
      for (int i = 0; i < NR_SIMBOLOS; i++)
         huffman->codigo[i][0] = '\0';//todas as strings sao inicializadas
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
   for (int i = 0; i < NR_SIMBOLOS; i++)//zera tudo
      freq[i] = 0;
   for (int i = 0; msg[i] != '\0'; i++)//conta a qtd de vezes q cada char aparece
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
               inserir(heap, criarNO(criar_item(freq[i], i)));//insere na heap minima o no (frequencia, char)
         }
         while (tamanho(heap) > 1) {//cria a arv de huff a partir da heap
            NO *esq = remover(heap);
            NO *dir = remover(heap);
            int freq = esq->item->frequencia + dir->item->frequencia;
            NO *novo = criarNO(criar_item(freq, '#'));
            novo->filho_esq_huff = esq;
            novo->filho_dir_huff = dir;
            inserir(heap, novo);
         }
         huffman->arvore = criar_arvore();//aloca-se a arvore
         huffman->arvore->raiz = remover(heap);//insere-se a raiz
         apagarHeap(heap);//heap nao mais necessaria!
         return 1;
      }
   }
   return 0;
}

void criar_codigo_aux(TABELA_HUFFMAN *huffman, NO *no, char *cod, int fim) {
   if (no != NULL) {
      if (no->filho_esq_huff == NULL && no->filho_dir_huff == NULL) {//atingiu a folha
         int i;
         for (i = 0; i <= fim; i++) {//escreve na tabela de codigo
            huffman->codigo[(int) no->item->simbolo][i] = cod[i];
         }
         huffman->codigo[(int) no->item->simbolo][fim + 1] = '\0';
      } 
      else {
         if (no->filho_esq_huff != NULL) {//existe filho_esq, vai para a esq e anota-se no aux
            fim++;
            cod[fim] = '0';
            criar_codigo_aux(huffman, no->filho_esq_huff, cod, fim);//recursao
            fim--;
         }
         if (no->filho_dir_huff != NULL) {//depois dos filhos esq, percorrem-se os dir!
            fim++;
            cod[fim] = '1';
            criar_codigo_aux(huffman, no->filho_dir_huff, cod, fim);//recursao
            fim--;
         }
      }
   }
}

void criar_codigo (TABELA_HUFFMAN *huffman) {
   char codigo[NR_SIMBOLOS];//aux
   criar_codigo_aux(huffman, huffman->arvore->raiz, codigo, -1);
}

int compactarHuffman (char *msg, char **compac, TABELA_HUFFMAN **huffman) {//retorna o tamanho!
   if (huffman != NULL && *huffman != NULL) {
      char *aux = (char *)malloc(sizeof(char)*8*strlen(msg));
      int i, j = 0;
      criar_arv(*huffman, msg);
      criar_codigo(*huffman);
      for (i = 0; msg[i] != '\0'; i++)
         for (int k = 0; (*huffman)->codigo[msg[i]][k] != '\0'; k++)//concatena em um aux!
            aux[j++] = (*huffman)->codigo[msg[i]][k];
      aux[j] = '\0';

      char *comp = strlen(aux)%8 ? (char *)calloc(strlen(aux)/8 + 3, sizeof(char)):
                                   (char *)calloc(strlen(aux)/8 + 2, sizeof(char));//*comentario

      for (i = 0, j = 0; aux[i] != '\0'; i++) {
         if (i%8 || i == 0)
            comp[j] += (aux[i]-48)*(1<<(i%8)); //-48 pois o 0 em ascii e 48
         else
            comp[++j] += aux[i]-48;//-48 pois o 0 em ascii e 48
      }
      comp[++j] += i%8 ? i%8 : 8;//usara de 1 a 8 bits do byte anterior! 
      comp[++j] = '\0';

      *compac = comp;
      free(aux);
      return j;//j = tamanho!
/**comentario:
tamanho (+3 pois divisao entre int arrendonda para baixo, portanto caso um dos bytes nao esteja completo, 
soma-se 1 para completar, 1 para o o byte com qtd de bits utilizados no ultimo byte,e 1 para o terminador!, 
agora, caso completa-se um byte inteiro, não há necessidade de corrigir a divisao inteira, 
portanto soma-se apenas 1 para o terminador e 1 para o byte com a qtd de bits utilizados!)
*/
   }
   return -1;//erro!
}

char *descompactarHuffman (char *msg, int size, TABELA_HUFFMAN *huffman) {
   if (huffman != NULL) {
      NO *aux = huffman->arvore->raiz;
      char *decod = NULL;//texto decodificado vem aqui
      int i = 0, j = 0, max;
      for (i = 0; i < size-2; i++) {
         for (int k = 0; k < 8; k++) {
            if((msg[i]&(1<<k)))//---------->1
               aux = aux->filho_dir_huff;
            else//------------------------->0
               aux = aux->filho_esq_huff;
            if (aux->filho_esq_huff == NULL && aux->filho_dir_huff == NULL) {//chegou na folha = encontrou o char!
               decod = (char *)realloc(decod, sizeof(char)*j+1);
               decod[j++] = aux->item->simbolo;
               aux = huffman->arvore->raiz;//volta para a raiz!
            }
         }
      }
      for (int k = 0; k < msg[size-1]; k++) {//trata o ultimo byte separado, pois ele pode estar completo ou nao!
         if((msg[i]&(1<<k)))//---------->1
            aux = aux->filho_dir_huff;
         else//------------------------->0
            aux = aux->filho_esq_huff;
         if (aux->filho_esq_huff == NULL && aux->filho_dir_huff == NULL) {//chegou na folha = encontrou o char!
            decod = (char *)realloc(decod, sizeof(char)*j+1);
            decod[j++] = aux->item->simbolo;
            aux = huffman->arvore->raiz;//volta para a raiz!
         }
      }
      decod = (char *)realloc(decod, sizeof(char)*j+1);
      decod[j] = '\0';
      return decod;
   }
   return NULL;
}
