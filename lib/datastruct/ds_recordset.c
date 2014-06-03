/*!
 * \file            ds_recordset.c
 * \brief           Implementation of query result set structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "datastruct/ds_recordset.h"
#include "datastruct/ds_record.h"
#include "datastruct/ds_list.h"
#include "datastruct/ds_str.h"

/*!  Result set structure  */
struct ds_recordset {
    size_t num_fields;          /*!<  The number of fields in a record  */
    size_t * field_lengths;     /*!<  Lengths of the longest fields     */
    ds_record headers;          /*!<  A list of field headers           */
    ds_list records;            /*!<  A list of records                 */
};

/*!
 * \brief           Updates the longest field lengths for a new record.
 * \details         The longest field lengths are stored to aid in the
 * production of reports. The same field in different records may have
 * different lengths, so a column in a report must have a width large
 * enough to hold them all. This functions checks the field lengths in the
 * specified record against the current longest field lengths, and increases
 * the longest field lengths to fit, if necessary. If this function is called
 * on every record added, and on the field headers, then the longest field
 * lengths will be just large enough for largest length in each individual
 * field.
 * \param set       The result set.
 * \param record    The record to check.
 */
static void ds_recordset_update_field_lengths(struct ds_recordset * set,
                                               ds_record record);

/*!
 * \brief           Returns the required length of a record text line.
 * \details         This function returns the length required - including
 * a terminating null character - to contain a text line for a record in
 * the current result set. This function should only be called after all
 * the records and headers have been added, and the longest field lengths
 * updated accordingly. The primary purpose of this function is to ensure
 * that text lines of a sufficient length can be allocated.
 * \param set       The results set.
 * \returns         The required length of a record text line.
 */
static size_t ds_recordset_get_record_line_length(struct ds_recordset * set);

/*!
 * \brief           Returns the sum total maximum length of all fields.
 * \param set       The results set.
 * \returns         The sum total maximum length of all fields.
 */
static size_t ds_recordset_get_total_field_length(struct ds_recordset * set);

/*!
 * \brief           Returns a formatted text line of field headers.
 * \details         This function is suitable for building a text report.
 * \param set       The result set.
 * \returns         A pointer to the line. The caller is responsible for
 * `free()`ing this pointer.
 */
static ds_str ds_recordset_get_headers_line(struct ds_recordset * set);

/*!
 * \brief           Returns a formatted text separator line.
 * \details         This function is suitable for building a text report.
 * \param set       The result set.
 * \returns         A pointer to the line. The caller is responsible for
 * `free()`ing this pointer.
 */
static ds_str ds_recordset_get_separator_line(struct ds_recordset * set);

/*!
 * \brief           Returns a formatted text line for the next record.
 * \details         This function returns the "current record", and advances
 * the current record pointer. Subsequent calls to this function will return
 * successive records.
 * \param list      The result set.
 * \returns         A pointer to the line, or `NULL` if the end of
 * the result set has been reached.
 */
static ds_str ds_recordset_get_next_line(struct ds_recordset * set);

/*!
 * \brief           Creates a formatted text line from a record.
 * \param set       The result set.
 * \param record    The record for which to construct the line.
 * \returns         A pointer the line, or `NULL` on failure. The caller
 * is responsible for `free()`ing this pointer.
 */
static ds_str ds_recordset_get_line_from_record(struct ds_recordset * set,
                                                 ds_record record);

/*!
 * \brief           Creates a comma-separated text line from a record.
 * \param set       The results set.
 * \param record    The record.
 * \returns         The line, or `NULL` on failure.
 */
/*
static ds_str ds_recordset_get_cs_line_from_record(struct ds_recordset * set,
                                                    ds_record record,
                                                    const bool squote);
*/
/*!
 * \brief           Adds a line to a report.
 * \param report    A pointer to the current place in the report.
 * \param line      A pointer to the dynamically allocated line. The function
 * will `free()` this pointer.
 * \returns         `report` advanced by `line_len` bytes.
 */
static ds_str add_line_to_report(ds_str report, ds_str line);

struct ds_recordset * ds_recordset_create(const size_t num_fields) {
    assert(num_fields > 0);

    struct ds_recordset * new_set = malloc(sizeof *new_set);
    if ( !new_set ) {
        return NULL;
    }

    new_set->num_fields = num_fields;
    new_set->headers = NULL;
    new_set->records = ds_list_create(true, ds_record_destructor);
    new_set->field_lengths = calloc(num_fields,
                                    sizeof *new_set->field_lengths);

    if ( !new_set->records || !new_set->field_lengths ) {
        ds_recordset_destroy(new_set);
        return NULL;
    }
    
    return new_set;
}

void ds_recordset_destroy(struct ds_recordset * set) {
    assert(set);

    if ( set->headers ) {
        ds_record_destroy(set->headers);
    }

    ds_list_destroy(set->records);
    free(set->field_lengths);
    free(set);
}

ds_record ds_recordset_add_record(struct ds_recordset * set,
                                   ds_record record) {
    assert(set && record);
    assert(ds_record_size(record) == ds_recordset_num_fields(set));

    struct ds_list * list = ds_list_append(set->records, record);
    if ( list ) {
        ds_recordset_update_field_lengths(set, record);
    }

    return record;
}

size_t ds_recordset_num_fields(struct ds_recordset * set) {
    assert(set);
    return set->num_fields;
}

size_t ds_recordset_num_records(struct ds_recordset * set) {
    assert(set);
    return ds_list_length(set->records);
}

void ds_recordset_set_headers(struct ds_recordset * set,
                               ds_record headers) {
    assert(set && headers);
    assert(ds_record_size(headers) == ds_recordset_num_fields(set));

    set->headers = headers;
    ds_recordset_update_field_lengths(set, headers);
}

ds_str ds_recordset_get_text_report(struct ds_recordset * set) {
    assert(set);

    ds_str report = ds_str_create("");

    ds_str line = ds_recordset_get_separator_line(set);
    ds_str check = add_line_to_report(report, line);

    line = ds_recordset_get_headers_line(set);
    if ( line ) {
        check = add_line_to_report(report, line);

        line = ds_recordset_get_separator_line(set);
        check = add_line_to_report(report, line);
    }

    ds_recordset_seek_start(set);

    while ( (line = ds_recordset_get_next_line(set)) ) {
        check = add_line_to_report(report, line);
    }
    
    line = ds_recordset_get_separator_line(set);
    check = add_line_to_report(report, line);

    (void)check;
    return report;
}

void ds_recordset_seek_start(struct ds_recordset * set) {
    assert(set);
    ds_list_seek_start(set->records);
}

ds_record ds_recordset_next_record(struct ds_recordset * set) {
    assert(set);
    return ds_list_get_next_data(set->records);
}
/*
char * ds_recordset_get_next_insert_query(struct ds_recordset * set,
                                           const char * table_name) {
    static char basic_query[] = "INSERT INTO %s (%s) VALUES (%s)";
    ds_list record = ds_recordset_next_record(set);
    if ( !record ) {
        return NULL;
    }

    char * headers = ds_recordset_get_cs_line_from_record(set,
            set->headers, false);
    char * values = ds_recordset_get_cs_line_from_record(set,
            record, true);
    size_t query_len = sizeof(basic_query) + strlen(table_name) +
                       strlen(headers) + strlen(values);

    char * line = malloc(query_len);
    if ( !line ) {
        return NULL;
    }

    sprintf(line, basic_query, table_name, headers, values);
    free(headers);
    free(values);

    return line;
}

static char * ds_recordset_get_cs_line_from_record(struct ds_recordset * set,
                                                 struct ds_list * record,
                                                 const bool squote) {
    assert(set);

    size_t line_len = ds_recordset_get_total_field_length(set);
    line_len += ds_recordset_num_fields(set) * 3;
    char * line = calloc(line_len, 1);
    if ( !line ) {
        return NULL;
    }

    ds_list_seek_start(record);
    char * line_ptr = line;
    for ( size_t i = 0; i < set->num_fields; ++i ) {
        char * field = ds_list_get_next_data(record);
        char * comma = (i == 0) ? "" : ",";
        char * quote = (squote) ? "'" : "";
        sprintf(line_ptr, "%s%s%s%s", comma, quote, field, quote);
        line_ptr += strlen(field) +
                    ((i == 0) ? 0 : 1) +
                    (squote ? 2 : 0);
    }

    return line;
}

*/
static ds_str ds_recordset_get_line_from_record(struct ds_recordset * set,
                                                ds_record record) {
    assert(set && record);

    ds_str new_line = ds_str_create("");

    for ( size_t i = 0; i < set->num_fields; ++i) {
        ds_str field = ds_record_get_field(record, i);
        assert(field);

        ds_str temp_str = ds_str_create_sprintf( "| %-*s ",
                (int) set->field_lengths[i],
                ds_str_cstr(field));
        ds_str_concat(new_line, temp_str);
        ds_str_destroy(temp_str);
    }

    ds_str_concat_cstr(new_line, "|");

    return new_line;
}

static void ds_recordset_update_field_lengths(struct ds_recordset * set,
                                               ds_record record) {
    assert(set && record);

    for ( size_t i = 0; i < set->num_fields; ++i ) {
        ds_str field = ds_record_get_field(record, i);
        size_t length = ds_str_length(field);
        if ( set->field_lengths[i] < length ) {
            set->field_lengths[i] = length;
        }
    }
}

static size_t
ds_recordset_get_record_line_length(struct ds_recordset * set) {
    static const size_t separator_width = 1;
    static const size_t padding_width = 1;
    static const size_t null_character_width = 1;

    assert(set);

    size_t record_line_length = null_character_width + separator_width;
    record_line_length += ds_recordset_get_total_field_length(set);
    record_line_length += set->num_fields *
                          (separator_width + padding_width * 2);

    return record_line_length;
}

static size_t
ds_recordset_get_total_field_length(struct ds_recordset * set) {
    assert(set);
    size_t fields_length = 0;
    for ( size_t i = 0; i < set->num_fields; ++i ) {
        fields_length += set->field_lengths[i];
    }
    return fields_length;
}

static ds_str ds_recordset_get_headers_line(struct ds_recordset * set) {
    assert(set);
    if ( set->headers ) {
        return ds_recordset_get_line_from_record(set, set->headers);
    }
    else {
        return NULL;
    }
}

static ds_str ds_recordset_get_separator_line(struct ds_recordset * set) {
    assert(set);

    const size_t line_size = ds_recordset_get_record_line_length(set);
    char * line = calloc(line_size, 1);
    if ( !line ) {
        return NULL;
    }

    size_t buf_idx = 0;
    for ( size_t fld_idx = 0; fld_idx < set->num_fields; ++fld_idx) {
        line[buf_idx++] = '+';
        for ( size_t i = 0; i < set->field_lengths[fld_idx] + 2; ++i ) {
            line[buf_idx++] = '-';
        }
    }

    line[buf_idx++] = '+';
    
    ds_str new_str = ds_str_create_direct(line, line_size);
    return new_str;
}

static ds_str ds_recordset_get_next_line(struct ds_recordset * set) {
    assert(set);

    ds_record record = ds_list_get_next_data(set->records);

    if ( record ) {
        return ds_recordset_get_line_from_record(set, record);
    }
    else {
        return NULL;
    }
}

ds_str add_line_to_report(ds_str report, ds_str line) {
    ds_str_concat(report, line);
    ds_str_concat_cstr(report, "\n");
    ds_str_destroy(line);
    return report;
}

