/*!
 * \file            ds_list.h
 * \brief           Interface to generic doubly-linked list data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_LIST_H
#define PG_GENERAL_LEDGER_DS_LIST_H

#include <stddef.h>
#include <stdbool.h>

/*!  Typedef for opaque list datatype  */
typedef struct ds_list * ds_list;

/*!
 * \brief                   Creates a new list.
 * \param free_on_delete    Set to `true` if the list elements should be
 * destroyed when removed from the list, and when the list itself is
 * destroyed. If set to `false`, the caller is responsible for destroying
 * the elements prior to destroying the list.
 * \param destructor        Pointer to a destructor function to use for 
 * destroying the list elements, when `free_on_delete` is true. If this is
 * set to `NULL`, `free()` from the standard C library will be used to
 * destroy the elements.
 * \returns                 A newly created list, or `NULL` on failure.
 */
ds_list ds_list_create(const bool free_on_delete, void (*destructor)(void *));

/*!
 * \brief           Destroys a list and frees any associated resources.
 * \param list      The list to destroy.
 */
void ds_list_destroy(ds_list list);

/*!
 * \brief           A list destructor function.
 * \details         This function may be passed to `ds_list_create()`
 * when creating a list of lists. It calls `ds_list_destroy()`, but the
 * parameter of `ds_list_destroy()` is not compatible with the function
 * signature expected by `ds_list_create()`, so this function provides an
 * appropriate interface.
 * \param list      The list to destroy.
 */
void ds_list_destructor(void * list);

/*!
 * \brief           Appends an element to a list.
 * \param list      The list to which to append.
 * \param element   The element to append.
 * \returns         The same list, or `NULL` on failure.
 */
ds_list ds_list_append(ds_list list, void * element);

/*!
 * \brief           Removes the last element of a list.
 * \param list      The list from which to remove.
 */
void ds_list_remove_tail(ds_list list);

/*!
 * \brief           Removes all the elements from a list.
 * \param list      The list from which to remove.
 */
void ds_list_remove_all(ds_list list);

/*!
 * \brief           Retrieves the data at a specified index.
 * \param list      The list from which to retrieve.
 * \param index     The index of the desired element.
 * \returns         A pointer to the data, or `NULL` if the index is out
 * of range.
 */
void * ds_list_element(ds_list list, const size_t index);

/*!
 * \brief           Returns the number of elements in a list.
 * \param list      The list.
 * \returns         The number of elements in the list.
 */
size_t ds_list_length(ds_list list);

/*!
 * \brief           Checks if a list is empty.
 * \param list      The list to check.
 * \returns         `true` is the list is empty, `false` otherwise.
 */
bool ds_list_is_empty(ds_list list);

/*!
 * \brief           Sets the current element to the first element of a list.
 * \param list      The list.
 */
void ds_list_seek_start(ds_list list);

/*!
 * \brief           Sets the current element to the last element of a list.
 * \param list      The list.
 */
void ds_list_seek_end(ds_list list);

/*!
 * \brief           Returns the next element of the list.
 * \details         This function returns the data of the "current element",
 * and advances the current element pointer. Subsequent calls to this function
 * will return successive elements.
 * \param list      The list.
 * \returns         A pointer to the next element, or `NULL` if the end of
 * the list has been reached.
 */
void * ds_list_get_next_data(ds_list list);

/*!
 * \brief           Returns the previous element of the list.
 * \details         This function returns the data of the "current element",
 * and decrements the current element pointer. Subsequent calls to this
 * function will return successively earlier elements.
 * \param list      The list.
 * \returns         A pointer to the previous element, or `NULL` if the start
 * of the list has been reached.
 */
void * ds_list_get_prev_data(ds_list list);

#endif      /*  PG_GENERAL_LEDGER_DS_LIST_H  */

