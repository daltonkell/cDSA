------
Queues
------

A queue is a very simple and ubiquitous data structure and organizes data on
a first-come, first-serve basis. A priority queue is a sub-type of a queue
which organizes data according to some arbitrary level of importance.

This module will look at both a simple implementation of a priority queue
and a second, more complex implementation which offers increased performance
(in terms of execution) at the cost of added complexity.

Overview
--------

Queues can be simply visualized as an array.
  - new items added to end
  - items are removed from only the front
  - often referred to as first-in first out, or FIFO,
    but this is not the only type of queue, e.g. last-
    in first out (LIFO)

Priority queues
  - each element is assigned some priority corresponding
    to some scheme defined
  - e.g. priority represented by int, higher int == higher priority
  - may be visualized as an array where all elements of the same
    priority class are grouped together
  - still, elements are added to the back of the queue and are removed
    via the front
    - removal operations now address the element of the highest priority
      that has been enqueued the longest

----- Queues in More Detail -----

10 basic operations:
  1. Create a queue
  2. Detemine if queue is empty
  3. Determine if queue is full
  4. Determine size of queue
  5. Append new entry
  6. Retrieve (without removing) entry at front
  7. Remove entry at front
  8. Clear the queue
  9. Traverse queue
  10. Destroy the queue

  See que.h, quep.h and que.c for implementation of this simple queue.
