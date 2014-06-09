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
                    ds_report report = ds_report_create();
                    assert(report);
                    bool no_report = false;

                    if ( !ds_str_compare_cstr(value, "listusers") ) {
                        ds_report_set_report_text(report,
                                                  db_list_users_report());
                        ds_report_set_title(report,
                                ds_str_create("Users List"));
                    }
                    else if ( !ds_str_compare_cstr(value, "listentities") ) {
                        ds_report_set_report_text(report,
                                                  db_list_entities_report());
                        ds_report_set_title(report,
                                ds_str_create("Entities List"));
                    }
                    else if ( !ds_str_compare_cstr(value, "listnomaccts") ) {
                        ds_report_set_report_text(report,
                                                  db_list_nomaccts_report());
                        ds_report_set_title(report,
                                ds_str_create("Nominal Accounts List"));
                    }
                    else if ( !ds_str_compare_cstr(value, "listjes") ) {
                        ds_report_set_report_text(report,
                                                  db_list_jes_report());
                        ds_report_set_title(report,
                                ds_str_create("Journal Entries Report"));
                    }
                    else if ( !ds_str_compare_cstr(value, "listjelines") ) {
                        ds_report_set_report_text(report,
                                                  db_list_jelines_report());
                        ds_report_set_title(report,
                            ds_str_create("Journal Entry Lines Report"));
                    }
                    else if ( !ds_str_compare_cstr(value, "listjesrcs") ) {
                        ds_report_set_report_text(report,
                                                  db_list_jesrcs_report());
                        ds_report_set_title(report,
                            ds_str_create("Journal Entry Sources Report"));
                    }
                    else if ( !ds_str_compare_cstr(value, "standingdata") ) {
                        ds_report_set_report_text(report,
                                              db_show_standingdata_report());
                        ds_report_set_title(report,
                            ds_str_create("Standing Data Report"));
                    }
                    else if ( !ds_str_compare_cstr(value, "currenttb") ) {
                        ds_str entity = config_value_get_cstr("entity");
                        ds_report_set_report_text(report,
                                      db_current_trial_balance_report(entity));
                        ds_report_set_title(report,
                            ds_str_create("Current Trial Balance"));

                        ds_str h_name = ds_str_create("Entity");
                        ds_str h_value = db_get_entity_name_from_id(entity);
                        /*
                        if ( entity ) {
                            h_value = ds_str_create_sprintf("[%s]",
                                    ds_str_cstr(entity));
                        }
                        else {
                            h_value = ds_str_create("All entities");
                        }
                        */
                        ds_report_add_header(report, h_name, h_value);
                        ds_str_destroy(h_name);
                        ds_str_destroy(h_value);
                    }
                    else if ( !ds_str_compare_cstr(value, "checktotal") ) {
                        ds_str entity = config_value_get_cstr("entity");
                        ds_report_set_report_text(report,
                                      db_check_total_report(entity));
                        ds_report_set_title(report,
                            ds_str_create("Double Entry Check Total Report"));
                    }
                    else if ( !ds_str_compare_cstr(value, "entries") ) {
                        ds_str je_num = config_value_get_cstr("je_num");
                        ds_report_set_report_text(report,
                                      db_all_jes_report(je_num));
                        ds_report_set_title(report,
                            ds_str_create("Detailed Journal Entry Report"));
                    }
                    else {
                        no_report = true;
                    }

                    if ( !no_report ) {
                        ds_report_print_text_report(report, stdout);
                        ds_report_destroy(report);
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
    printf("  --help                Display this information\n");
    printf("  --version             Display version information\n");
    printf("\nReporting options:\n");
    printf("  --entity <entity>     Specifies an entity\n");
    printf("  --listusers           Show a list of users\n");
    printf("  --listentities        Show a list of entities\n");
    printf("  --listnomaccts        Show a list of nominal accounts\n");
    printf("  --listjes             Show a list of simple journal entries\n");
    printf("  --listjelines         Show a list of journal entry lines\n");
    printf("  --listjesrcs          Show a list of journal entry sources\n");
    printf("  --standingdata        Show the standing data\n");
    printf("  --currenttb           Show a current trial balance\n");
    printf("                               (optionally for <entity>)\n");
    printf("  --checktotal          Show double entry check totals\n");
    printf("                               (optionally for <entity>)\n");
    printf("  --entries[=<je_num>]  Show detailed journal entries\n");
    printf("                               (optionally for <je_num> only)\n");
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

