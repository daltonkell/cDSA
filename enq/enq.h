#ifndef ENQ_H
#define ENQ_H

#include <stdbool.h>
#include <stdio.h>
#include "cda.h"

// list macros operate on list w/o queueing/dequeuing
// macros not type-checked
#define ENQ_GET_HEAD( list ) ((list)->fwd_link) // get head of list
#define ENQ_GET_TAIL( list ) ((list)->bwd_link) // get tail of list
#define ENQ_GET_NEXT( item ) ((item)->fwd_link) // get item after item
#define ENQ_GET_PREV( item ) ((item)->bwd_link) // get item before item
#define ENQ_GET_LIST_NAME( list ) ((list)->name)// get list name
#define ENQ_GET_ITEM_NAME( item ) ((item)->name)// get item name

// equivalence type struct for enqueuable item
// needs forward link to next item, backwards
// link to previous item; if forward/backward
// links point to itself, it is not enqueued
typedef struct enq_item_s
{
    struct enq_item_s *fwd_link; // forward link, points to next enq_item_s
    struct enq_item_s *bwd_link; // backwards link
    char              *name; // name of enq_item_s
} ENQ_ITEM_t, *ENQ_ITEM_p_t;


// list anchor - no application data; when instantiated, this in
// effect is the doubly-linked list
typedef ENQ_ITEM_t ENQ_ANCHOR_t, *ENQ_ANCHOR_p_t;

// methods to do stuff with the list ----------

// create a new doubly linked list
ENQ_ANCHOR_p_t ENQ_create_list(const char *name);
// create new enqueuable item
ENQ_ITEM_p_t ENQ_create_item(const char *name, size_t size);
// test whether item is enqueued
CDA_BOOL_t ENQ_is_item_enqed( ENQ_ITEM_p_t item );
// test whether the list if empty
CDA_BOOL_t ENQ_is_list_empty( ENQ_ANCHOR_p_t anchor );
// add item to head of list
ENQ_ITEM_p_t ENQ_add_head( ENQ_ANCHOR_p_t anchor, ENQ_ITEM_p_t item );
// add item to tail of list
ENQ_ITEM_p_t ENQ_add_tail( ENQ_ANCHOR_p_t anchor, ENQ_ITEM_p_t item );
// add item after previously enqueued item
ENQ_ITEM_p_t ENQ_add_after(ENQ_ITEM_p_t item, ENQ_ITEM_p_t after);
// add item before previously enqueued item
ENQ_ITEM_p_t ENQ_add_before(ENQ_ITEM_p_t item, ENQ_ITEM_p_t before);
// dequeue item from list
ENQ_ITEM_p_t ENQ_deq_item(ENQ_ITEM_p_t item);
// dequeue item from head of list
ENQ_ITEM_p_t ENQ_dequeue_head(ENQ_ANCHOR_p_t anchor);
ENQ_ITEM_p_t ENQ_dequeue_tail(ENQ_ANCHOR_p_t anchor);
ENQ_ITEM_p_t ENQ_destroy_item( ENQ_ITEM_p_t item);
ENQ_ITEM_p_t ENQ_empty_list( ENQ_ANCHOR_p_t anchor);
ENQ_ITEM_p_t ENQ_destroy_list( ENQ_ANCHOR_p_t anchor);

#endif /*ENQ_H*/
