#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
lista* junta_nomes(lista *lst1, lista *lst2)
{
	/* complexidade do algoritmo: O(n1+n2) onde n1 e n2 são os tamanhos de lst1 e lst2, respetivamente */
	if(!lst1 && !lst2)
		return NULL;

	lista *lst = lista_nova();
	if(!lst)
		return NULL;

	// insere todos os elementos de lst1 em lst
	for(l_elemento *elem = lst1->inicio; elem != NULL; elem = elem->proximo)
	{
		if(lista_insere(lst, elem->str, NULL) == NULL)
		{
			lista_apaga(lst);
			return NULL;
		}
	}

	// insere todos os elementos de lst2 em lst
	for(l_elemento *elem = lst2->inicio; elem != NULL; elem = elem->proximo)
	{
		if(!lista_insere(lst, elem->str, NULL))
		{
			lista_apaga(lst);
			return NULL;
		}
	}

	return lst;
}

/*** problema 1.2 ***/
lista* lista_remove_duplicados(lista *lst)
{
	if(!lst || lst->tamanho==0)
		return NULL;

	lista *lst_dup = lista_nova();
	if(!lst_dup)
		return NULL;

	for(l_elemento *elem1 = lst->inicio; elem1 != NULL; elem1 = elem1->proximo)
	{
		// printf("elem1: %s\n", elem1->str);
		for(l_elemento *elem2 = elem1->proximo; elem2 != NULL; elem2 = elem2->proximo)
		{
			// printf("elem2: %s\n", elem2->str);
			// se encontrar um elemento repetido, insere-o na nova lista e remove-o da lista original
			if(strcmp(elem1->str, elem2->str) == 0)
			{
				if(!lista_insere(lst_dup, elem2->str, NULL))
					return NULL;

				elem2 = lista_remove(lst, elem2);  // a função retorna apontador para elem2->proximo
				if(elem2)
					elem2 = elem2->anterior;  // recua uma posição para compensar o ciclo for
				else  // se retornou NULL, salta fora do segundo for
					break;
			}
		}
	}

	return lst_dup;
}

/*** problema 1.3 ***/
fila* pesquisa_nomes(lista *lst, char *nome)
{
	if(!lst || lst->tamanho == 0 || !nome)
		return NULL;

	fila *f = fila_nova();
	if(!f)
		return NULL;

	for(l_elemento *elem = lst->inicio; elem != NULL; elem = elem->proximo)
	{
		// se nome for uma substring de elem->str, insere elem->str na fila
		if(strstr(elem->str, nome) != NULL)
		{
			if(fila_push(f, elem->str) == -1)
			{
				fila_apaga(f);
				return NULL;
			}
		}
	}

	return f;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

void lerParaLista(FILE* ficheiro, lista* l)
{
	char buffer[256], *nlptr;

	if (ficheiro == NULL || l == NULL)
		return;

	while(fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
		*nlptr = '\0';
		lista_insere(l,buffer,NULL);
	}
}

int main()
{
	FILE *f;
	lista *l1=NULL, *l2=NULL, *l12=NULL, *l=NULL, *duplicados=NULL;
	fila *resultado=NULL;
	l_elemento *e;

	/* testes */
	f = fopen("nomes1.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l12 = lista_nova();
	l1 = lista_nova();
	lerParaLista(f, l1);
	rewind(f);
	lerParaLista(f, l12);
	fclose(f);

	f = fopen("nomes2.txt","r");
	if(f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l2 = lista_nova();
	lerParaLista(f, l2);
	rewind(f);
	lerParaLista(f, l12);
	fclose(f);

	/* inicio teste prob1.1 */
	l = junta_nomes(l1, l2);
	if(l)
		printf("\nLista resultante contem %d nomes.\n", lista_tamanho(l));
	else
		printf("\njunta_nomes retornou NULL\n");
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	duplicados = lista_remove_duplicados(l12);
	if(duplicados)
	{
		int n=0;
		printf("\nNomes duplicados (total de %d):\n", lista_tamanho(duplicados));
		for (e = duplicados->inicio; e != NULL && n<3; e = e->proximo, n++)
			printf("%s\n", e->str);
		if(lista_tamanho(duplicados)>5)
		{
			puts("...");
			for ( ; e->proximo != NULL; e = e->proximo);
			printf("%s\n", e->str);
		}
		else
			for ( ; e != NULL; e = e->proximo)
				printf("%s\n", e->str);
		if(lista_tamanho(l12) != 302)
			printf("Nem todos os nomes duplicados foram removidos da lista (tamanho: %d; esperado: 302)\n", lista_tamanho(l12));
	}
	else
		printf("\nlista_remove_duplicados retornou NULL\n");
	/* fim teste prob1.2 */

	/* inicio teste prob1.3 */
	resultado = pesquisa_nomes(l1, "SILVA");
	if(resultado)
	{
		int n=0;
		printf("\nNomes encontrados (%d): \n", fila_tamanho(resultado));
		while (!fila_vazia(resultado) && n<3) {
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
			n++;
		}
		if(fila_tamanho(resultado) > 2)
		{
			puts("...");
			while (fila_tamanho(resultado) > 1)
				fila_pop(resultado);
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
		}
		else {
			while (!fila_vazia(resultado)) {
					printf("%s\n", fila_front(resultado));
					fila_pop(resultado);
				}
		}
	}
	else
		printf("\npesquisa_nomes retornou NULL\n\n");
	/* fim teste prob1.3 */

	lista_apaga(l);
	lista_apaga(l1);
	lista_apaga(l2);
	lista_apaga(duplicados);
	fila_apaga(resultado);

	return 0;
}
