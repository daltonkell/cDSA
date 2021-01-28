#ifndef BTREE_H
#define BTREE_H

#include <cda.h>

/* macros */
#define BTREE_NULL_ID      (NULL)
#define BTREE_NULL_NODE_ID (NULL)

/* type aliases */

/* tree ID and node ID structures */
typedef struct btree__control_s *BTREE_ID_t;
typedef struct btree__node_s    *BTREE_NODE_ID_t;

/* callback functions */
typedef void BTREE_VISIT_PROC_t(void *data);
typedef BTREE_VISIT_PROC_t *BTREE_VISIT_PROC_p_t;
typedef void BTREE_DESTROY_PROC_t(void *data);
typedef BTREE_DESTROY_PROC_t *BTREE_DESTROY_PROC_p_t;

/* traversal order
 * TODO: level traversal
 */
typedef enum btree_traverse_order_e
{
    BTREE_PREORDER,
    BTREE_INORDER,
    BTREE_POSTORDER
} BTREE_TRAVERSE_ORDER_e_t;

/* Methods associated with the binary tree

  - Create a tree
  - add root node to the tree
  - add left child to node
  - add right child to node
  - get a tree's root node
  - get the data associated with a node
  - get a node's left child
  - get a node's right child
  - check if tree is empty
  - check if node is a leaf
  - traverse a binary tree
  - destroy subtree
  - destroy a binary tree
*/

/* Create a tree

Parameters
  None

Returns
  tree id

Notes
  Throws SIGABRT if tree cannot be created
*/
BTREE_ID_t BTREE_create_tree(void);

/* Add root node to tree
Parameters
  tree id ptr
  data ptr
Returns
  node ptr
*/
BTREE_NODE_ID_t BTREE_add_root(BTREE_ID_t tree, void *data);

/* Add left child
Parameters
  node ID ptr
  data ptr
Returns
  node ID of left child
*/
BTREE_NODE_ID_t BTREE_add_left(BTREE_NODE_ID_t node, void *data);

/* Add right child
Parameters
  node ID ptr
  data ptr
Returns
  node ID of right child
*/
BTREE_NODE_ID_t BTREE_add_right(BTREE_NODE_ID_t node, void *data);

/* Get a tree's root node
Parameters
  tree ID
Returns
  root node ID
 */
BTREE_NODE_ID_t BTREE_get_root(BTREE_ID_t tree);

/* Get data from a node
Parameters
  node ID
Returns
  void ptr
*/
void *BTREE_get_data(BTREE_NODE_ID_t node);

/* Get left child of node
Parameters
  node ID
Returns
  node ID of node's left child or NODE_NULL_ID
*/
BTREE_NODE_ID_t BTREE_get_left(BTREE_NODE_ID_t node);

/* Get right child of node
Parameters
  node ID
Returns
  node ID of node's left child or NODE_NULL_ID
*/
BTREE_NODE_ID_t BTREE_get_right(BTREE_NODE_ID_t node);

/* Check if tree is empty
Parameters
  tree ID
Returns
  bool
*/
CDA_BOOL_t BTREE_is_tree_empty(BTREE_ID_t tree);

/* Check if a node is a leaf
Parameters
  node ID
Returns
  bool
*/
CDA_BOOL_t BTREE_is_node_leaf(BTREE_NODE_ID_t node);

/* Traverse a tree
Parameters
  tree ID
  travseral order
  traversal proc
Returns
  void
*/
void BTREE_traverse_tree(
    BTREE_ID_t tree,
    BTREE_TRAVERSE_ORDER_e_t order,
    BTREE_VISIT_PROC_p_t traverse_proc
);

/* Destroy a subtree
User is given opportunity to destroy data prior to freeing
the subtree with BTREE_DESTROY_PROC_p_t.

Parameters
  node ID
  data destroy proc
Returns
  null node ID
*/
BTREE_NODE_ID_t BTREE_destroy_subtree(
    BTREE_NODE_ID_t node,
    BTREE_DESTROY_PROC_p_t destroy_proc
);

/* Destroy a tree
Parameters
  tree ID ptr
  destroy proc ptr
Returns
  null tree ID
*/
BTREE_ID_t BTREE_destroy_tree(
    BTREE_ID_t tree,
    BTREE_DESTROY_PROC_p_t destroy_proc
);
#endif /* BTREE_H */
