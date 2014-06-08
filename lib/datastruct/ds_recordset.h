/*!
 * \file            ds_recordset.h
 * \brief           Interface to record set structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_RECORD_SET_H
#define PG_GENERAL_LEDGER_DS_RECORD_SET_H

#include "ds_record.h"
#include "ds_str.h"
#include "ds_fieldtypes.h"

/*!  Typedef for opaque record set data type  */
typedef struct ds_recordset * ds_recordset;

/*!
 * \brief               Creates a new record set.
 * \param num_fields    The non-zero number of fields in the record set.
 * \returns             A pointer to the new record set.
 */
ds_recordset ds_recordset_create(const size_t num_fields);

/*!
 * \brief           Destroys a record set and frees associated resources.
 * \param set       The record set to destroy.
 */
void ds_recordset_destroy(ds_recordset set);

/*!
 * \brief           Adds a record to a record set.
 * \details         The record *must* have the same number of fields as
 * the number of fields provided to `ds_recordset_create()`.
 * \param set       The record set to which to add.
 * \param record    The record to add.
 * \returns         A pointer to the new record (i.e. it returns the
 * second parameter) or `NULL` on failure.
 */
ds_record ds_recordset_add_record(ds_recordset set, ds_record record);

/*!
 * \brief           Returns the number of fields in a record set.
 * \param set       The record set.
 * \returns         The number of fields in the record set.
 */
size_t ds_recordset_num_fields(ds_recordset set);

/*!
 * \brief           Returns the number of records in a record set.
 * \param set       The record set.
 * \returns         The number of records in the record set.
 */
size_t ds_recordset_num_records(ds_recordset set);

/*!
 * \brief           Sets the record headers in a record set.
 * \param set       The record set.
 * \param headers   The headers, in the form of a `ds_record` of strings.
 * The list *must* have the same number of elements as the number of fields
 * provided to `ds_recordset_create()`.
 */
void ds_recordset_set_headers(ds_recordset set, ds_record headers);

/*!
 * \brief           Sets the type for a specified field.
 * \param set       The record set.
 * \param index     The index to set.
 * \param type      The type for the field at the specified index.
 */
void ds_recordset_set_type(ds_recordset set,
                           const size_t index,
                           const enum ds_field_types type);
/*!
 * \brief           Returns a formatted text report for the record set.
 * \details         The report is returned as a single multi-line string.
 * \param set       The record set.
 * \returns         A pointer to the report. The caller is responsible for
 * `free()`ing this pointer.
 */
ds_str ds_recordset_get_text_report(ds_recordset set);

/*!
 * \brief               Gets the next SQL INSERT query.
 * \param set           The set.
 * \param table_name    The table name into which to insert.
 * \returns             The query. Caller is responsible for `free()`ing.
 */
ds_str ds_recordset_get_next_insert_query(ds_recordset set,
                                           const char * table_name);
/*!
 * \brief           Sets the current record to the first record.
 * \param set       The record set.
 */
void ds_recordset_seek_start(ds_recordset set);

/*!
 * \brief           Returns the next record in the record set.
 * \details         This function returns the "current record", and advances
 * the current record pointer. Subsequent calls to this function will return
 * successive records.
 * \param set       The record set.
 * \returns         A pointer to the next record, or `NULL` if the end of
 * the record set has been reached.
 */
ds_record ds_recordset_next_record(ds_recordset set);

#endif      /*  PG_GENERAL_LEDGER_DS_RECORD_SET_H  */

