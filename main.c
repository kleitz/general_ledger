/*!
 * \file            main.c
 * \brief           Main function for general_ledger.
 * \details         Main function for general_ledger.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
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
void print_usage_message(char * progname);
void print_help_message(char * progname);

/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */

int main(int argc, char ** argv) {
    gl_set_logging(true);

    struct params * params = params_init();
    int status = get_cmdline_options(argc, argv, params);

    if ( status ) {
        print_usage_message(argv[0]);
    }
    else if ( params->help ) {
        print_help_message(argv[0]);
    }
    else if ( params->create ) {
        if ( get_configuration(params) ) {
            gl_log_msg("Couldn't get parameters.");
        }
        else {
            params->password = login();
            if ( params->password ) {
                db_connect(params->hostname, params->database,
                           params->username, params->password);
                db_close();
            }
            else {
                gl_log_msg("Couldn't get password.\n");
            }
        }
    }
    else {
        printf("No options specified.\n");
    }

    params_free(params);
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

void print_usage_message(char * progname) {
    fprintf(stderr, "Usage: %s [-h] [-c]\n", progname);
}

void print_help_message(char * progname) {
    print_usage_message(progname);
    printf("Options:\n");
    printf("  -h            Show this help message.\n");
    printf("  -c            Create database structure.\n");
}

