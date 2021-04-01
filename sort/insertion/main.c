#include <stdio.h>
#include "insert.h"

int main()
{

    /* trivial driver program to display selection sort */
    /* NOTE sentinel value of 0 at a[0] */
    int a[11] = {0, 55, 6, 23, 7, 8, 8, 5, 4, 3, 10};

    printf("Array before insertion sort\n");
    for (int i=1; i<11; ++i)
    {
        printf("pos: %i | value: %i\n", i, a[i]);
    }
    printf("\n");

    /* invoke selsort */
    INSERT_sort_int_array(a, 11);

    printf("Array after insertion sort\n");
    for (int i=1; i<11; ++i)
    {
        printf("pos: %i | value: %i\n", i, a[i]);
    }
    printf("\n");
    
    return 0;
}
