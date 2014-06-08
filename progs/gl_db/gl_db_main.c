/*!
 * \file            gl_db_main.c
 * \brief           Main function for GL database program.
 * \details         Main function for GL database program.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gl_general/gl_general.h"
#include "database/database.h"
#include "gl_db_config.h"
#include "datastruct/data_structures.h"
#include "file_ops/file_ops.h"

/*!
 * \brief           Prints a program usage message.
 * \param progname  The program name.
 */
void print_usage_message(const char * progname);

/*!
 * \brief           Prints a program version message.
 * \param progname  The program name.
 */
void print_version_message(const char * progname);

/*!
 * \brief           Prints a program help message.
 * \param progname  The program name.
 */
void print_help_message(const char * progname);

/*!  Program name  */
static const char * program = "gl_db";

/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */
int main(int argc, char ** argv) {
    gl_set_logging(true);
    config_init();

    struct params * params = params_init();
    bool status = get_cmdline_options(argc, argv, params);

    if ( !status ) {
        print_usage_message(program);
    }
    else if ( config_value_get_cstr("help") ) {
        print_help_message(program);
    }
    else if ( config_value_get_cstr("version") ) {
        print_version_message(program);
    }
    else if ( config_value_get_cstr("login") ) {
        if ( !get_configuration(params, "conf_files/gl_db_conf.conf") ) {
            gl_log_msg("Couldn't get parameters.");
        }
        else {
            params->password = login();
            if ( params->password ) {
                db_connect(ds_str_cstr(params->hostname),
                           ds_str_cstr(params->database),
                           ds_str_cstr(params->username),
                           ds_str_cstr(params->password));

                if ( config_value_get_cstr("create") ) {
                    db_create_database_structure();
                }
                else if ( config_value_get_cstr("delete") ) {
                    db_delete_database_structure();
                }
                else if ( config_value_get_cstr("loadsample") ) {
                    db_load_sample_data();
                }
                else {
                    gl_log_msg("No supported option provided.");
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
    config_free();
    gl_set_logging(false);

    return EXIT_SUCCESS;
}

void print_usage_message(const char * progname) {
    fprintf(stderr, "Usage: %s [options]\n", progname);
}

void print_help_message(const char * progname) {
    print_usage_message(progname);
    printf("General options:\n");
    printf("  --help            Display this information\n");
    printf("  --version         Display version information\n");
    printf("\nDatabase options:\n");
    printf("  --create          Create database structure\n");
    printf("  --delete          Delete database structure\n");
    printf("  --loadsample      Load sample data\n");
}

void print_version_message(const char * progname) {
    printf("%s (working title) 0.1 (experimental)\n", progname);
    printf("Copyright (C) 2014 Paul Griffiths\n");
    printf("This is free software; see the source for copying conditions.  ");
    printf("There is NO\n");
    printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A ");
    printf("PARTICULAR PURPOSE.\n");
    (void)progname;
}

