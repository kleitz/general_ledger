#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gl_general/gl_general.h"
#include "database/database.h"
#include "database/database_sql.h"
#include "datastruct/ds_result_set.h"
#include "datastruct/ds_list.h"

MYSQL * main_mss = NULL;
MYSQL * conn_mss = NULL;

static void db_error_quit(const char * msg, MYSQL * mss) {
    if ( mss ) {
        gl_log_msg("%s: %s", msg, mysql_error(mss));
    }
    else {
        gl_log_msg("%s");
    }
    exit(EXIT_FAILURE);
}

static void db_error_msg(const char * msg, MYSQL * mss) {
    if ( mss ) {
        gl_log_msg("%s: %s", msg, mysql_error(mss));
    }
    else {
        gl_log_msg("%s");
    }
}

void db_connect(const char * host, const char * database,
                const char * username, const char * password) {
    main_mss = mysql_init(NULL);
    if ( !main_mss ) {
        db_error_quit("Couldn't initialize mysql.", NULL);
    }

    conn_mss = mysql_real_connect(main_mss, host, username, password,
            database, 0, NULL, 0);
    if ( !conn_mss ) {
        db_error_quit("Couldn't connect to database", main_mss);
    }
    else {
        gl_log_msg("Connection was successful.");
    }
}

void db_close(void) {
    if ( !conn_mss ) {
        gl_error_quit("Closing connection which is not open.");
    }
    mysql_close(conn_mss);
    main_mss = NULL;
    conn_mss = NULL;
}

int db_execute_query(const char * query) {
    int ret_val;

    if ( conn_mss ) {
        int status = mysql_query(conn_mss, query);
        if ( status ) {
            db_error_msg("Query unsuccessful", conn_mss);
            ret_val = -1;
        }
        else {
            gl_log_msg("Query successful");
            ret_val = 0;
        }
    }
    else {
        gl_log_msg("Attempting to write query with no connection.");
        ret_val = -1;
    }

    return ret_val;
}

int db_list_users(void) {
    int ret_val = 0;

    if ( conn_mss ) {
        int status = mysql_query(conn_mss, "SELECT * FROM users");
        if ( status ) {
            db_error_msg("Query unsuccessful", conn_mss);
            ret_val = -1;
        }
        else {
            MYSQL_RES * result = mysql_store_result(conn_mss);
            if ( !result ) {
                ret_val = -1;
            }
            else {
                MYSQL_ROW row;
                while ( (row = mysql_fetch_row(result)) ) {
                    unsigned long * lengths = mysql_fetch_lengths(result);
                    printf("[%.*s] [%.*s] [%.*s]\n",
                            (int) lengths[0], row[0] ? row[0] : NULL,
                            (int) lengths[1], row[1] ? row[1] : NULL,
                            (int) lengths[2], row[2] ? row[2] : NULL);

                }

            }

            mysql_free_result(result);
        }
    }

    return ret_val;
}

ds_result_set db_create_result_set_from_query(const char * query) {

    if ( conn_mss ) {
        int status = mysql_query(conn_mss, query);
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
        ds_result_set result_set = ds_result_set_create(num_fields);

        ds_list field_names = ds_list_create(true, NULL);
        MYSQL_FIELD * fields = mysql_fetch_fields(result);
        for ( size_t i = 0; i < num_fields; ++i ) {
            char * f = strdup(fields[i].name);
            if ( !f ) {
                gl_error_quit("Couldn't duplicate string.");
            }
            ds_list_append(field_names, f);
        }

        ds_result_set_set_headers(result_set, field_names);

        while ( (row = mysql_fetch_row(result)) ) {
            ds_list record = ds_list_create(true, NULL);

            unsigned long * lengths = mysql_fetch_lengths(result);

            for ( size_t i = 0; i < num_fields; ++i ) {
                size_t buflen = lengths[i] ? lengths[i] + 1 : 7;
                char buffer[buflen];
                if ( lengths[i] ) {
                    sprintf(buffer, "%.*s", (int) lengths[i], row[i]);
                    buffer[buflen - 1] = '\0';
                }
                else {
                    strcpy(buffer, "(NULL)");
                }

                char * new_line = strdup(buffer);
                if ( !new_line ) {
                    gl_error_quit("Couldn't duplicate string.");
                }

                ds_list_append(record, new_line);
            }

            ds_result_set_add_record(result_set, record);
        }

        mysql_free_result(result);
        return result_set;
    }

    return NULL;
}
