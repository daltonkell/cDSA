#ifndef STK_H
#include "stk.h"
#endif

#ifndef STK_MERGE_H
#define STK_MERGE_H

// type aliases for comparison; this "creates" a type of
// function that returns int with parameters (const void*, const void*)
typedef int CMP_PROC_t(const void*, const void*);
typedef CMP_PROC_t *CMP_PROC_p_t; // so we can pass the pointer to the function

void stk_mergesort(
                   void **array,
                   STK_ID_t stack,
                   size_t numElements,
                   CMP_PROC_p_t compare_proc
                  );
#endif
