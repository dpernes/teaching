#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
    if((comprimento < 1) || (altura < 1))
        return NULL;

    armazem *armz = (armazem*)malloc(sizeof(armz));
    if(!armz)
        return NULL;

    armz->comprimento = comprimento;
    armz->altura = altura;
    armz->contentores = fila_nova();
    if(!(armz->contentores))
    {
        free(armz);
        return NULL;
    }

    return armz;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
    if(!armz || (fila_tamanho(armz->contentores) == 0))
        return 1;

    return 0;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
    if(!armz)
        return 0;
    if((fila_tamanho(armz->contentores) >= armz->comprimento)
       && (fila_back(armz->contentores)->tamanho >= armz->altura))
       return 1;

    return 0;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
    if(!armz || !contr || armazem_cheio(armz))
        return 0;

    pilha *back = fila_back(armz->contentores);  // última pilha da fila
    if(back && (back->tamanho < armz->altura))  // se pilha criada e com espaço livre
        pilha_push(back, contr);  // adiciona novo contentor
    else  // se pilha não criada ou cheia
    {
        back = pilha_nova();  // cria a pilha
        if(!back)
            return 0;
        fila_push(armz->contentores, back);  // adiciona-a à fila
        pilha_push(back, contr);  // adiciona novo contentor à nova pilha
    }

    return 1;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
    if(!armz || armazem_vazio(armz))
        return NULL;

    pilha *front = fila_front(armz->contentores);  // primeira pilha da filha
    contentor *top = pilha_top(front);  // contentor no topo da primeira pilha
    contentor *contr = contentor_novo(top->destino, top->valor);  // copia para um novo contentor

    pilha_pop(front);  // apaga o contentor top
    if(pilha_tamanho(front) == 0)  // se a pilha front ficar vazia, apaga-a
        fila_pop(armz->contentores);

    return contr;
}
