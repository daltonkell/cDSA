#include <stdio.h>
#include "cda.h"
#include "list.h"

// let's represent an entry in this list as
// a struct
typedef struct data_struct_s {
    char *name;
    int field1;
} DATA_STRUCT_t, *DATA_STRUCT_p_t;

//void print_data_struct(DATA_STRUCT_p_t ele_ptr)
void print_data_struct(void *ele_ptr)
{
    DATA_STRUCT_p_t ele = ele_ptr;
    printf("%s\n",ele->name);
    printf("Value of field1:\t%i\n", ele->field1);
}

// LIST_TRAVERSAL_PROC_p_t pointer to function
LIST_TRAVERSAL_PROC_p_t print_list_proc = print_data_struct;

void data_struct_destroy_proc(void *ele_ptr)
{
    DATA_STRUCT_p_t ele = ele_ptr;
    printf("FREEING %p -> name\n", ele);
    CDA_free(ele->name);
}

// pointer to destroy function
LIST_DESTROY_PROC_p_t destroy_ele_proc = data_struct_destroy_proc;

int main()
{

    // trivial example - create 3 elements;
    // our destroy_proc must free the mem for ele->name
    void *e1_p = CDA_malloc(sizeof(DATA_STRUCT_t));
    DATA_STRUCT_p_t ele1 = e1_p;
    // allocate mem for name as struct expects ptr to char
    ele1->name   = CDA_NEW_STR_IF("elem1");
    ele1->field1 = 5; // compiler expects an int, not ptr to int

    //DATA_STRUCT_t ele2 = {
    //    "this_element_2",
    //    44
    //};
    //DATA_STRUCT_t ele3 = {
    //    "elem_3",
    //    7
    //};

    // create a list
    LIST_ID_t list = LIST_NULL_ID;
    list = LIST_create_list(
        3,
        sizeof(DATA_STRUCT_t),
        "myList"
    );

    // add a new element
    LIST_add_entry(
        list,
        //&ele1
        ele1
    );
    //LIST_add_entry(
    //    list,
    //    &ele2
    //);
    //LIST_add_entry(
    //    list,
    //    &ele3
    //);

    printf("Is the list empty?\t%i\n", LIST_is_list_empty(list));
    printf("Is the list full?\t%i\n", LIST_is_list_full(list));
    printf("Number of elements in list:\t%lu\n", LIST_get_list_size(list));

    // travserse the list
    LIST_traverse_list(
        list,
        print_list_proc
    );

    // clear the list
    LIST_clear_list(list, data_struct_destroy_proc);

    // destroy the list
    LIST_destroy_list(list, NULL);

    return 0;
}
