#include <stdio.h>
#include <string.h>

#ifndef CDA_H
#include "cda.h" // CDA_malloc, CDA_free
#endif

// a char is one byte
typedef unsigned char BYTE_t;

// type aliases for comparison; this "creates" a type of
// function that returns int with parameters (const void*, const void*)
typedef int CMP_PROC_t(const void*, const void*);
typedef CMP_PROC_t *CMP_PROC_p_t; // so we can pass the pointer to the function

void mergesort( void         *array,
                size_t       num_ele,
                size_t       ele_size,
                CMP_PROC_p_t cmp_proc
              );
