/*!
 * \file            ds_vector.h
 * \brief           Interface to generic doubly-linked vector data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_VECTOR_H
#define PG_GENERAL_LEDGER_DS_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

/*!  Typedef for opaque vector datatype  */
typedef struct ds_vector * ds_vector;

/*!
 * \brief                   Creates a new vector.
 * \param size              The size of the vector.
 * \param free_on_delete    Set to `true` if the vector elements should be
 * destroyed when removed from the vector, and when the vector itself is
 * destroyed. If set to `false`, the caller is responsible for destroying
 * the elements prior to destroying the vector.
 * \param destructor        Pointer to a destructor function to use for 
 * destroying the vector elements, when `free_on_delete` is true. If this is
 * set to `NULL`, `free()` from the standard C library will be used to
 * destroy the elements.
 * \returns                 A newly created vector, or `NULL` on failure.
 */
ds_vector ds_vector_create(const size_t size,
                           const bool free_on_delete,
                           void (*destructor)(void *));

/*!
 * \brief           Destroys a vector and frees any associated resources.
 * \param vector    The vector to destroy.
 */
void ds_vector_destroy(ds_vector vector);

/*!
 * \brief           A vector destructor function.
 * \details         This function may be passed to `ds_vector_create()`
 * when creating a vector of vectors. It calls `ds_vector_destroy()`, but the
 * parameter of `ds_vector_destroy()` is not compatible with the function
 * signature expected by `ds_vector_create()`, so this function provides an
 * appropriate interface.
 * \param vector    The vector to destroy.
 */
void ds_vector_destructor(void * vector);

/*!
 * \brief           Clears all the elements in a vector.
 * \details         If the vector was created with `free_on_delete`, the
 * elements are `free()`d prior to being cleared (i.e. set to `NULL`).
 * \param vector    The vector.
 */
void ds_vector_clear(ds_vector vector);

/*!
 * \brief           Sets an element of a vector.
 * \details         If the element is currently occupied, the existing
 * element is `free()`d.
 * \param vector    The vector to which to set.
 * \param index     The index of the element to set.
 * \param element   The element to set.
 */
void ds_vector_set(ds_vector vector, const size_t index, void * element);

/*!
 * \brief           Retrieves the data at a specified index.
 * \param vector    The vector from which to retrieve.
 * \param index     The index of the desired element.
 * \returns         A pointer to the data, or `NULL` if the index is out
 * of range.
 */
void * ds_vector_element(ds_vector vector, const size_t index);

/*!
 * \brief           Returns the size of a vector.
 * \param vector    The vector.
 * \returns         The size of the vector.
 */
size_t ds_vector_size(ds_vector vector);

/*!
 * \brief           Sets the current element to the first element of a vector.
 * \param vector    The vector.
 */
void ds_vector_seek_start(ds_vector vector);

/*!
 * \brief           Returns the next element of the vector.
 * \details         This function returns the data of the "current element",
 * and advances the current element pointer. Subsequent calls to this function
 * will return successive elements.
 * \param vector    The vector.
 * \returns         A pointer to the next element, or `NULL` if the end of
 * the vector has been reached.
 */
void * ds_vector_get_next_data(ds_vector vector);

#endif      /*  PG_GENERAL_LEDGER_DS_VECTOR_H  */

