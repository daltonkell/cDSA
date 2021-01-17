#ifndef STKP_H
#define STKP_H

#include "stk.h"
#include <stddef.h> // size_t


// typedef declaration for control structure
typedef struct stack__control_s
{
    void   **stack;
    void   **sptr;
    size_t size;
} STK__CONTROL_t, *STK__CONTROL_p_t;

#endif
