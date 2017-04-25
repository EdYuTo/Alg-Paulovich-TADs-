//EDSON YUDI TOMA 9791305

#include "item.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[ ]) {
   char *command = (char *)malloc(32*sizeof(char));
   int sair = 0;
   LISTA_LIGADA *lista;

   lista = criar_lista();

   do {
      scanf("%s", command);
      
      if(strcmp(command,"sair") == 0) {
         sair = 1;

      } else if(strcmp(command,"cadastrar") == 0) {
         char *primeiro_nome = (char *)malloc(16);
            scanf("%s", primeiro_nome);

         char *ultimo_nome = (char *)malloc(16);
            scanf("%s", ultimo_nome);

         char *cpf = (char *)malloc(16);
            scanf("%s", cpf); 

         char *telefone = (char *)malloc(21);
            scanf("%s", telefone);

         inserir_item(lista, 
            criar_item(primeiro_nome, ultimo_nome, cpf, telefone));

      } else if(strcmp(command,"buscar") == 0) {
         char *cpf2 = (char *)malloc(16);
         scanf("%s", cpf2); //cpf
         imprimir_item(retornar_item(lista, cpf2));
	 free(cpf2);

      } else if(strcmp(command,"remover") == 0) {
         char *cpf3 = (char *)malloc(16);
         scanf("%s", cpf3); //cpf
         remover_item(lista, cpf3);
	 free(cpf3);

      } else if(strcmp(command,"dump") == 0) {
         imprimir(lista);
      }
   } while(!sair);

   free(command);
   apagar_lista(lista);

   return 0;
}
/*
comentarios:
   na parte de cadastrar, os valores foram declarados dentro do if para
q pudessem ser alocados e salvos dentro da lista (lembrando que eles 
serao liberados quando a lista for apagada);
   quanto ao 'buscar' e 'remover' o valor de cpf e utilizado e liberado
(poderia se declarado fora no comeco do codigo)
*/
