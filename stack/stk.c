#include "stkp.h" // STK__CONTROL_p_t, STK_ID_t
#include "stdlib.h"

// function implementations -----------
STK_ID_t STK_create_stack(size_t size)
{
    // create control structure
    STK__CONTROL_p_t stack = (STK__CONTROL_p_t)CDA_NEW(STK__CONTROL_p_t);

    // allocate mem set stack pointer to point at it;
    // NOTE that CDA_calloc will throw SIGABRT if it can't
    // create the memory
    stack->stack = CDA_calloc(size, sizeof(void*));
    stack->sptr  = stack->stack;

    // set the stack size as passed
    stack->size = size;

    // cast pointer, return
    return (STK_ID_t)stack;
}

STK_MARK_t STK_push_item(STK_ID_t stack, void *item)
{

    // use STK_is_stack_full to check if stack overflow will occur
    CDA_ASSERT(STK_is_stack_full(stack)==CDA_FALSE);

    // index at the current position of this item
    STK_MARK_t mark = stack->sptr - stack->stack;

    // store the item at the location pointed to by sptr
    // then increment the sptr
    *stack->sptr = item;
    ++stack->sptr;

    return mark;
}

void *STK_get_item(STK_ID_t stack, STK_MARK_t mark, int offset)
{
    /* A few assertions to ensure the indexed value is legal:
     *  - stack & stack+offset are >= stack (upper bound)
     *  - stack & stack+offset < stack->sptr (lower bound)
     */
    CDA_ASSERT(stack->stack + mark >= stack->stack);
    CDA_ASSERT(stack->stack + mark < stack->sptr);
    CDA_ASSERT(stack->stack + mark + offset >= stack->stack);
    CDA_ASSERT(stack->stack + mark + offset <stack->sptr);

    /* ptr arithmetic to the desired spot, then dereference */
    return *(stack->stack + mark + offset);
}

void STK_change_item(STK_ID_t stack, STK_MARK_t mark, int offset, void *val)
{

    /* Quite literally almost the same code as STK_get_item */

    /* A few assertions to ensure the indexed value is legal:
     *  - stack & stack+offset are >= stack (upper bound)
     *  - stack & stack+offset < stack->sptr (lower bound)
     */
    CDA_ASSERT(stack->stack + mark >= stack->stack);
    CDA_ASSERT(stack->stack + mark < stack->sptr);
    CDA_ASSERT(stack->stack + mark + offset >= stack->stack);
    CDA_ASSERT(stack->stack + mark + offset <stack->sptr);

    /* ptr arithmetic to the desired spot, then dereference and assign val */
    *(stack->stack + mark + offset) = val;
}

void *STK_peek_item(STK_ID_t stack)
{
    // first assert that the stack isn't empty,
    // then return the top item w/o decrementing
    CDA_ASSERT(stack->sptr != stack->stack);
    return *(stack->sptr - 1);
}

STK_MARK_t STK_grab_stack_space(STK_ID_t stack, int num_slots)
{
    CDA_ASSERT( !( (size_t*)(stack->sptr + num_slots) >= (size_t*)(stack + stack->size) ));
    stack->sptr += num_slots;
    return stack->sptr - stack->stack - 1;
}

void *STK_pop_item(STK_ID_t stack)
{
    CDA_ASSERT(stack->sptr != stack->stack);
    // decrement, then return the value pointed at
    --stack->sptr;
    return *(stack->sptr);
}

CDA_BOOL_t STK_is_stack_empty(STK_ID_t stack)
{
    // if stack pointer points at itself, it's considered empty
    return stack->sptr == stack->stack ? CDA_TRUE : CDA_FALSE;
}

CDA_BOOL_t STK_is_stack_full(STK_ID_t stack)
{
    // stack is full if difference between stack-stack and
    // stack->sptr == stack->size
    return (stack->sptr - stack->stack) == stack->size ? CDA_TRUE : CDA_FALSE;
}

void STK_clear_to_mark(STK_ID_t stack, STK_MARK_t mark)
{
    /* ensure the mark does not exceed stack bounds */
    CDA_ASSERT(stack->stack + mark >= stack->stack);
    CDA_ASSERT(stack->stack + mark < stack->sptr);
    stack->sptr = stack->stack + mark;
}

void STK_clear_stack(STK_ID_t stack)
{

    // check if the stack is NULL, if so, do nothing
    if (stack == STK_NULL_ID)
    {
    }
    // simply make the stack pointer point at itself!
    stack->sptr = stack->stack;
}

STK_ID_t STK_destroy_stack(STK_ID_t stack)
{
    // check if the stack is NULL, if so, return the same thing
    if (stack == STK_NULL_ID)
    {
        return stack;
    }
    // free the memory that was dynamically allocated to the stack
    CDA_free(stack->stack);
    CDA_free(stack);
    return STK_NULL_ID;
}
