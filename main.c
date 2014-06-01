/*!
 * \file            main.c
 * \brief           Main function for general_ledger.
 * \details         Main function for general_ledger.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gl_general/gl_general.h"
#include "database/database.h"
#include "config.h"

char * login(void);

/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */

int main(void) {
    gl_set_logging(true);

    char * passwd = login();

    if ( passwd ) {
        struct params * params = get_configuration(passwd);
        if ( params ) {
            db_connect(params->hostname, params->database,
                       params->username, params->password);
            db_close();
            params_free(params);
        }
        else {
            gl_log_msg("Couldn't get parameters.");
            free(passwd);
        }

        //db_connect();
        //db_close();
    }

    gl_set_logging(false);

    return EXIT_SUCCESS;
}

char * login(void) {
    char buffer[30] = {0};
    char * passwd = NULL;

    printf("Enter password (*WILL BE VISIBLE*): ");
    fflush(stdout);

    if ( fgets(buffer, 30, stdin) ) {
        size_t length = strlen(buffer);
        if ( length && buffer[length - 1] == '\n' ) {
            buffer[length - 1] = '\0';
        }

        passwd = strdup(buffer);
        if ( !passwd ) {
            gl_log_msg("Couldn't allocate memory for password.");
        }
    }
    else {
        gl_log_msg("Couldn't get password.");
    }

    return passwd;
}
