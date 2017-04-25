#include "arraylist.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct NO {
   ITEM **list;//vetor de ponteiros para itens
   int posicao;//indica qual no estamos lidado (equivalente a uma chave)
   int mchave;//indica a maior chave, facilitar insercao e remocao
   int fimvet;//quantidade de elementos ocupados do vetor
   int tamanho;//tamanho do vetor
   struct NO *proximo;
} NO;

struct ArrayList {
   NO *inicio;
   NO *fim;
   int numero; //quantidade de nos
};

NO *criarNo(int posicao) {
   NO *no = (NO *)malloc(sizeof(NO));
  
    if (no != NULL) {
      no->list = NULL;
      no->posicao = posicao;
      no->fimvet = 0;
      no->mchave = -1;
      no->tamanho = 0;
      no->proximo = NULL;

      return no;
   }
   return NULL;
}

ArrayList *new_arrayList() {
   ArrayList *arraylist = (ArrayList *)malloc(sizeof(ArrayList));

   if (arraylist != NULL) {
      NO *no = criarNo(0);

      arraylist->inicio = no;
      arraylist->fim = no;
      arraylist->numero = 1;

      return arraylist;
   }

   return NULL;
}

int add_arrayList(ArrayList *arraylist, ITEM *element) {
   if (arraylist != NULL && element != NULL) {
      if (arraylist->fim->list == NULL) {//se a lista estiver vazia aloca-se o vetor da lista
         arraylist->fim->list = (ITEM **)malloc(sizeof(ITEM *)*(10<<(arraylist->fim->posicao)));
         arraylist->fim->tamanho = 10<<(arraylist->fim->posicao);
      }
      else if (arraylist->fim->fimvet == arraylist->fim->tamanho) {//caso o vetor da lista esteja cheio, aloca-se um novo no com um novo vetor!
         NO *no = criarNo(arraylist->fim->posicao + 1);
         if (no != NULL) {
            arraylist->numero++;
            arraylist->fim->proximo = no;
            arraylist->fim = no;
            arraylist->fim->list = (ITEM **)malloc(sizeof(ITEM *)*(10<<(arraylist->fim->posicao)));//garante que o novo tamanho sera sempre 2x maior!
            arraylist->fim->tamanho = 10<<(arraylist->fim->posicao);
         }
      }
      NO *aux = arraylist->inicio;
      for (int i = 0; i < arraylist->numero; i++) {
         if(element->chave >= aux->mchave && aux->fimvet < aux->tamanho) {
            arraylist->fim->list[arraylist->fim->fimvet] = element; //tratado-se os casos de cheio/vazio basta inserir normalmente!
            arraylist->fim->fimvet++;//note que se fimvet < tamanho, o vetor nao esta cheio e, portanto, el. esta no no fim!
            arraylist->fim->mchave = element->chave;
            return 1;
         }
         else if (element->chave < aux->mchave) {
            int j = 0;
            while (aux->list[j]->chave < element->chave) j++;//para-se no elemento com a chave maior!
            ITEM *aux1 = aux->list[j];//armazena-se o valor em um aux para nao perde-lo!
            ITEM *aux2;
            aux->list[j] = element;//substitui-se o valor
            arraylist->fim->list[arraylist->fim->fimvet] = NULL;//insere-se um suposto item vazio(ele sera substituido apos o shift)
            arraylist->fim->fimvet++;//incrementa-se o tamanho!
            while (aux != NULL) {
               for (int k = j; k < aux->fimvet-1; k++) {
                  aux->mchave = aux1->chave;
                  aux2 = aux->list[k+1];
                  aux->list[k+1] = aux1;
                  aux1 = aux2;
               }
               j = -1;
               aux = aux->proximo;
            }
            return 1;
         }
         aux = aux->proximo;//enquanto nao adicionar move o no!
      }
   }
   return 0;
}

ArrayList *clone_arrayList(ArrayList *arraylist) {
   ArrayList *newarraylist = new_arrayList();

   if (arraylist != NULL && newarraylist != NULL) {
      newarraylist->numero = arraylist->numero;
      newarraylist->fim = newarraylist->inicio;
      newarraylist->fim->tamanho = 10;
      newarraylist->fim->fimvet = arraylist->inicio->fimvet;
      newarraylist->fim->mchave = arraylist->inicio->mchave;
     
      NO *aux = arraylist->inicio->proximo;//caso seja null significa q nao ha proximo, portanto arraylist->numero = 1, nem entra no for!
      for (int i = 1; i < arraylist->numero; i++) {
         newarraylist->fim->proximo = criarNo(i);
         newarraylist->fim = newarraylist->fim->proximo;
         newarraylist->fim->tamanho = 10<<(i);
         newarraylist->fim->fimvet = aux->fimvet;
         newarraylist->fim->mchave = aux->mchave;
         aux = aux->proximo;//ultimo caso ele fica igual a NULL e o for acaba! pq vai ate < q a quantidade de nos!
      }
      aux = arraylist->inicio;
      NO *newaux = newarraylist->inicio;
      for (int i = 0; i < arraylist->numero; i++) {
         newaux->list = (ITEM **)malloc(sizeof(ITEM *)*(newaux->tamanho));//pode usar 10<<i
         for (int j = 0; j < newaux->fimvet; j++) {
            newaux->list[j] = criar_item(aux->list[j]->chave, aux->list[j]->valor);
         }
         aux = aux->proximo;
         newaux = newaux->proximo;
      }
      return newarraylist;
   }
   return NULL;
}

int contains_arrayList(ArrayList *arraylist, int chave) {//------------------------->BUSCA
   if (arraylist != NULL) {
      NO *aux = arraylist->inicio;
      for (int i = 0; i < arraylist->numero; i++) {
         if (aux->mchave >= chave)
            for (int j = 0; j < aux->fimvet; j++)//FAZER BUSCA BINARIA!!
               if (aux->list[j]->chave == chave)//
                  return 1;//contem!
         aux = aux->proximo;
      }
   }
   return 0;//n contem!
}

ITEM *get_arrayList(ArrayList *arraylist, int pos) {
   if (arraylist !=  NULL) {
      int soma = 0, i;
      for (i = 0; soma+(10<<i) <= pos; i++) 
         soma += (10<<i);//quando o for acabar saberemos que a posicao esta no no i do array!

      NO *aux = arraylist->inicio;
      if (pos >= 0 && arraylist->numero > i) { 
         while (aux->posicao != i) {
            if (aux != NULL) 
               aux = aux->proximo;
            else
               return NULL;//evitar pos invalida!
         }
         if (aux->fimvet > pos-soma)//evitar pos invalida!
            return aux->list[pos-soma];//a posicao desejada - a soma da pg ate o vetor atual eh igual a posicao desejada no vetor atual!
      }
   }
   return NULL;
}

int indexOf_arrayList(ArrayList *arraylist, int chave) {//------------------------------>BUSCA
   if (arraylist != NULL) {
      NO *aux = arraylist->inicio;
      int i, soma = 0;
      for (i = 0; i < arraylist->numero && chave > aux->mchave; i++, aux = aux->proximo);//enquanto a chave for menor q a maior chave pula-se o no!
      if (aux != NULL) {
         for (int j = 0; j < i; j++) 
            soma += (10<<j);
         for (i = 0; i < aux->fimvet; i++)//FAZER BUSCA BINARIA!!!
            if (aux->list[i]->chave == chave)
               return soma + i;//a soma da pg das quantidade de posicoes anteriores + a posicao atual
      }
   }
   return -1;//return de erro!
}

int isEmpty_arrayList(ArrayList *arraylist){
   if (arraylist != NULL) {
      if (arraylist->inicio->list == NULL)
         return 1;//retorna 1 se verdadeiro!
   }
   return 0;//falso!
}

int remove_arrayList(ArrayList *arraylist, int pos) {
   if (arraylist !=  NULL) {
      if (get_arrayList(arraylist, pos) != NULL) {//checa se a posicao eh valida!
         int soma = 0, i;
         for (i = 0; soma+(10<<i) <= pos; i++) 
            soma += (10<<i);//quando o for acabar saberemos que a posicao esta no no i do array!

         NO *aux = arraylist->inicio;
         if (pos >= 0 && arraylist->numero > i) { 
            while (aux->posicao != i) {
               if (aux != NULL) 
                  aux = aux->proximo;
            }
            apagar_item(&(aux->list[pos-soma]));//a posicao desejada - a soma da pg ate o vetor atual eh igual a posicao desejada no vetor atual!
         }
         int j = pos-soma;
         while (aux != NULL) {//parada
            for (int k = j; k < aux->fimvet-1; k++) {
               aux->list[k] = aux->list[k+1];//shifts
            }
            if (aux->proximo != NULL && aux->fimvet == aux->tamanho) 
               aux->list[aux->fimvet - 1] = aux->proximo->list[0];//shifts entre nos
            else
               aux->fimvet--;//se nao houver shift entre nos significa que estamos no ultimo, portanto diminuiremos o fimvet!
            if (aux->fimvet > 0)
               aux->mchave = aux->list[aux->fimvet-1]->chave;
            j = 0;
            aux = aux->proximo;
         }
         if (arraylist->fim->fimvet < 1) {//checar se o ultimo no ficou vazio e apaga-lo!
            free(arraylist->fim->list);
            free(arraylist->fim);
            arraylist->numero--;
            aux = arraylist->inicio;
            for (int k = 0; k < arraylist->numero; k++)
               aux = aux->proximo;
            aux->proximo = NULL;
         }
         return 1;
      }
   }
   return 0;
}

int size_arrayList(ArrayList *arraylist) {
   if (arraylist != NULL) {
      int soma = 0;
      for (int i = 0; i < arraylist->numero-1; i++)
         soma += (10<<i);
      return soma + arraylist->fim->fimvet;//soma da pg ate o no anterior mais a ultima pos usada do no atual!
   }
   return 0;
}

int set_arrayList(ArrayList *arraylist, int pos, ITEM *element) {
   if (arraylist != NULL && element != NULL) {
      if (pos < size_arrayList(arraylist)) {//checar se nao esta tentando inserir em uma posicao indevida!
         remove_arrayList(arraylist, pos);
         add_arrayList(arraylist, element);
         return 1;
      }
      else
         apagar_item(&element);//caso esteja, lembrar de desalocar o item alocado!
   }
   return 0;
}

ArrayList *subArray_arrayList(ArrayList *arraylist, int beginIndex, int endIndex) {
   ArrayList *newarraylist = new_arrayList();
//a funcao seria mais rapida se ao inves de chamar a outra funcao todas as vezes, simplesmente copiar todos os itens a partir de tal pos.
   if (arraylist != NULL && newarraylist != NULL) {
      if (beginIndex >= 0) {//evitar acessar posicao negativa
         for (int i = beginIndex; i < endIndex; i++) {
            ITEM *item = get_arrayList(arraylist, i);
            if (item == NULL) break;//se a funcao get_arrayList retornar NULL significa q houve algum erro, provavelmente nao ha mais itens no vetor!
            ITEM *novoitem = criar_item(item->chave, item->valor);
            add_arrayList(newarraylist, novoitem);
         }
      }
      return newarraylist;
   }
   return NULL;
}

int destroy_arrayList(ArrayList *arraylist) {
   if (arraylist != NULL) {
      NO *aux = arraylist->inicio;
      for (int i = 0; i < arraylist->numero; i++) {
         for (int j = 0; j < aux->fimvet; j++)
            apagar_item(&(aux->list[j]));//free em todos os ITEMs
         free(aux->list);//free na lista
         aux = aux->proximo;
         free(arraylist->inicio);//"apaga-se" o primeiro no
         arraylist->inicio = aux;//o primeiro no passa a ser o aux
      }
      free(arraylist);//"apaga-se" o array
   return 1;
   }
   return 0;
}

void print_arrayList(ArrayList *arraylist) {
   if (arraylist != NULL) {
      NO *aux = arraylist->inicio;
      for(int i = 0; i < arraylist->numero; i++) {
         for(int j = 0; j < aux->fimvet; j++) {//lembrando que fimvet sempre aponta para a proxima posicao a ser adicionada!
            imprimir_item(aux->list[j]);
         }
         printf("\n\n");
         aux = aux->proximo;//lembrando q o pior dos casos (acessar aux->proximo com aux = NULL), nao ocorre pois o for sempre termina antes!
      }
   }
}
