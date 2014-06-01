#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

#include <stdio.h>
#include <stdlib.h>

#include "gl_general/gl_general.h"
#include "database/database.h"

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
