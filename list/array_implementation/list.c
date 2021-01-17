/* Array implementation of LIST */

#include <stdio.h>

#ifndef CDA_H
#include "cda.h"
#endif

#include "listp.h"

LIST_ID_t LIST_create_list(
    size_t max_list_size,
    size_t entry_size,
    const char *name
    )
{
    // allocation memory for the control member
    LIST__CONTROL_p_t list = CDA_NEW(LIST__CONTROL_t);

    // allocate memory for the array to hold the rest of the items,
    // then set the necessary fields in the structure
    list->array      = CDA_calloc(max_list_size, entry_size);
    list->max_size   = max_list_size;
    list->entry_size = entry_size;
    list->next       = 0;
    list->name       = CDA_NEW_STR_IF(name);

    return list;
}

const void *LIST_add_entry(LIST_ID_t list, const void *data)
{
    // create nextEntry w/ pointer arith; if max reached,
    // abort
    if (list->next >= (int)list->max_size){abort();}
    LIST__ENTRY_p_t nextEntry =
        list->array + (list->next * list->entry_size);

    // copy data into nextEntry
    memmove(nextEntry, data, list->entry_size);
    // increment next
    ++list->next;

    return data;
}

LIST_ID_t LIST_traverse_list(
    LIST_ID_t list,
    LIST_TRAVERSAL_PROC_p_t traversal_proc
    )
{
    LIST__ENTRY_p_t entry = list->array;
    int idx = 0;

    for (idx=0; idx<list->next; ++idx)
    {
        if (traversal_proc == NULL)
        {
            printf("Doing nothing, traversal_proc == NULL\n");
        }
        else
        { // actually call the function
            traversal_proc(entry);
        }

        // need to advance the pointer
        entry += list->entry_size;
    }

    return list;
}

CDA_BOOL_t LIST_is_list_empty(LIST_ID_t list)
{
    // list is empty if next is 0
    return list->next == 0 ? CDA_TRUE : CDA_FALSE;
}

CDA_BOOL_t LIST_is_list_full(LIST_ID_t list)
{
    // list empty iff next >= max
    return list->next < list->max_size ? CDA_FALSE : CDA_TRUE;
}

size_t LIST_get_list_size(LIST_ID_t list)
{
    // nelements = next + 1
    return list->next + 1;
}

LIST_ID_t LIST_clear_list(
    LIST_ID_t             list,
    LIST_DESTROY_PROC_p_t destroy_proc
    )
{
    // iterate over elements in list, removing
    LIST__ENTRY_p_t entry = list->array;
    int idx = 0;

    for (idx=0; idx<list->next; ++idx)
    {
        if (destroy_proc == NULL)
        {
            // nothing to do here
            printf("User passed a NULL destroy_proc\n");
        }
        else
        {   // actually call the function
            printf("Destroying element %i ...\n", idx);
            destroy_proc(entry);
        }

        // need to advance the pointer to the array
        entry += list->entry_size;
    }

    // "remove elements" by setting next to 0
    list->next = 0;

    return list;
}

LIST_ID_t LIST_destroy_list(
    LIST_ID_t list,
    LIST_DESTROY_PROC_p_t destroy_proc
    )
{

    printf("CLEARING LIST\n");
    // clear list
    LIST_clear_list(list, destroy_proc);

    printf("LIST CLEAR, FREEING MEMORY FROM LIST\n");

    // free list->array and list->name
    CDA_free(list->array);
    CDA_free(list->name);

    return list;
}
