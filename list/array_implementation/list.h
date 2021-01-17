/* LIST public header file */
#ifndef CDA_H
#include "cda.h"
#endif

// alias for LIST_ID_t
typedef struct list__control_s *LIST_ID_t;

// NULL value for list identifier;
// for example, lists can be declared/initialized like
//     LIST_ID_t list = LIST_NULL_ID;
#define LIST_NULL_ID    (NULL)

// ** defining the travsersal proc functions **
// the function to be optionally passed when destroying a list is to
// be a function returning void which takes a parameter of pointer to void
typedef void LIST_DESTROY_PROC_t(void *);
typedef LIST_DESTROY_PROC_t *LIST_DESTROY_PROC_p_t;

// the function to be optionally passed when traversing a list is
// to be a func returning void taking parameter pointer to void
typedef void LIST_TRAVERSAL_PROC_t(void *);
typedef LIST_TRAVERSAL_PROC_t *LIST_TRAVERSAL_PROC_p_t;

// function declarations

/* Create an empty list and return a value which identifies the list
 *  - max_list_size: hint of list's maximum size
 *  - entry_size   : size of an entry in the list
 *  - name         : name of the list
 *
 * Returns:
 *  - list ID
 * Exceptions:
 *  - throws SIGABRT is list can't be created
 * Notes:
 *  - user responsible for freeing memory occupied with LIST_destroy_list
 *  - after creation, list guaranteed to hold max_list_size entries but
 *    may hold more
 */
LIST_ID_t LIST_create_list(
                           size_t max_list_size,
                           size_t entry_size,
                           const char *name
                          );

/* Add an entry to the list/
 *  - list: ID of previously created list
 *  - data: data to be appended to list tail
 *
 * Returns:
 *  - list ID
 * Exceptions:
 *  - throws SIGABRT if new entry cannot be created
 * Notes:
 *  - data arg must piont to a block of memory equal in size to the entry size
 *    specified in LIST_create_list. A new entry is created for the list and the
 *    data is copied into it
 */
const void *LIST_add_entry(LIST_ID_t list, const void *data);

/* Traverse list in order, calling the user's travseral
 * process at each node.
 *
 * 
 * Where:
 *   list: ID of previously created list
 *   traversal_proc: function to call for each node
 * Returns:
 *   list
 * Notes:
 *   - travseral proc may be NULL
 */
LIST_ID_t LIST_traverse_list(
    LIST_ID_t               list,
    LIST_TRAVERSAL_PROC_p_t travsersal_proc
    );

/* Check if list is empty
 * Where:
 *   list: ID of created list
 * Returns:
 *   CDA_TRUE if list is empty, CDA_FALSE otherwise
 */
CDA_BOOL_t LIST_is_list_empty(LIST_ID_t list);

/* Check if list is full
 * Where:
 *   list: ID of list
 * Returns:
 *   CDA_BOOL_t (True if full, False if not)
 */
CDA_BOOL_t LIST_is_list_full(LIST_ID_t list);

/* Get size of list (number elements in list)
 * Where:
 *   list: ID of list
 * Returns:
 *   size_t
 */
size_t LIST_get_list_size(LIST_ID_t list);

/* Clear list (remove all elements). If caller specifies a
 * destroy process, the process will be called on each node before
 * destruction. Returns list to empty, initial state.
 * Where:
 *   list: ID of list
     destroy_proc: function to call on each node
 * Returns:
 *   list
 * Notes:
 *   - if not needed, the destroy proc can be NULL
 */
LIST_ID_t LIST_clear_list(
    LIST_ID_t             list,
    LIST_DESTROY_PROC_p_t destroy_proc
    );

/* Destroy the list by first clearing the list (via LIST_clear_list)
 * then destroying the list itself. If a destroy process is specified,
 * the process will be called on each node.
 * Where:
 *   list: list ID
 *   destroy_proc: function to call on each node
 * Returns:
 *   list
 * Notes:
 *   - destroy proc may be NULL if not needed
 */
LIST_ID_t LIST_destroy_list(
    LIST_ID_t list,
    LIST_DESTROY_PROC_p_t destroy_proc
    ); 
