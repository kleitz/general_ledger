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
#include "datastruct/ds_list.h"
#include "datastruct/ds_result_set.h"
#include "delim_file_read/delim_file_read.h"

char * login(void);
void print_usage_message(char * progname);
void print_version_message(char * progname);
void print_help_message(char * progname);
void test_functionality(void);

/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */

int main(int argc, char ** argv) {
    //test_functionality();
    //return 0;

    gl_set_logging(true);

    struct params * params = params_init();
    int status = get_cmdline_options(argc, argv, params);

    if ( status ) {
        print_usage_message(argv[0]);
    }
    else if ( params->help ) {
        print_help_message(argv[0]);
    }
    else if ( params->version ) {
        print_version_message(argv[0]);
    }
    else if ( params->create || params->list_users ) {
        if ( get_configuration(params) ) {
            gl_log_msg("Couldn't get parameters.");
        }
        else {
            params->password = login();
            if ( params->password ) {
                db_connect(params->hostname, params->database,
                           params->username, params->password);

                if ( params->list_users ) {
                    char * report = db_list_users_report();
                    printf("%s", report);
                    free(report);
                }
                else if ( params->create ) {
                    db_create_database_structure();
                }

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
    fprintf(stderr, "Usage: %s [options]\n", progname);
}

void print_help_message(char * progname) {
    print_usage_message(progname);
    printf("Options:\n");
    printf("  --help        Display this information\n");
    printf("  --version     Display version information\n");
    printf("  --create      Create database structure\n");
    printf("  --listusers   Show a list of users\n");
}

void print_version_message(char * progname) {
    printf("general_ledger (working title) 0.1 (experimental)\n");
    printf("Copyright (C) 2014 Paul Griffiths\n");
    printf("This is free software; see the source for copying conditions.  ");
    printf("There is NO\n");
    printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A ");
    printf("PARTICULAR PURPOSE.\n");
    (void)progname;
}

void test_functionality(void) {
    ds_result_set set = delim_file_read("sample_data/users");

    char * report = ds_result_set_get_text_report(set);
    printf("%s\n", report);
    free(report);

    ds_result_set_seek_start(set);
    char * query;
    while ( (query = ds_result_set_get_next_insert_query(set, "users")) ) {
        printf("%s\n", query);
        free(query);
    }

    ds_result_set_destroy(set);
}
