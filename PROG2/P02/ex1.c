#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

size_t get_odd_numbers(int *v, size_t v_len, bool get_odd, int **v_odd)
{
    *v_odd = (int *)malloc(v_len*sizeof(int));
    if(!v_odd)
    {
        printf("Falha ao alocar %d bytes de memória", (int)(v_len*sizeof(int)));
        return 0;
    }
    size_t n_odd=0;

    for(int i=0; i < v_len; i++)
        if(v[i]%2 == get_odd){
            n_odd++;
            (*v_odd)[n_odd-1] = v[i];
        }

    *v_odd = (int *)realloc(*v_odd, n_odd*sizeof(int));
    if(!v_odd)
    {
        printf("Falha ao realocar %d bytes de memória", (int)(n_odd*sizeof(int)));
        return 0;
    }

    return n_odd;
}

int main()
{
    size_t N;
    printf("Número de elementos? ");
    scanf("%lu", &N);

    int *V = (int *)malloc(N*sizeof(int));
    if(!V)
    {
        printf("Falha ao alocar %lu bytes de memória", N*sizeof(int));
        return -1;
    }

    for(int i=0; i<N; i++)
    {
        printf("Introduza %dº elemento: ", i+1);
        scanf("%d", V+i);
    }
    printf("\n");

    int *V_even=NULL, *V_odd=NULL;
    size_t N_even = get_odd_numbers(V, N, false, &V_even);
    size_t N_odd = get_odd_numbers(V, N, true, &V_odd);

    if(N_even==-1 || N_odd==-1) return -1;

    printf("Vetor original: [ ");
    for(int i=0; i<N; i++) printf("%d ", V[i]);
    printf("]\n");

    printf("Números pares: [ ");
    for(int i=0; i<N_even; i++) printf("%d ", V_even[i]);
    printf("]\n");

    printf("Números ímpares: [ ");
    for(int i=0; i<N_odd; i++) printf("%d ", V_odd[i]);
    printf("]\n");

    free(V); free(V_even); free(V_odd);
    V = NULL; V_even = NULL; V_odd = NULL;

    return 0;
}
