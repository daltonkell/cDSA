/* QUE public header
 *
 * This module defines data types for
 *  - queue ID (control structure)
 *  - callback functions associated with queue operations
 *  - data used as input/output ops like append/remove
 *
 * For input/output operations, we COULD use a void pointer to
 * represent the user's data. However, applications often mix
 * the use of queues and other list types, so using a standard
 * data type which is strongly defined is a good idea. For this
 * reason, this module will define an item in the queue as an
 * enqueuable item from our ENQ module.
 *
 * Basic operations:
 *   1. Create a queue
 *   2. Detemine if queue is empty
 *   3. Determine if queue is full
 *   4. Determine size of queue
 *   5. Append new entry
 *   6. Retrieve (without removing) entry at front
 *   7. Remove entry at front
     8. Destroy item
 *   9. Clear the queue
 *   10. Traverse queue
 *   11. Destroy the queue                         TODO
 *
 */

/* NOTE:
 * This include guard is included because of the que_item_s typedef.
 * Can't we make this typedef private and only use
 * 
 * typedef struct que_item_s;
 * 
 * as an incomplete decl, and then define in quep.h?
 * 
 */

#ifndef ENQ_H
#include <enq.h>
#endif

#ifndef CDA_H
#include <cda.h>
#endif

/* macro for NULL id */
#define QUE_NULL_ID (NULL)

/* control structure */
typedef struct que__control_s *QUE_ID_t;

/* queue item */
typedef struct que_item_s
{
    ENQ_ITEM_t item;
    void       *data;
} QUE_ITEM_t, *QUE_ITEM_p_t;

/* callback function typedefs */
typedef void QUE_DESTROY_PROC_t(void *data);
typedef QUE_DESTROY_PROC_t *QUE_DESTROY_PROC_p_t;
typedef void QUE_TRAVERSE_PROC_t(void *data);
typedef QUE_TRAVERSE_PROC_t *QUE_TRAVERSE_PROC_p_t;

/* CREATE A QUEUE
Create a new queue and return the ID.

Parameters
  name: ptr to char

Returns
  queue ID
*/
QUE_ID_t QUE_create_queue(const char *name);

/* CREATE A QUEUE ITEM
Create a new item to contain user data.

Parameters
  const char *name: item name
  void * dataL user data

Returns
  QUE_ITEM_p_t
*/
QUE_ITEM_p_t QUE_create_item(const char *name, void *data);

/* TEST IF QUEUE IS FULL
Check if the queue is full and return boolean.

Parameters
  qid: id of queue

Returns
  CDA_BOOL_t
*/
CDA_BOOL_t QUE_is_queue_full(QUE_ID_t qid);

/* TEST IF QUEUE IS EMPTY
Check if the queue is empty and return boolean.

Parameters
  qid: id of queue

Returns
  CDA_BOOL_t
*/
CDA_BOOL_t QUE_is_queue_empty(QUE_ID_t qid);

/* GET SIZE
Get the size of the queue in number of elements.

Parameters
  qid: queue id

Returns
  int
*/
int QUE_get_queue_size(QUE_ID_t qid);

/* APPEND
Add an item to the queue. To the back of the line!

Parameters
  qid
  QUE_ITEM_p_t item: ptr to item

Returns
  QUE_ITEM_p_t
*/
QUE_ITEM_p_t QUE_append_item(QUE_ID_t qid, QUE_ITEM_p_t item);

/* GET FRONT ENTRY, DON'T REMOVE
Get the first entry in the queue w/o removing it.
If queue is empty, returns QUE_NULL_ID.

Parameters
  qid: queue ID

Returns
  QUE_ITEM_p_t
*/
QUE_ITEM_p_t QUE_get_item_no_remove(QUE_ID_t qid);

/* GET FRONT ENTRY
Remove and return the first entry in the queue.
If queue is empty, returns QUE_NULL_ID.

Parameters
  qid: queue ID

Returns
  QUE_ITEM_p_t
*/
QUE_ITEM_p_t QUE_get_item(QUE_ID_t qid);

/* DESTROY AN ITEM
Parameters
  QUE_ID_t

Returns
  QUE_ITEM_p_t
*/
QUE_ITEM_p_t QUE_destroy_item(QUE_ITEM_p_t item);

/* CLEAR THE QUEUE
If a destroy proc is given, use that before removing each
item. destroyProc can be NULL.

Parameters
  QUE_ID_t qid
  QUE_DESTROY_PROC_p_t destroyProc

Returns
  qid
*/
QUE_ID_t QUE_clear_queue(QUE_ID_t qid, QUE_DESTROY_PROC_p_t destroyProc);

/* TRAVERSE THE QUE
Apply traverseProc on each item. The traverseProc can be NULL.

Parameters
  qid
  traverseProc

Returns
  qid
*/
QUE_ID_t QUE_traverse_queue(QUE_ID_t qid, QUE_TRAVERSE_PROC_p_t traverseProc);

/* DESTROY A QUEUE
Uses QUE_clear_queue to clear the items, then destroys the queue.

Parameters
  qid
  traverseProc

Returns
  QUE_NULL_ID

Notes
  Will throw SIGABRT if qid cannot be freed.
*/
QUE_ID_t QUE_destroy_queue(QUE_ID_t qid, QUE_DESTROY_PROC_p_t destroyProc);
