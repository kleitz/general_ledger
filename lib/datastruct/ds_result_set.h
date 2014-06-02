/*!
 * \file            ds_result_set.h
 * \brief           Interface to query result set structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_RESULT_SET_H
#define PG_GENERAL_LEDGER_DS_RESULT_SET_H

#include "datastruct/ds_list.h"

/*!  Typedef for opaque result set data type  */
typedef struct ds_result_set * ds_result_set;

/*!  Typedef for opaque record data type  */
typedef struct ds_list * ds_record;

/*!
 * \brief               Creates a new result set.
 * \param num_fields    The non-zero number of fields in the result set.
 * \returns             A pointer to the new result set.
 */
ds_result_set ds_result_set_create(const size_t num_fields);

/*!
 * \brief           Destroys a result set and frees associated resources.
 * \param set       The result set to destroy.
 */
void ds_result_set_destroy(ds_result_set set);

/*!
 * \brief           Adds a record to a result set.
 * \details         A "record" in a result set is a `ds_list` of strings.
 * The list *must* have the same number of elements as the number of fields
 * provided to `ds_result_set_create()`.
 * \param set       The result set to which to add.
 * \param record    The record to add.
 * \returns         A pointer to the new record (i.e. it returns the
 * second parameter) or `NULL` on failure.
 */
ds_record ds_result_set_add_record(ds_result_set set, ds_list record);

/*!
 * \brief           Returns the number of fields in a result set.
 * \param set       The result set.
 * \returns         The number of fields in the result set.
 */
size_t ds_result_set_num_fields(ds_result_set set);

/*!
 * \brief           Sets the record headers in a record set.
 * \param set       The result set.
 * \param headers   The headers, in the form of a `ds_list` of strings.
 * The list *must* have the same number of elements as the number of fields
 * provided to `ds_result_set_create()`.
 */
void ds_result_set_set_headers(ds_result_set set, ds_list headers);

/*!
 * \brief           Returns a formatted text report for the result set.
 * \details         The report is returned as a single multi-line string.
 * \param set       The result set.
 * \returns         A pointer to the report. The caller is responsible for
 * `free()`ing this pointer.
 */
char * ds_result_set_get_text_report(ds_result_set set);

/*!
 * \brief           Sets the current record to the first record.
 * \param set       The result set.
 */
void ds_result_set_seek_start(ds_result_set set);

/*!
 * \brief           Sets the current record to the last record.
 * \param set       The result set.
 */
void ds_result_set_seek_end(ds_result_set set);

/*!
 * \brief           Returns the next record in the result set.
 * \details         This function returns the "current record", and advances
 * the current record pointer. Subsequent calls to this function will return
 * successive records.
 * \param list      The result set.
 * \returns         A pointer to the next record, or `NULL` if the end of
 * the result set has been reached.
 */
ds_record ds_result_set_get_next_data(ds_result_set set);

/*!
 * \brief           Returns the previous record in the result set.
 * \details         This function returns the "current record", and decrements
 * the current record pointer. Subsequent calls to this function will return
 * successively earlier records.
 * \param list      The result set.
 * \returns         A pointer to the next record, or `NULL` if the start of
 * the result set has been reached.
 */
ds_record ds_result_set_get_prev_data(ds_result_set set);

#endif      /*  PG_GENERAL_LEDGER_DS_RESULT_SET_H  */

