#ifndef QUEP_H
#define QUEP_H

#include "que.h"
#include <enq.h>

/* Because we have chosen an enqeuable item as our
 * queue item type, the implementation will actually be very close
 * to that of a linked list. Our control structure will contain
 * a pointer to an anchor.
 */

typedef struct que__control_s
{
    ENQ_ANCHOR_p_t anchor;
} QUE__CONTROL_t, *QUE__CONTROL_p_t;

#endif
