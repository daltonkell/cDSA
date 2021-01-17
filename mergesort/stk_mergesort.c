#include "stk.h"
#include "stk_merge.h"
#include <stdio.h>

/* function to compare ints from void pointers */
int compare_int(void *x, void *y)
{
    if (*(int*)x < *(int*)y) return -1;
    else if (*(int*)x == *(int*)y) return 0;
    else return 1;
}

int main()
{
    
    /* create stack with NULL id
     * create array to sort (int for now)
     */
    STK_ID_t stack = STK_NULL_ID;
    int array[]      = {69, 43, 1, 72, 5, 25, 44};
    int *i_array_p[] = { &array[0], &array[1], &array[2], &array[3], &array[4], &array[5], &array[6]};

    printf("Array before sorting: ");
    for (int i=0; i<7; ++i)
    {
        printf("%i ", array[i]);
    }
    printf("\n");

    /* sort */
    /* NOTE function name decays to ptr */
    stk_mergesort((void*)i_array_p, stack, 7, (CMP_PROC_p_t)compare_int);

    printf("Array after sorting: ");
    for (int i=0; i<7; ++i)
    {
        //printf("%i ", array[i]);
        printf("%i ", *(i_array_p[i]));
    }
    printf("\n");

    /* clear the stack, destroy stack */
    /* TODO these core dump? are you trying to free NULL? */
    STK_clear_stack(stack);
    STK_destroy_stack(stack);

    return 0;

}
