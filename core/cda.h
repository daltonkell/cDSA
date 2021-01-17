/* Public header */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

// macros
#define CDA_TRUE               (1)
#define CDA_FALSE              (0)

#define CDA_ASSERT( exp )      (assert( (exp) ))
#define CDA_CARDINALITY( arr ) (sizeof( (arr) )/sizeof( *(arr) ))
#define CDA_NEW( type )        ((type *)CDA_malloc( sizeof(type) ))
#define CDA_NEW_STR( str )     (strcpy( (char *)CDA_malloc( strlen( str ) + 1), (str)) ) 
#define CDA_NEW_STR_IF( str )  ((str) == NULL ? NULL : CDA_NEW_STR( (str) ))

// equivalence types, help with portability
typedef int           CDA_BOOL_t;
typedef signed char   CDA_INT8_t;  // char == 1 byte, 8 bits
typedef unsigned char CDA_UINT8_t; 


// function prototypes
void *CDA_calloc(size_t nitems, size_t size);
void *CDA_malloc(size_t size);
void CDA_free(void *mem);
