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
#include "gl_reports_config.h"
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
static const char * program = "gl_reports";

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
    ds_str value;

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

                if ( (value = config_value_get_cstr("report")) ) {
                    ds_str report = NULL;

                    if ( !ds_str_compare_cstr(value, "listusers") ) {
                        report = db_list_users_report();
                    }
                    else if ( !ds_str_compare_cstr(value, "listentities") ) {
                        report = db_list_entities_report();
                    }
                    else if ( !ds_str_compare_cstr(value, "listjes") ) {
                        report = db_list_jes_report();
                    }
                    else if ( !ds_str_compare_cstr(value, "listjelines") ) {
                        report = db_list_jelines_report();
                    }
                    else if ( !ds_str_compare_cstr(value, "listjesrcs") ) {
                        report = db_list_jesrcs_report();
                    }
                    else if ( !ds_str_compare_cstr(value, "standingdata") ) {
                        report = db_show_standingdata_report();
                    }
                    else if ( !ds_str_compare_cstr(value, "currenttb") ) {
                        ds_str entity = config_value_get_cstr("entity");
                        report = db_current_trial_balance_report(entity);
                    }
                    else if ( !ds_str_compare_cstr(value, "checktotal") ) {
                        ds_str entity = config_value_get_cstr("entity");
                        report = db_check_total_report(entity);
                    }

                    if ( report ) {
                        printf("%s", ds_str_cstr(report));
                        ds_str_destroy(report);
                    }
                    else {
                        gl_log_msg("Unrecognized report.");
                    }
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
    printf("\nReporting options:\n");
    printf("  --entity <entity> Specifies an entity\n");
    printf("  --listusers       Show a list of users\n");
    printf("  --listentities    Show a list of entities\n");
    printf("  --listjes         Show a list of journal entries\n");
    printf("  --listjelines     Show a list of journal entry lines\n");
    printf("  --listjesrcs      Show a list of journal entry sources\n");
    printf("  --standingdata    Show the standing data\n");
    printf("  --currenttb       Show a current trial balance\n");
    printf("                                   (optionally for <entity>)\n");
    printf("  --checktotal      Show double entry check totals\n");
    printf("                                   (optionally for <entity>)\n");
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

