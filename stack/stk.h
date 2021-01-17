/* STACK public header */

/* NOTE
 * THIS DOES NOT IMPLEMENT A SEGMENTED STACK
 */

#ifndef STK_H
#define STK_H

#include "cda.h" // CDA_...
#include <stddef.h> // size_t

// incomplete declaration for stack ID
typedef struct stack__control_s *STK_ID_t;

// typedef for a stack mark
typedef int STK_MARK_t, *STK_MARK_p_t;

// macro for declaring a value for NULL stack ID
#define STK_NULL_ID (NULL)

// functions----------

/* Create a stack
 * 
 * Create a stack of a given size. Stack stores items of type
 * *void.
 * 
 * Parameters
 *   size: size of stack in number of items
 * 
 * Exceptions
 *   Throws SIGABRT on creation failure
 * 
 * Returns
 *   stack ID to to be used in all subsequent stack operations
 * 
 * Notes
 *   None
 */
STK_ID_t STK_create_stack(size_t size);

/* Push an item onto the stack
 * 
 * Parameters
 *   stack: stack ID
 *   item: item to push
 * 
 * Exceptions
 *   Throws SIGABRT on stack overflow
 * 
 * Returns
 *   mark representing the position of the pushed item
 * 
 * Notes
 *   None
 */
STK_MARK_t STK_push_item(STK_ID_t stack, void *item);

/* Get an item from the stack relative to a mark. Does
 * not decrement the stack pointer stack->sptr.
 *
 * Parameters
 *   stack : pointer to stack
 *   mark  : mark in the stack
 *   offset: position relative to the mark
 * 
 * Returns
 *   *void item at the position
 * 
 * Exceptions
 *   Throws SIGABRT if mark (or offset + mark) exceeds bounds of stack->sptr
 */
void *STK_get_item(STK_ID_t stack, STK_MARK_t mark, int offset);

/* Substitute a ptr to an item in the place of an existing one.
 * Does not increment/decrement stack->sptr.
 * 
 * Parameters
 *   stack : ptr to stack
 *   mark  : mark in the stack
 *   offset: place to index stack relative to mark
 *   val   : item to exchange
 * 
 * Returns
 *   void
 * 
 * Exceptions
 *   Throws SIGABRT if mark or mark+offset exceeds stack bounds
 */
void STK_change_item(STK_ID_t stack, STK_MARK_t mark, int offset, void *val);

/* Pop an item from the stack
 * 
 * Parameters
 *   stack: stack ID
 * 
 * Exceptions
 *   See notes
 * 
 * Returns
 *   Top item of the stack
 * 
 * Notes
 *   Function contains an assertion which throws SIGABRT if the user
 *   attempts to illegally remove an item from an empty stack.
 *   Assertion disabled in production code.
 */
void *STK_pop_item(STK_ID_t stack);

/* Peek - get the top item without removing it
 * 
 * Parameters
 *   stack: stack ID
 * 
 * Exceptions
 *   See notes
 * 
 * Returns
 *   Value at top of stack
 * 
 * Notes
 *   Throws SIGABRT if user tries to peek at an empty stack.
 *   Assertion is disabled in production code.
 */
void *STK_peek_item(STK_ID_t stack);

/* GRAB STACK SPACE
 * Grab ununsed space in the stack, which essentially means
 * the stack pointer is advanced to this and skips over it.
 * 
 * Parameters
 *   stack: ptr to stack
 *   num_slots: number of spaces to grab (skip)
 * 
 * Returns
 *   STK_MARK_t position of unoccupied stack space
 * 
 * Exceptions
 *   Throws SIGABRT if num_slots + stack->sptr exceeds stack size.
 */
STK_MARK_t STK_grab_stack_space(STK_ID_t stack, int num_slots);

/* Check if stack is empty
 * 
 * Parameters
 *   stack: stack ID
 * 
 * Exceptions
 *   None
 * 
 * Returns
 *   CDA_TRUE if stack empty, otherwise CDA_FALSE
 * 
 * Notes
 *   None
 */
CDA_BOOL_t STK_is_stack_empty(STK_ID_t stack);

/* Check if stack is full
 * 
 * Parameters
 *   stack: stack ID
 * 
 * Exceptions
 *   None
 * 
 * Returns
 *   CDA_TRUE if stack full, otherwise CDA_FALSE
 * 
 * Notes
 *   None
 */
CDA_BOOL_t STK_is_stack_full(STK_ID_t stack);

/* Clear a stack up to a certain mark, removing those
 * items from the stack.
 *  
 * Parameters
 *   stack: ptr to stack
 *   mark : mark to clear to
 * 
 * Returns
 *   void
 * 
 * Exceptions
 *   Throws SIGABRT if mark exceeds stack bounds.
 */
void STK_clear_to_mark(STK_ID_t stack, STK_MARK_t mark);

/* Clear a stack, removing all items
 * 
 * Parameters
 *   stack: stack ID
 * 
 * Exceptions
 *   None
 * 
 * Returns
 *   void
 * 
 * Notes
 *   None
 */
void STK_clear_stack(STK_ID_t stack);

/* Destroy a stack, freeing all associated resources.
 * 
 * Parameters
 *   stack: stack ID
 * 
 * Exceptions
 *   None
 * 
 * Returns
 *   STK_NULL_ID
 * 
 * Notes
 *   None
 */
STK_ID_t STK_destroy_stack(STK_ID_t stack);
// ----------functions

#endif
