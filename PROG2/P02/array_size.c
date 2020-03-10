#include <stdlib.h>
#include <stdio.h>
#define LEN 16

size_t length(int *v)
{
    return sizeof(v)/sizeof(int);
}

int *new_array(size_t len)
{
    return (int *)malloc(len*sizeof(int));
}

int main()
{
    int v[LEN];
    int *w = (int *)malloc(LEN*sizeof(int));
    int *u = new_array(LEN);

    printf("sizeof(int) = %lu, sizeof(int*) = %lu\n\n", sizeof(int), sizeof(int*));

    /* The line below will produce the correct result, because v is an automatic
    array and it was created inside the current function. */
    size_t v_len = sizeof(v)/sizeof(int);

    /* The line below will produce an incorrect result, because w is a dynamic array,
    so the operator sizeof sees w as a pointer. Therefore, the result will be sizeof(int*)/sizeof(int). */
    size_t w_len = sizeof(w)/sizeof(int);

    /* The line below will produce an incorrect result, for the same reason as in the previous example.
    The result will be sizeof(int*)/sizeof(int). */
    size_t u_len = sizeof(u)/sizeof(int);
    printf("Length of arrays in main():\n");
    printf("v_len = %lu, w_len = %lu, u_len = %lu\n\n", v_len, w_len, u_len);

    /* The line below will produce an incorrect result. Although v is an automatic array,
    when it is used inside the function length() it is seen as a pointer.
    Therefore, the result will be sizeof(int*)/sizeof(int). */
    v_len = length(v);

    /* The line below will produce an incorrect result, because the array w is dynamic.
    The result will be sizeof(int*)/sizeof(int). */
    w_len = length(w);

    /* The line below will produce an incorrect result, for the same reason as in the previous example.
    The result will be sizeof(int*)/sizeof(int). */
    u_len = length(u);
    printf("Length of arrays determined by length():\n");
    printf("v_len = %lu, w_len = %lu, u_len = %lu\n\n", v_len, w_len, u_len);

    return 0;
}