#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "heap.h"

/*** problema 2.1 ***/
vetor *heap_ordena(vetor *v)
{
    if (v == NULL)
        return NULL;

    heap *h = heap_nova(v->tamanho);
    if (h == NULL)
        return NULL;

    // insere todos os elementos do vetor na heap,
    // atribuindo-lhes a prioridade como definida no enunciado
    for (int i = 0; i < v->tamanho; i++)
    {
        char *str = v->elementos[i].str;
        int prioridade = (str[0] << 8) + str[1];
        if (heap_insere(h, str, prioridade) == 0)
        {
            heap_apaga(h);
            return NULL;
        }
    }

    vetor *v_ord = vetor_novo();
    if (v_ord == NULL)
    {
        heap_apaga(h);
        return NULL;
    }

    // insere todos os elementos da heap no final do vetor a retornar
    // (nota que inserir no final do vetor é mais eficiente do que inserir no início: O(1) vs. O(n))
    while (h->tamanho > 0)
    {
        char *str = heap_remove(h);
        if (vetor_insere(v_ord, str, -1) == -1)
        {
            vetor_apaga(v_ord);
            heap_apaga(h);
            return NULL;
        }
    }
    heap_apaga(h);

    // neste momento, o vetor está ordenado por ordem crescente
    // para o termos por ordem decrescente, invertemo-lo
    for (int i = 0; i < v_ord->tamanho / 2; i++)
    {
        v_elemento aux = v_ord->elementos[i];
        v_ord->elementos[i] = v_ord->elementos[v_ord->tamanho - i - 1];
        v_ord->elementos[v_ord->tamanho - i - 1] = aux;
    }

    return v_ord;
}

/*** problema 2.2 ***/
/*
complexidade do algoritmo:
O(n*log(n)), onde n é o tamanho do vetor

justificacao:
n operações de inserção na heap: n*O(log(n)) = O(n*log(n))
n operações de remoção na heap: n*O(log(n)) = O(n*log(n))
n operações de inserção no final do vetor: n*O(1) = O(n)
inversão do vetor: O(n)
total: O(n*log(n)) + O(n*log(n)) + O(n) + O(n) = O(n*log(n))
*/

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_LINE 100

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);

    /* teste problema 2.1 */
    {
        int i, j;
        char cidade[MAX_LINE];
        vetor *v, *res;
        FILE *fp;

        puts("* Problema 2.1 *");
        v = vetor_novo();
        fp = fopen("cidades.txt", "r");
        while (fgets(cidade, MAX_LINE, fp) != NULL)
        {
            *strchr(cidade, ',') = '\0';
            vetor_insere(v, cidade, v->tamanho);
        }
        res = heap_ordena(v);
        if (res != NULL)
        {
            for (i = 0; i < 3 && i < vetor_tamanho(res); i++)
                printf("%s\n", vetor_elemento(res, i));
            if (vetor_tamanho(res) > 3)
            {
                if (vetor_tamanho(res) > 6)
                    puts("...");
                j = i;
                if (vetor_tamanho(res) - 3 > j)
                    j = vetor_tamanho(res) - 3;
                for (i = j; i < vetor_tamanho(res); i++)
                    printf("%s\n", vetor_elemento(res, i));
            }
        }

        vetor_apaga(v);
        vetor_apaga(res);
    }

    return 0;
}
