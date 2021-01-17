#include "quep.h" /* QUE__CONTROL_t, QUE__CONTROL_p_t */

QUE_ID_t QUE_create_queue(const char *name)
{
    /* allocate new pointer */
    QUE__CONTROL_p_t qid = CDA_NEW(QUE__CONTROL_t);

    /* create enqueable item as anchor */
    qid->anchor = ENQ_create_list(name);

    return qid;
}

QUE_ITEM_p_t QUE_create_item(const char *name, void *data)
{
    /* create pointer and cast as item type */
    QUE_ITEM_p_t item = (QUE_ITEM_p_t)ENQ_create_item(name, sizeof(QUE_ITEM_t));

    /* assign data */
    item->data = data;
    return item;
}

CDA_BOOL_t QUE_is_queue_full(QUE_ID_t qid)
{
    /* queue is never full, return false */
    return CDA_FALSE;
}

CDA_BOOL_t QUE_is_queue_empty(QUE_ID_t qid)
{
    /* Get anchor and test if the anchor's item points to itself */
    return ENQ_is_list_empty(qid->anchor);
}

int QUE_get_queue_size(QUE_ID_t qid)
{
    int size = 0;
    while (qid->anchor->fwd_link != qid->anchor)
    {
        ++size;
    }
    return size;
}

QUE_ITEM_p_t QUE_append_item(QUE_ID_t qid, QUE_ITEM_p_t item)
{
    /* cast and add the item to the linked list, as
     * each item in the linked list must be ENQ_ITEM_t
     */
    return (QUE_ITEM_p_t)ENQ_add_tail(qid->anchor, (ENQ_ITEM_p_t)item);
}

QUE_ITEM_p_t QUE_get_item_no_remove(QUE_ID_t qid)
{
    /* if queue is empty, return QUE_NULL_ID */
    if (QUE_is_queue_empty(qid))
    {
        return QUE_NULL_ID;
    }

    /* access first item, cast back to QUE_ITEM_p_t and return it */
    return (QUE_ITEM_p_t)qid->anchor->fwd_link;
}

QUE_ITEM_p_t QUE_get_item(QUE_ID_t qid)
{
    /* if queue is empty, return QUE_NULL_ID */
    if (QUE_is_queue_empty(qid))
    {
        return QUE_NULL_ID;
    }

    /* get the first item, cast back as QUE_ITEM_p_t
     * and return it. Take care of queue ordering by
     * using ENQ_dequeue_head()
     */

    return (QUE_ITEM_p_t)ENQ_dequeue_head(qid->anchor);
}

QUE_ITEM_p_t QUE_destroy_item(QUE_ITEM_p_t item)
{
    /* Use ENQ_destroy_item to destroy the item */
    ENQ_destroy_item((ENQ_ITEM_p_t)item);

    return QUE_NULL_ID;
}

QUE_ID_t QUE_clear_queue(QUE_ID_t qid, QUE_DESTROY_PROC_p_t destroyProc)
{
    QUE_ITEM_p_t item = QUE_NULL_ID;
    while (!ENQ_is_list_empty(qid->anchor))
    {
        /* get items from the list, cast as QUE_ITEM_p_t
         * and (optionally) perform the destroy proc on them
         */
        item = (QUE_ITEM_p_t)ENQ_GET_HEAD(qid->anchor);
        //item = (QUE_ITEM_p_t)(qid->anchor->fwd_link);
        if (destroyProc != NULL)
        {
            destroyProc(item->data);
        }

        /* finish by destroying the item */
        QUE_destroy_item(item);
    }

    return qid;
}

QUE_ID_t QUE_traverse_queue(QUE_ID_t qid, QUE_TRAVERSE_PROC_p_t traverseProc)
{
    /* retrieve the first item and cast as QUE_ITEM_p_t */
    //QUE_ITEM_p_t item = (QUE_ITEM_p_t)ENQ_GET_NEXT(qid->anchor);
    /* get head of list */
    ENQ_ITEM_p_t head = ENQ_GET_HEAD(qid->anchor);
    QUE_ITEM_p_t item = NULL;
    while (head != qid->anchor)
    {
        /* get next item in the list */
        item = (QUE_ITEM_p_t)head;
         
        if (traverseProc != NULL)
        {
            /* call on the data */
            traverseProc(item->data);
        }
        /* get the next item */
        head = ENQ_GET_NEXT(head);
    }

    return qid;
}

QUE_ID_t QUE_destroy_queue(QUE_ID_t qid, QUE_DESTROY_PROC_p_t destroyProc)
{
    /* clear the queue */
    QUE_clear_queue(qid, destroyProc);

    /* destroy the linked list */
    ENQ_destroy_list(qid->anchor);

    /* free qid */
    CDA_free(qid);

    return QUE_NULL_ID;
}
