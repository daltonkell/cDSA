#include <stdio.h>
#include "mergesort.h" // mergesort, CMP_PROC_t, CMP_PROC_p_t

int compare_equality_int_values(const void *v1, const void *v2)
{
    if ( *(int*)(v1) < *(int*)(v2) )
    {
        return -1;
    }
    else if ( *(int*)(v1) == *(int*)(v2) )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int main()
{
    // declare array
    int array[5] = {2, 31, 1, 24, 6};

    printf("Original: \n");
    for (int i=0; i<5; ++i){ printf("%d, ", array[i]); }
    printf("\n");

    // sort
    mergesort((void*)array, 5, 4, (CMP_PROC_p_t)compare_equality_int_values);

    printf("Sorted: \n");
    for (int i=0; i<5; ++i){ printf("%d, ", array[i]); }

    return 0;
}
