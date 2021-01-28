#ifndef BTREEP_H
#define BTREEP_H

#include "btree.h"

/* full definitions of control structure and node structure */
typedef struct btree__control_s *BTREE__CONTROL_p_t;
typedef struct btree__node_s    *BTREE__NODE_p_t;

/* Each node to contain
- ptr to tree
- ptr to parent node
- ptr to left child, right child
- ptr to void data
*/
typedef struct btree__node_s
{
    BTREE__CONTROL_p_t tree;
    BTREE__NODE_p_t    parent;
    BTREE__NODE_p_t    left;
    BTREE__NODE_p_t    right;
    void               *data;
} BTREE__NODE_t;

/* Tree control structure to point at root node */
typedef struct btree__control_s
{
    BTREE__NODE_p_t root;
} BTREE__CONTROL_t, *BTREE_ID_t;

/* Traversal functions */
void BTREE__traverse_inorder(
    BTREE_NODE_ID_t node,
    BTREE_VISIT_PROC_p_t visit_proc);

void BTREE__traverse_preorder(
    BTREE_NODE_ID_t node,
    BTREE_VISIT_PROC_p_t visit_proc);

void BTREE__traverse_postorder(
    BTREE_NODE_ID_t node,
    BTREE_VISIT_PROC_p_t visit_proc);

#endif /* BTREEP_H */
