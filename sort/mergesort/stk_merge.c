/* Implementation of the mergesort algorithm using a stack
 * instead of recursion.
 */

#include "stk.h"       /* STK_ */
#include "stk_merge.h" /* CMP_PROC_t, CMP_PROC_p_t */

/* Perform mergesort on a given array, using a given stack ID.
 * Mutate the array.
 *
 * Parameters
 *   array: pointer to array of void pointers
 *   stack: stack ID pointer
 *   numElements: number of elements in array to sort
 * 
 * Returns
 *   void
 * 
 * Notes
 *   Takes advantage of the stack data structure to avoid pointer
 *   arithmetic, making the algorithm easier to read and debug.
 *
 */
void stk_mergesort(
                   void **array,
                   STK_ID_t stack,
                   size_t numElements,
                   CMP_PROC_p_t compare_proc
                  )
{
    /* first, test if the stack we're going to use is NULL */
    if (stack == STK_NULL_ID)
    {
        stack = STK_create_stack(20);
    }

    /* now we get into the actual mergesort alg */
    if (numElements > 1)
    {
        /* divide into sub-arrays */
        size_t lowHalf  = numElements / 2; /* int division */
        size_t highHalf = numElements - lowHalf;
        void **array2   = array + lowHalf; /* simplified pointer arith */

        /* recursive calls */
        stk_mergesort(array, stack, lowHalf, compare_proc);
        stk_mergesort(array2, stack, highHalf, compare_proc);

        /* iterate through indices of array(s) */
        /* now we only need two indices as we aren't keeping track
         * of another dynamically allocated array
         */
        size_t i = 0, j = 0;

        /* first while loop compares the elements at each index in
         * the two arrays; compare_proc returns -1 (<) 0 (=) 1 (>)
         */
        while (i < (int)lowHalf && j < (int)highHalf)
        {
            /* dereference pointer to pointer, yielding pointer */
            if (compare_proc(array[i], array2[j]) < 0)
            {
                STK_push_item(stack, array[i++]); /* NOTE can use [i++]? */
                //++i;
            }
            else
            {
                STK_push_item(stack, array2[j++]);
                //++j;
            }
        }

        /* second and third while loops fill in the rest */
        while (i < (int)lowHalf)
        {
            STK_push_item(stack, array[i]);
            ++i;
        }

        while (j < (int)highHalf)
        {
            STK_push_item(stack, array2[j]);
            ++j;
        }

        /* now reverse the stack and assign back to array */
        i = numElements;
        while (i > 0)
        {
            array[--i] = STK_pop_item(stack);
            //--i;
        }
    }
}
