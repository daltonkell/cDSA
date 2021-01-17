#include <stdbool.h>
#include <stdio.h>

#include "cda.h"
#include "enq.h"

// basic implementation of doubly linked list

// create a new doubly linked list
ENQ_ANCHOR_p_t ENQ_create_list(const char *name)
{
    /* create a new list; caller is responsible for freeing mem */

    // allocate space for anchor
    ENQ_ANCHOR_p_t list = CDA_NEW( ENQ_ANCHOR_t );

    // assign self-referring links
    list->fwd_link = list;
    list->bwd_link = list;
    list->name     = CDA_NEW_STR_IF( name );
    return list; // return the pointer
}

// create new enqueuable item
ENQ_ITEM_p_t ENQ_create_item(const char *name, size_t size)
{
    /* Create a new item to be enqueued. This item can be of
     * any size, which should include the static size portion.
     */

    // allocate space for another item and cast it to be ENQ_ITEM_p_t
    ENQ_ITEM_p_t item = (ENQ_ITEM_p_t)CDA_malloc( size );

    // set the fwd/bwd links to itself (not yet enqueued)
    item->fwd_link = item;
    item->bwd_link = item;

    // set the name; remember, we need to first make sure we have the
    // ability to set the name by checking if the memory we are
    // about to use belongs to us
    item->name = CDA_NEW_STR_IF( name );

    // return the pointer to the item
    return item;
}

// test whether item is enqueued
CDA_BOOL_t ENQ_is_item_enqed( ENQ_ITEM_p_t item )
{
    /* The logic of this method relies entirely on being able
     * to correctly identify the state of the item. An item is
     * enqueued if its forward/backward link points to something
     * other than itself, or they point to the anchor.
     */

    // awesome use case for ternary operator
    //return ( (item->fwd_link == item) && (item->bwd_link == item) ? CDA_FALSE : CDA_TRUE );
    return ( (item->fwd_link == item) ? CDA_FALSE : CDA_TRUE );
}

// test whether the list if empty
CDA_BOOL_t ENQ_is_list_empty( ENQ_ANCHOR_p_t anchor )
{
    /* The list is empty if the fwd/bwd link of the anchor
     * point to itself.
     */

    return (
        anchor->fwd_link == anchor && anchor->bwd_link == anchor
        ? CDA_TRUE : CDA_FALSE
    );

}

// add item to head of list
ENQ_ITEM_p_t ENQ_add_head( ENQ_ANCHOR_p_t anchor, ENQ_ITEM_p_t item )
{
    /* Similar to ENQ_add_tail, add the item to the head of the list.
     * Now:
     * anchor              item_new             item_prev
     *   fwd -> item_new     fwd -> item_prev     fwd -> unchanged
     *   bwd -> unchanged    bwd -> anchor        bwd -> item_new
     */

    // assert the item is not already enqueued
    CDA_ASSERT( !ENQ_is_item_enqed( item ) );

    // local copy of the previous item at the head (pointed to by the fwd_link of the anchor)
    ENQ_ITEM_p_t current_head = anchor->fwd_link;

    // set the anchor's fwd_link -- NOTE that bwd_link stays the same
    anchor->fwd_link = item;

    // set new item's links
    item->fwd_link = current_head;
    item->bwd_link = anchor;

    // set the now-previous item's bwd link; fwd_link doesn't change
    current_head->bwd_link = item;

    return item;

}


// add item to tail of list
ENQ_ITEM_p_t ENQ_add_tail( ENQ_ANCHOR_p_t anchor, ENQ_ITEM_p_t item )
{
    /* Add item to the tail of the list. Ensure that the
     * item is not already enqueued first (that'll create
     * some nightmares).
     */

    // assert the item is not already enqueued
    CDA_ASSERT( !ENQ_is_item_enqed( item ) );

    // current tail (pointed at by bwd_link of anchor)
    ENQ_ITEM_p_t current_tail = anchor->bwd_link;

    // the anchor's backward link now should point to new item;
    // anchor's fwd_link does not change
    anchor->bwd_link = item;

    // should now have a forward link pointing to the new item;
    // it previously pointed at some other item
    current_tail->fwd_link = item;

    // the item's backward link should point at the item
    // the item's forward link should point at the anchor
    item->bwd_link = current_tail;
    item->fwd_link = anchor;

    // assert that we've done this correctly
    CDA_ASSERT( item->fwd_link == anchor );

    return item;

}

// add item after previously enqueued item
ENQ_ITEM_p_t ENQ_add_after(ENQ_ITEM_p_t item, ENQ_ITEM_p_t after)
{
    /* Add item to the list after `after` */

    // first, check that the item is not enqueued
    CDA_ASSERT( !ENQ_is_item_enqed(item) );

    // grab the item after `after` - need to assign its pointers, too
    ENQ_ITEM_p_t after2 = after->fwd_link;

    // reassign fwd_link pointer to `after`; bwd unchanged
    after->fwd_link = item;

    // assign links to item
    item->bwd_link = after;
    item->fwd_link = after2;

    // reassign bwd_link of after2
    after2->bwd_link = item;

    return item;
}

// add item before previously enqueued item
ENQ_ITEM_p_t ENQ_add_before(ENQ_ITEM_p_t item, ENQ_ITEM_p_t before)
{
    /* Add `item` before `before` */

    // assert that item is not already enqueued
    CDA_ASSERT ( !ENQ_is_item_enqed( item ) );

    // get item that's before `before`, need to change its fwd_link
    ENQ_ITEM_p_t before2 = before->bwd_link;

    // reassign the fwd_link; bwd is unchanged
    before2->fwd_link = item;

    // assign `item` links
    item->bwd_link = before2;
    item->fwd_link = before;

    // reassign `before` bwd_link to item
    before->bwd_link = item;

    return item;
}

// dequeue item from list
ENQ_ITEM_p_t ENQ_deq_item(ENQ_ITEM_p_t item)
{
    /* Dequeue *any* item from the list. NOTE that
     * because of our careful definition of the unenqueued
     * state, we don't need to check if the item is enqueued
     * or not; the algorithm works just as well on unenqueued
     * items.
     */

    // the item that is pointed to by bwd_link should point
    // to the item ahead of item with its fwd_link
    item->bwd_link->fwd_link = item->fwd_link;

    // the item pointed to by fwd_link should point to
    // the item behind item with its bwd_link
    item->fwd_link->bwd_link = item->bwd_link;

    // now, 'reset' the state of the item
    item->bwd_link = item;
    item->fwd_link = item;

    return item;
}

// dequeue item from head of list
ENQ_ITEM_p_t ENQ_dequeue_head(ENQ_ANCHOR_p_t anchor)
{
    /* If the list is non-empty, return the pointer to the dequeued
     * item; otherwise, return the pointer to the anchor.
     */

    if ( ENQ_is_list_empty( anchor ) ){ return anchor; }

    // item to be dequeued
    ENQ_ITEM_p_t item = anchor->fwd_link;

    // anchor should fwd_link to item->fwd_link
    anchor->fwd_link = item->fwd_link;

    // item's fwd_link item should point bwd to anchor
    item->fwd_link->bwd_link = anchor;

    // item should point to itself
    item->fwd_link = item;
    item->bwd_link = item;

    return item;

}

ENQ_ITEM_p_t ENQ_dequeue_tail(ENQ_ANCHOR_p_t anchor)
{
    /* Dequeue the item at the tail of the list. If the list
     * is empty, return the pointer to the anchor. Otherwise,
     * return the pointer to the dequeued item.
     */

    // check if empty
    if (ENQ_is_list_empty( anchor ) ){ return anchor;}

    // item to be dequeued
    ENQ_ITEM_p_t item = anchor->bwd_link;

    // the anchor's bwd_link should point to the item's bwd_link;
    // fwd link remains unchanged
    anchor->bwd_link = item->bwd_link;

    // item pointed to by item's bwd_link should fwd_link to anchor
    item->bwd_link->fwd_link = anchor;

    // item should point to itself
    item->bwd_link = item;
    item->fwd_link = item;

    return item;

}

ENQ_ITEM_p_t ENQ_destroy_item( ENQ_ITEM_p_t item )
{
    /* Destroy an item, thereby freeing the memory. If the item
     * is enqueued, it will be dequeued before destruction.
     */

    ENQ_deq_item( item );
    CDA_free( item-> name); // always free the name too!
    CDA_free( item );

    return NULL; // NOTE not really sure why returning NULL when the return type is ENQ_ITEM_p_t?
}

ENQ_ITEM_p_t ENQ_empty_list( ENQ_ANCHOR_p_t anchor )
{
    /* Empty a list pointed at by anchor. This will remove all
     * items from the list and free the memory. The pointer to the
     * anchor is then returned.
     */

    while ( !ENQ_is_list_empty( anchor ))
    {
        ENQ_destroy_item( anchor->fwd_link );
    }

    return anchor;
}

ENQ_ITEM_p_t ENQ_destroy_list( ENQ_ANCHOR_p_t anchor )
{
    /* Empty the list, then free the memory occupied by
     * the anchor. Returns NULL explicitly (why?).
     */

    ENQ_empty_list( anchor );
    CDA_free( anchor->name ); // always free name
    CDA_free( anchor );
    return NULL;
}

void print_doubly_linked_list(ENQ_ANCHOR_p_t anchor)
{
    /* Print the contents and links of a doubly-linked list */

    // print anchor
    printf("Anchor: %p\n  name: %s\n", anchor, anchor->name);

    if ( ENQ_is_list_empty( anchor )) // no items
    {
        // stop
        return;
    }


    // grab the forward link; will be reassigned as loop continues
    ENQ_ITEM_p_t tmp = anchor->fwd_link;
    bool go = true;
    while (go)
    {

        // assert if fwd_link is ENQ_ITEM_p_t?
        //CDA_ASSERT(

        // print the name, links of next pointer
        printf("Item: %p\n  name: %s\n  fwd_link: %p\n  bwd_link: %p\n", tmp, tmp->name, tmp->fwd_link, tmp->bwd_link);
        
        if ( tmp->fwd_link == anchor ) go = false; // no more items left

        // reassign tmp to move onto next item
        tmp = tmp->fwd_link;

    }

}
// ---------- end methods
