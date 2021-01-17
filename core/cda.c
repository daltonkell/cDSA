/* "Principal source file" */

#include <stdlib.h>

void *CDA_calloc(size_t nitems, size_t size)
{
    /* Cover method for calloc; ensure
     * mem allocated is not NULL. Memory
     * contents are initialized to 0.
     */
    void *mem = calloc(nitems, size);
    if (mem == NULL && size > 0){abort();}
    return mem;
}

void *CDA_malloc(size_t size){
    /* Cover method for malloc; ensure mem
     * allocated is not NULL
     */

    void *mem = malloc(size); // allocate
    // abort if NULL and we requested mem
    if (mem == NULL && size > 0){abort();}

    return mem;
}

void CDA_free(void *mem){
    /* cover method for freeing memory;
     * only free memory if the pointer is
     * not NULL
     */

    if (mem != NULL){free(mem);}
}
