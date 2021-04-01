#include <stdio.h>
#include <string.h>

#include "cda.h" // CDA_malloc, CDA_free
#include "mergesort.h" // mergesort, BYTE_t, CMP_PROC_t, CMP_PROC_p_t

// implement mergesort algorithm
void mergesort( void         *array,
                size_t       num_ele,
                size_t       ele_size,
                CMP_PROC_p_t cmp_proc
              )
{
    if (num_ele > 1)
    {
        size_t lower_half = num_ele / 2; // floor division
        size_t upper_half = num_ele - lower_half;

        // a char is a sinlge byte; if we have a pointer to
        // the first byte of one element in the array, and then
        // increase the value of said pointer by the size of an
        // element, we should arrive at the address of the next
        // element
        BYTE_t *array1    = array;
        BYTE_t *array2    = array + (lower_half * ele_size);

        // recursive calls
        mergesort((void*)array1, lower_half, ele_size, cmp_proc);
        mergesort((void*)array2, upper_half, ele_size, cmp_proc);

        // indices for arrays, temporary array
        size_t i = 0, j = 0, k = 0;

        // create temporary array
        void *tmp = CDA_malloc(num_ele * ele_size);

        // first while loop - grab the lower value of each index;
        // the cmp_proc returns either -1 (<), 0 (=), 1 (>)
        while (i < (int)lower_half && j < (int)upper_half)
        {
            if (cmp_proc(array1 + i*ele_size,
                         array2 + j*ele_size
                        ) < 0
            )
            {
                // assign value of array1 to tmp using memcpy
                memcpy(tmp + k*ele_size, array1 + i*ele_size, ele_size);

                // critical! incremement pointers used
                ++i;
                ++k;
            }
            else
            {
                // assign value of array2 to tmp using memcpy
                memcpy(tmp + k*ele_size, array2 + j*ele_size, ele_size);

                // incremement pointers used
                ++j;
                ++k;
            }
        }

        // second and third while loops; once the lower values
        // have been exhausted, we still need to account for the
        // remaining higher values

        // for remaining values in array1
        while (i < (int)lower_half)
        {
            memcpy(tmp + k*ele_size, array1 + i*ele_size, ele_size);
            ++i;
            ++k;
        }

        // for remaining values in array2
        while (j < (int)upper_half)
        {
            memcpy(tmp + k*ele_size, array2 + j*ele_size, ele_size);
            ++j;
            ++k;
        }

        // finally, we must copy tmp back to array
        memcpy(array, tmp, ele_size * num_ele);

        // free temporary array
        CDA_free(tmp);

    }
}
