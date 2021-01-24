#include "btreep.h" /* BTREE__CONTROL_p_t, BTREE__NODE_p_t */
#include <cda.h>

/* Create tree */
BTREE_ID_t BTREE_create_tree(void)
{
    /* allocate memory for new tree control */
    BTREE__CONTROL_p_t tree = CDA_NEW(BTREE__CONTROL_t);
    tree->root = BTREE_NULL_ID;
    return tree;
}

/* Add root node */
BTREE_NODE_ID_t BTREE_add_root(BTREE_ID_t tree, void *data)
{
    CDA_ASSERT(tree->root==NULL);

    /* Create root node */
    BTREE__NODE_p_t node = CDA_NEW(BTREE__NODE_t);

    /* Assign root node to tree; ensure root's children are null,
       other pointers accordingly */
    tree->root = node;
    node->tree = tree;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data = data;

    return node;
}

/* Add left child to node */
BTREE_NODE_ID_t BTREE_add_left(BTREE_NODE_ID_t node, void *data)
{
    /* Assert node does not already have a left child */
    CDA_ASSERT(node->left == NULL);

    /* Create child node */
    BTREE__NODE_p_t left_child = CDA_NEW(BTREE__NODE_t);

    /* Assign ptrs appopriately */
    left_child->data = data;
    left_child->parent = node;
    left_child->left = NULL;
    left_child->right = NULL;
    left_child->tree = node->tree;
    node->left = left_child;

    return left_child;
}

/* Add right child */
BTREE_NODE_ID_t BTREE_add_right(BTREE_NODE_ID_t node, void *data)
{
    /* Assert node does not already have a right child */
    CDA_ASSERT(node->right == NULL);

    /* Create child node */
    BTREE__NODE_p_t right_child = CDA_NEW(BTREE__NODE_t);

    /* Assign ptrs appopriately */
    right_child->data = data;
    right_child->parent = node;
    right_child->right = NULL;
    right_child->right = NULL;
    right_child->tree = node->tree;
    node->right = right_child;

    return right_child;
}

/* Get root node of tree */
BTREE_NODE_ID_t BTREE_get_root(BTREE_ID_t tree)
{
    return tree->root;
}

/* Get data from a node */
void *BTREE_get_data(BTREE_NODE_ID_t node)
{
    return node->data;
}

/* Get left child of node */
BTREE_NODE_ID_t BTREE_get_left(BTREE_NODE_ID_t node)
{
    return node->left;
}

/* Get right child of node */
BTREE_NODE_ID_t BTREE_get_right(BTREE_NODE_ID_t node)
{
    return node->right;
}

/* Check if tree is empty */
CDA_BOOL_t BTREE_is_tree_empty(BTREE_ID_t tree)
{
    return tree->root != NULL ? CDA_TRUE : CDA_FALSE;
}

/* Check if node is leaf */
CDA_BOOL_t BTREE_is_node_leaf(BTREE_NODE_ID_t node)
{
    return (node->left != NULL || node->right != NULL) ? CDA_FALSE : CDA_TRUE;
}

/* TODO *********************************
 * Traverse a tree
void BTREE_traverse_tree(
    BTREE_ID_t tree,
    BTREE_TRAVERSE_ORDER_e_t order,
    BTREE_TRAVERSE_PROC_p_t traverse_proc
);
 */

/* Destroy a subtree
 * Recursive procedure, destroying all left children,
 * then right children, then the node itself. Users are
 * given opportunity to destroy node data prior to freeing
 * the child.
 *
 * TODO Implement in non-recursive nature
*/
BTREE_NODE_ID_t BTREE_destroy_subtree(
    BTREE_NODE_ID_t node,
    BTREE_DESTROY_PROC_p_t destroy_proc
)
{
    CDA_ASSERT(node != NULL);

    /* set up recursive calls for children */
    if (node->left != NULL)
    {
        BTREE_destroy_subtree(node->left, destroy_proc);
    }
    if (node->right != NULL)
    {
        BTREE_destroy_subtree(node->right, destroy_proc);
    }

    /* call the user function on data */
    if (destroy_proc != NULL)
    {
        destroy_proc(node->data);
    }

    /* TODO */
}

/* Destroy tree */
BTREE_ID_t BTREE_destroy_tree(
    BTREE_ID_t tree,
    BTREE_DESTROY_PROC_p_t destroy_proc
)
{
    /* leverage BTREE_destroy_subtree, call it at the root */
    BTREE_destroy_subtree(tree->root, destroy_proc);

    /* free the mem associated w/ tree */
    CDA_free(tree);

    return BTREE_NULL_ID;
}
