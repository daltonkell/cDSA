#include "stk.h"
#include <stddef.h>
#include <stdio.h>

int main()
{

    // create stack
    STK_ID_t stack = STK_create_stack(1);
    STK_MARK_t mark = 0;

    // show stack is empty
    assert(STK_is_stack_empty(stack) == CDA_TRUE);
    assert(STK_is_stack_full(stack)  == CDA_FALSE);

    // push item onto stack
    int x = 7;
    mark = STK_push_item(stack, &x);

    printf("Mark should be 0: %i\n", mark);

    // check stack is full
    assert(STK_is_stack_full(stack) == CDA_TRUE);

    // peek the item
    int * x_1 = (int *)STK_peek_item(stack);
    printf("Peeked %i from top of stack\n", *x_1);

    // assert stack still full
    assert(STK_is_stack_full(stack) == CDA_TRUE);
    assert(STK_is_stack_empty(stack) == CDA_FALSE);

    // pop the item from the stack, print it
    int * x_2 = (int *)STK_pop_item(stack);
    printf("Popped %i from top of stack\n", *x_2);

    // assert stack empty
    assert(STK_is_stack_empty(stack) == CDA_TRUE);
    assert(STK_is_stack_full(stack) == CDA_FALSE);
    
    // clear the stack
    STK_clear_stack(stack);

    // destroy the stack
    stack = STK_destroy_stack(stack);

    assert(stack == NULL);

    return 0;
}
