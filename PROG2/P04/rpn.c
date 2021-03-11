#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "pilha.h"

#define MAX_LEN 128
#define ERROR_VAL 999999

int rpn_calcula(char* expressao)
{
    pilha *p = pilha_nova();
    char *tok = strtok(expressao, " ");  // percorre a string dada pelas substrings separadas por espaços
    while(tok)
    {
        if((tok[0] >= '0') && (tok[0] <= '9'))  // se for um número
        {
            int elemento = atoi(tok);  // converte a string para o inteiro correspondente
            pilha_push(p, elemento);  // e guarda o inteiro na pilha
        }
        else  // se for um operador (+, -, *, / ou %)
        {
            int op2 = pilha_top(p);  // retira os dois elementos no topo da pilha
            pilha_pop(p);
            int op1 = pilha_top(p);
            pilha_pop(p);
            int res;
            switch(tok[0])  // efetua a operação correspondente ao operador dado
            {
                case '+':  // soma
                    res = op1 + op2;
                    break;
                case '-':  // subtração
                    res = op1 - op2;
                    break;
                case '*':  // multiplicação
                    res = op1 * op2;
                    break;
                case '/':  // divisão inteira
                    res = op1 / op2;
                    break;
                case '%':  // resto da divisão inteira
                    res = op1 % op2;
                    break;
                default:  // operadores desconhecidos são erro
                    pilha_apaga(p);
                    return ERROR_VAL;
            }
            pilha_push(p, res);  // guarda o resultado da operação na pilha
        }
        tok = strtok(NULL, " ");  // avança para a substring seguinte
    }

    int res = pilha_top(p);  // o resultado final é o valor que resta na pilha
    pilha_pop(p);
    if(pilha_tamanho(p) != 0)  // se a pilha não ficou vazia no fim, algo correu mal
    {
        pilha_apaga(p);
        return ERROR_VAL;
    }
    pilha_apaga(p);

    return res;
}

int main()
{
    char rpn_expr[MAX_LEN+1];
    printf("Expressão: ");
    fgets(rpn_expr, MAX_LEN, stdin);
    rpn_expr[strlen(rpn_expr)-1] = '\0';

    int res = rpn_calcula(rpn_expr);
    printf("Resultado: %d\n", res);

    return 0;
}
