#include "insert.h"

/* NOTE
 * Is it possible to memoize this?
 */

void INSERT_sort_int_array(int *array, int N)
{
    /* initialize variables */
    int i, j, v;
    i = j = v = 0;

    /* begin outer loop */
    for (i=2; i<=N; ++i)
    {
        v = array[i];
        j = i;

        /* compare the elements "already considered" */
        while (array[j-1] > v)
        {
            /* set array[j] to the larger one, decrement counter */
            array[j] = array[j-1];
            --j;
        }
        /* set array[j], wherever that is, to the lower value v */
        array[j] = v;
    }
}
