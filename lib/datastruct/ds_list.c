/*!
 * \file            ds_list.c
 * \brief           Implementation of generic doubly-linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data_structures.h"

/*!  List element data structure  */
struct ds_list_element {
    void * data;                        /*!<  Pointer to data               */
    struct ds_list_element * previous;  /*!<  Pointer to previous element   */
    struct ds_list_element * next;      /*!<  Pointer to next element       */
};

/*!  List data structure  */
struct ds_list {
    size_t length;                      /*!<  Length of list                */
    bool free_on_delete;                /*!<  'Free on delete' flag         */
    struct ds_list_element * head;      /*!<  Pointer to head element       */
    struct ds_list_element * tail;      /*!<  Pointer to tail element       */
    struct ds_list_element * current;   /*!<  Pointer to current element    */
    void (*data_destructor)(void *);    /*!<  Data destructor function      */
};

/*!
 * \brief           Creates a list element from provided data.
 * \details         The element pointers are set to `NULL`, and the caller
 * should modify them when inserting the element into a list.
 * \param data      A pointer to the element data.
 * \returns         A pointer to the new element, or `NULL` on failure.
 */
static struct ds_list_element * list_element_create(void * data);

/*!
 * \brief           Frees resources associated with a list element.
 * \param element   A pointer to the element to free.
 * \param data_free `true` if the data element should itself be freed,
 * `false` otherwise.
 * \param destructor    A pointer to the destructor function, to be used if
 * `data_free` is `true`. If this is `NULL`, `free()` from the standard C
 * library is used.
 */
static void list_element_destroy(struct ds_list_element * element,
                                 const bool data_free,
                                 void (*destructor)(void *));

ds_list ds_list_create(const bool free_on_delete,
                                void (*destructor)(void *)) {
    ds_list new_list = malloc(sizeof *new_list);
    if ( !new_list ) {
        return NULL;
    }

    new_list->length = 0;
    new_list->free_on_delete = free_on_delete;
    new_list->current = NULL;
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->data_destructor = destructor;

    return new_list;
}

void ds_list_destroy(ds_list list) {
    assert(list);

    ds_list_remove_all(list);
    free(list);
}

void ds_list_destructor(void * list) {
    ds_list_destroy(list);
}

ds_list ds_list_append(ds_list list, void * data) {
    assert(list);

    struct ds_list_element * new_tail = list_element_create(data);
    if ( !new_tail ) {
        return NULL;
    }

    if ( ds_list_is_empty(list) ) {
        list->head = new_tail;
        list->tail = new_tail;
    }
    else {
        struct ds_list_element * old_tail = list->tail;
        old_tail->next = new_tail;
        new_tail->previous = old_tail;
        list->tail = new_tail;
    }

    list->length++;
    return list;
}

void ds_list_remove_tail(ds_list list) {
    assert(list && !ds_list_is_empty(list));

    struct ds_list_element * old_tail = list->tail;
    struct ds_list_element * new_tail = old_tail->previous;

    if ( list->current == old_tail ) {

        /*  Invalidate current pointer if it points
         *  to the element which is about to be removed  */

        list->current = NULL;
    }

    if ( new_tail ) {

        /*  List will not be empty after removing this element  */

        list->tail = new_tail;
        new_tail->next = NULL;
    }
    else {

        /*  List wil be empty after removing this element  */

        list->tail = NULL;
        list->head = NULL;
    }

    list_element_destroy(old_tail, list->free_on_delete, list->data_destructor);
    list->length--;
}

void ds_list_remove_all(ds_list list) {
    assert(list);

    while ( !ds_list_is_empty(list) ) {
        ds_list_remove_tail(list);
    }
}

void * ds_list_element(ds_list list, const size_t index) {
    assert(list && index < ds_list_length(list));

    struct ds_list_element * current_element = list->head;
    size_t i = index;
    while ( current_element && i > 0 ) {
        current_element = current_element->next;
        --i;
    }

    if ( current_element ) {
        return current_element->data;
    }
    else {
        return NULL;
    }
}

size_t ds_list_length(ds_list list) {
    assert(list);
    return list->length;
}

bool ds_list_is_empty(ds_list list) {
    assert(list);
    return list->length == 0;
}

void ds_list_seek_start(ds_list list) {
    assert(list);
    list->current = list->head;
}

void ds_list_seek_end(ds_list list) {
    assert(list);
    list->current = list->tail;
}

void * ds_list_get_next_data(ds_list list) {
    assert(list);

    void * return_data = NULL;

    if ( list->current ) {
        return_data = list->current->data;
        list->current = list->current->next;
    }

    return return_data;
}

void * ds_list_get_prev_data(ds_list list) {
    assert(list);

    void * return_data = NULL;

    if ( list->current ) {
        return_data = list->current->data;
        list->current = list->current->previous;
    }

    return return_data;
}

static struct ds_list_element * list_element_create(void * data) {
    struct ds_list_element * new_element = malloc(sizeof *new_element);
    if ( !new_element ) {
        return NULL;
    }

    new_element->data = data;
    new_element->previous = NULL;
    new_element->next = NULL;

    return new_element;
}

static void list_element_destroy(struct ds_list_element * element,
                                 const bool data_free,
                                 void (*destructor)(void *)) {
    assert(element);

    if ( data_free ) {
        if ( destructor ) {
            destructor(element->data);
        }
        else {
            free(element->data);
        }
    }
    free(element);
}

