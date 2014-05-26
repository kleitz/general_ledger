/*!
 * \file            main.c
 * \brief           Main function for general_ledger.
 * \details         Main function for general_ledger.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdio.h>
#include <stdlib.h>
#include "gl_general.h"
#include "database.h"
#include "config_file_read/config_file_read.h"


/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */

int main(void) {
    gl_set_logging(true);
    //db_connect();
    //db_close();

    int status = config_file_read("test_conf.conf");
    if ( status == CONFIG_FILE_NO_FILE ) {
        gl_log_msg("Couldn't open config file.");
    }
    else if ( status == CONFIG_FILE_MALFORMED_FILE ) {
        gl_log_msg("Badly formed config file.");
    }

    config_file_print_all();

    const char * value;
    if ( (value = config_file_value("database")) ) {
        printf("Database: '%s'\n", value);
    }
    else {
        printf("Database not specified in config file.\n");
    }

    if ( (value = config_file_value("hostname")) ) {
        printf("Hostname: '%s'\n", value);
    }
    else {
        printf("Hostname not specified in config file.\n");
    }

    config_file_free();
    gl_set_logging(false);

    return EXIT_SUCCESS;
}
