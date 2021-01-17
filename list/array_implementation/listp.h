/* LIST private header */
#ifndef LISTP_H
#define LISTP_H

#include "list.h"
#include <stddef.h>

typedef char *LIST__ENTRY_p_t;

// list ID will be opaque, which will be included
// in the header file
typedef struct list__control_s
{
    LIST__ENTRY_p_t array;
    size_t          max_size;
    size_t          entry_size;
    int             next;
    char            *name;
} LIST__CONTROL_t, *LIST__CONTROL_p_t;

#endif
