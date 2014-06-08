/*!
 * \file            db_mysql_general.c
 * \brief           Implementation of MYSQL database functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gl_general/gl_general.h"
#include "database/db_internal.h"

/*!  MYSQL initialization object.  */
MYSQL * main_mss = NULL;

/*!  MYSQL connection object.  */
MYSQL * conn_mss = NULL;

/*
static void db_error_quit(const char * msg, MYSQL * mss) {
    if ( mss ) {
        gl_log_msg("%s: %s", msg, mysql_error(mss));
    }
    else {
        gl_log_msg("%s");
    }
    exit(EXIT_FAILURE);
}
*/

/*!
 * \brief           Logs a MYSQL error message.
 * \param msg       The plain error message to log.
 * \param mss       The MYSQL connection from which to retrieve the MYSQL
 * error message.
 */
static void db_error_msg(const char * msg, MYSQL * mss);

bool db_connect(const char * host, const char * database,
                const char * username, const char * password) {
    main_mss = mysql_init(NULL);
    if ( !main_mss ) {
        db_error_msg("Couldn't initialize mysql.", NULL);
        return false;
    }

    conn_mss = mysql_real_connect(main_mss, host, username, password,
                                  database, 0, NULL, 0);
    if ( !conn_mss ) {
        db_error_msg("Couldn't connect to database", main_mss);
        return false;
    }

    return true;
}

void db_close(void) {
    if ( !conn_mss ) {
        gl_error_quit("Closing connection which is not open.");
    }
    mysql_close(conn_mss);
    main_mss = NULL;
    conn_mss = NULL;
}

bool db_execute_query(ds_str query) {
    bool ret_val = false;

    if ( conn_mss ) {
        int status = mysql_query(conn_mss, ds_str_cstr(query));
        if ( status ) {
            db_error_msg("Query unsuccessful", conn_mss);
        }
        else {
            gl_log_msg("Query successful");
            ret_val = true;
        }
    }
    else {
        gl_log_msg("Attempting to write query with no connection.");
    }

    return ret_val;
}

ds_recordset db_create_recordset_from_query(ds_str query) {
    if ( conn_mss ) {
        int status = mysql_query(conn_mss, ds_str_cstr(query));
        if ( status ) {
            db_error_msg("Query unsuccessful", conn_mss);
            return NULL;
        }

        MYSQL_RES * result = mysql_store_result(conn_mss);

        if ( !result ) {
            db_error_msg("Couldn't store result", conn_mss);
            return NULL;
        }

        MYSQL_ROW row;

        unsigned int num_fields = mysql_num_fields(result);
        ds_recordset set = ds_recordset_create(num_fields);

        ds_record field_names = ds_record_create(num_fields);
        MYSQL_FIELD * fields = mysql_fetch_fields(result);

        for ( size_t i = 0; i < num_fields; ++i ) {
            ds_str new_field = ds_str_create(fields[i].name);
            ds_record_set_field(field_names, i, new_field);
        }

        ds_recordset_set_headers(set, field_names);

        while ( (row = mysql_fetch_row(result)) ) {
            ds_record record = ds_record_create(num_fields);

            unsigned long * lengths = mysql_fetch_lengths(result);

            for ( size_t i = 0; i < num_fields; ++i ) {
                ds_str new_field;
                if ( lengths[i] ) {

                    /*  CHECK IF THIS IS BAD  */

                    new_field = ds_str_create_sprintf("%.*s",
                            (int) lengths[i], row[i]);
                }
                else {
                    new_field = ds_str_create("");
                }

                ds_record_set_field(record, i, new_field);
            }

            ds_recordset_add_record(set, record);
        }

        mysql_free_result(result);
        return set;
    }

    return NULL;
}

static void db_error_msg(const char * msg, MYSQL * mss) {
    if ( mss ) {
        gl_log_msg("%s: %s", msg, mysql_error(mss));
    }
    else {
        gl_log_msg("%s");
    }
}

