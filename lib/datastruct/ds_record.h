/*!
 * \file            ds_record.h
 * \brief           Interface to record data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_RECORD_H
#define PG_GENERAL_LEDGER_DS_RECORD_H

#include <stddef.h>
#include <stdbool.h>

#include "ds_str.h"

/*!  Typedef for opaque record datatype  */
typedef struct ds_record * ds_record;

/*!
 * \brief                   Creates a new record.
 * \param size              The size of the record.
 * \returns                 A newly created record, or `NULL` on failure.
 */
ds_record ds_record_create(const size_t size);

/*!
 * \brief           Destroys a record and frees any associated resources.
 * \param record    The record to destroy.
 */
void ds_record_destroy(ds_record record);

/*!
 * \brief           A record destructor function.
 * \param record    The record to destroy.
 */
void ds_record_destructor(void * record);

/*!
 * \brief           Clears and `free()`s all the elements in a record.
 * \param record    The record.
 */
void ds_record_clear(ds_record record);

/*!
 * \brief           Sets a field of a record.
 * \details         If the field is currently occupied, the existing
 * field is `free()`d.
 * \param record    The record to set.
 * \param index     The index of the field to set.
 * \param field     The value to which to set the field.
 */
void ds_record_set_field(ds_record record, const size_t index, ds_str field);

/*!
 * \brief           Retrieves the field at a specified index.
 * \param record    The record from which to retrieve.
 * \param index     The index of the desired field.
 * \returns         A pointer to the field, or `NULL` if the index is out
 * of range.
 */
ds_str ds_record_get_field(ds_record record, const size_t index);

/*!
 * \brief           Returns the size of a record.
 * \param record    The record.
 * \returns         The size of the record.
 */
size_t ds_record_size(ds_record record);

/*!
 * \brief           Sets the current field to the first field of a record.
 * \param record    The record.
 */
void ds_record_seek_start(ds_record record);

/*!
 * \brief           Returns the next field of the record.
 * \details         This function returns the data of the "current field",
 * and advances the current field pointer. Subsequent calls to this function
 * will return successive fields.
 * \param record    The record.
 * \returns         A pointer to the next field, or `NULL` if the end of
 * the record has been reached.
 */
ds_str ds_record_get_next_data(ds_record record);

/*!
 * \brief           Tokenizes a string into a record.
 * \param str       The string to tokenize.
 * \param delim     The delimiting character.
 * \returns         A new record containing the tokens.
 */
ds_record ds_record_tokenize(ds_str str, const char delim);

/*!
 * \brief           Makes a delimited string from a record.
 * \param record    The record.
 * \param delim     The delimiting character.
 * \returns         The delimited string, or `NULL` on failure.
 */
ds_str ds_record_make_delim_string(ds_record record, const char delim);

/*!
 * \brief           Makes a delimited SQL values string from a record.
 * \param record    The record.
 * \returns         The delimited values string, or `NULL` on failure.
 */
ds_str ds_record_make_values_string(ds_record record);

#endif      /*  PG_GENERAL_LEDGER_DS_RECORD_H  */

