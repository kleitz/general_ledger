/*!
 * \file            db_sampledata.c
 * \brief           Implementation of database sample data functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <assert.h>

#include "db_internal.h"
#include "file_ops/file_ops.h"
#include "gl_general/gl_general.h"

/*!
 * \brief           Adds sample data from a file to a database table.
 * \param table     The table into which to load the sample data.
 * \param filename  The filename from which to load the data. The file
 * should be a text file with each row containing a list of values
 * separated by ':' characters. The first row should contain the names
 * of the fields in the table. Blank lines and lines where the first
 * printable character is '#' are ignored.
 * \returns         `true` on success, `false` on failure.
 */
static bool db_add_sample_data(const char * table, const char * filename);

bool db_load_sample_data(void) {
    static const char * sample_data[][2] = {
        {"users", "sample_data/users"},
        {"entities", "sample_data/entities"},
        {"nomaccts", "sample_data/nomaccts"},
        {"jes", "sample_data/jes"},
        {NULL, NULL}
    };

    bool status = true;
    for ( size_t i = 0; sample_data[i][0]; ++i ) {
        gl_log_msg("Loading sample data for table %s...", sample_data[i][0]);
        status = db_add_sample_data(sample_data[i][0],
                                    sample_data[i][1]);
    }

    return status;
}

static bool db_add_sample_data(const char * table, const char * filename) {
    bool ret_val = true;

    ds_recordset data = delim_file_read(filename, ':');
    assert(data);
    ds_recordset_seek_start(data);

    ds_str query;
    while ( (query = ds_recordset_get_next_insert_query(data, table)) ) {
        ret_val = db_execute_query(ds_str_cstr(query));
        ds_str_destroy(query);

        if ( !ret_val ) {
            ds_recordset_destroy(data);
            return false;
        }
    }

    ds_recordset_destroy(data);
    return true;
}

