/*!
 * \file            main.c
 * \brief           Main function for general_ledger.
 * \details         Main function for general_ledger.
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
#include "config.h"
#include "datastruct/data_structures.h"
#include "file_ops/file_ops.h"

/*!
 * \brief           Logs a user in and retrieves the password.
 * \returns         The password.
 */
ds_str login(void);

/*!
 * \brief           Prints a program usage message.
 * \param progname  The program name.
 */
void print_usage_message(char * progname);

/*!
 * \brief           Prints a program version message.
 * \param progname  The program name.
 */
void print_version_message(char * progname);

/*!
 * \brief           Prints a program help message.
 * \param progname  The program name.
 */
void print_help_message(char * progname);

/*!
 * \brief           Casual test function.
 * \details         Used for casually testing program functionality.
 */
void test_functionality(void);

/*!  Casual testing flag  */
static const bool testing = false;

/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */
int main(int argc, char ** argv) {
    if ( testing ) {
        test_functionality();
        return 0;
    } 

    gl_set_logging(true);
    config_init();

    struct params * params = params_init();
    bool status = get_cmdline_options(argc, argv, params);
    ds_str value;

    if ( !status ) {
        print_usage_message(argv[0]);
    }
    else if ( config_value_get_cstr("help") ) {
        print_help_message(argv[0]);
    }
    else if ( config_value_get_cstr("version") ) {
        print_version_message(argv[0]);
    }
    else if ( config_value_get_cstr("login") ) {
        if ( !get_configuration(params) ) {
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
                else if ( (value = config_value_get_cstr("report")) ) {
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
                    else if ( !ds_str_compare_cstr(value, "currenttb") ) {
                        ds_str entity = config_value_get_cstr("entity");
                        if ( entity ) {
                            report = db_current_trial_balance_report(entity);
                        }
                        else {
                            gl_log_msg("Entity not specified.");
                        }
                    }

                    if ( report ) {
                        printf("%s", ds_str_cstr(report));
                        ds_str_destroy(report);
                    }
                    else {
                        gl_log_msg("Unrecognized report.");
                    }
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

ds_str login(void) {
    ds_str passwd = ds_str_create("");

    printf("Enter password (*WILL BE VISIBLE*): ");
    fflush(stdout);

    if ( !ds_str_getline(passwd, 80, stdin) ) {
        ds_str_destroy(passwd);
        gl_log_msg("Couldn't get password.");
        return NULL;
    }

    return passwd;
}

void print_usage_message(char * progname) {
    fprintf(stderr, "Usage: %s [options]\n", progname);
}

void print_help_message(char * progname) {
    print_usage_message(progname);
    printf("Options:\n");
    printf("  --help            Display this information\n");
    printf("  --version         Display version information\n");
    printf("  --create          Create database structure\n");
    printf("  --delete          Delete database structure\n");
    printf("  --entity <entity> Specifies an entity\n");
    printf("  --loadsample      Load sample data\n");
    printf("  --listusers       Show a list of users\n");
    printf("  --listentities    Show a list of entities\n");
    printf("  --listjes         Show a list of journal entries\n");
    printf("  --listjelines     Show a list of journal entry lines\n");
    printf("  --currenttb       Show a current trial balance for <entity>\n");
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
    ds_str initial_string = ds_str_create("Hello, world!");
    ds_str lss = ds_str_substr_left(initial_string, 6);
    ds_str rss = ds_str_substr_right(initial_string, 6);
    ds_str lss2 = ds_str_substr_left(initial_string, 100);
    ds_str rss2 = ds_str_substr_right(initial_string, 100);

    printf("Initial string: [%s]\n", ds_str_cstr(initial_string));
    printf("Left substring: [%s]\n", ds_str_cstr(lss));
    printf("Right substring: [%s]\n", ds_str_cstr(rss));
    printf("Left wide substring: [%s]\n", ds_str_cstr(lss2));
    printf("Right wide substring: [%s]\n", ds_str_cstr(rss2));

    ds_str main_string = ds_str_create("key=value");
    ds_str left;
    ds_str right;
    ds_str_split(main_string, &left, &right, '=');

    printf("Main string: [%s] (%zu)\n", ds_str_cstr(main_string), ds_str_length(main_string));
    printf("Left split: [%s] (%zu)\n", ds_str_cstr(left), ds_str_length(left));
    printf("Right right: [%s] (%zu)\n", ds_str_cstr(right), ds_str_length(right));

    ds_str unt1 = ds_str_create("    a string");
    printf("Untrimmed: [%s] (%zu)\n", ds_str_cstr(unt1), ds_str_length(unt1));
    ds_str_trim_leading(unt1);
    printf("Trimmed: [%s] (%zu)\n", ds_str_cstr(unt1), ds_str_length(unt1));

    ds_str unt2 = ds_str_create("a string    ");
    printf("Untrimmed: [%s] (%zu)\n", ds_str_cstr(unt2), ds_str_length(unt2));
    ds_str_trim_trailing(unt2);
    printf("Trimmed: [%s] (%zu)\n", ds_str_cstr(unt2), ds_str_length(unt2));

    ds_str unt3 = ds_str_create("   a string   ");
    printf("Untrimmed: [%s] (%zu)\n", ds_str_cstr(unt3), ds_str_length(unt3));
    ds_str_trim(unt3);
    printf("Trimmed: [%s] (%zu)\n", ds_str_cstr(unt3), ds_str_length(unt3));

    printf("%c %c %c\n", ds_str_char_at_index(unt3, 2),
                         ds_str_char_at_index(unt3, 3),
                         ds_str_char_at_index(unt3, 4));

    if ( ds_str_is_empty(unt3) ) {
        printf("unt3 is empty.\n");
    }
    else {
        printf("unt3 is not empty.\n");
    }

    ds_str str1 = ds_str_create("Hello, ");
    ds_str_concat_cstr(str1, "world!");
    printf("Concatenated: [%s] (%zu)\n", ds_str_cstr(str1), ds_str_length(str1));

    printf("Index of 'r': %d\n", ds_str_strchr(str1, 'r', 0));

    ds_str str3 = ds_str_create("Hello, world!");
    printf("Before assign: [%s] (%zu)\n", ds_str_cstr(str3),
                                          ds_str_length(str3));
    ds_str_assign_cstr(str3, "Goodbye, world!");
    printf("After assign: [%s] (%zu)\n", ds_str_cstr(str3),
                                         ds_str_length(str3));
    ds_str str4 = ds_str_create("Back to the world!");
    ds_str_assign(str3, str4);
    printf("After reassign: [%s] (%zu)\n", ds_str_cstr(str3),
                                           ds_str_length(str3));

    ds_str str5 = ds_str_create("1234");
    int n1;
    ds_str_intval(str5, 10, &n1);
    ds_str str6 = ds_str_create("5678stuff");
    int n2;
    ds_str_intval(str6, 10, &n2);
    printf("String: %s, int: %d\n", ds_str_cstr(str5), n1);
    printf("String: %s, int: %d\n", ds_str_cstr(str6), n2);

    ds_str str7 = ds_str_create("1234.5678");
    double d1;
    ds_str_doubleval(str7, &d1);
    ds_str str8 = ds_str_create("9876.5432stuff");
    double d2;
    ds_str_doubleval(str8, &d2);
    printf("String: %s, double: %.4f\n", ds_str_cstr(str7), d1);
    printf("String: %s, double: %.4f\n", ds_str_cstr(str8), d2);

    ds_str list = ds_str_create("token1:token2:token3:token4");
    ds_record tized = ds_record_tokenize(list, ':');
    for ( size_t i = 0; i < ds_record_size(tized); ++i ) {
        ds_str token = ds_record_get_field(tized, i);
        printf("Token %zu: %s\n", i + 1, ds_str_cstr(token));
    }
    ds_str tokenized = ds_record_make_delim_string(tized, ':');
    printf("Tokenized again: [%s]\n", ds_str_cstr(tokenized));
    ds_str_destroy(tokenized);
    tokenized = ds_record_make_values_string(tized, NULL);
    printf("To values string: [%s]\n", ds_str_cstr(tokenized));
    ds_str_destroy(tokenized);
    ds_record_destroy(tized);

    ds_str str9 = ds_str_create("Test string");
    if ( !ds_str_compare_cstr(str9, "Test string") ) {
        printf("OK! Strings compare equal.\n");
    }
    else {
        printf("Not OK! Strings do not compare equal.\n");
    }
                
    ds_str ld = ds_str_create("<tag>");
    ds_str rd = ds_str_create("</tag>");
    ds_str contents = ds_str_create("contents");

    ds_str tag1 = ds_str_decorate(contents, ld, rd);
    ds_str tag2 = ds_str_decorate(contents, ld, NULL);

    printf("Decorated 1: %s\n", ds_str_cstr(tag1));
    printf("Decorated 2: %s\n", ds_str_cstr(tag2));

    ds_str tv = ds_str_create("hello,1,1.45,0");
    ds_record tvtok = ds_record_tokenize(tv, ',');
    enum ds_field_types thetypes[] = {
        DS_FIELD_STRING,
        DS_FIELD_INT,
        DS_FIELD_DOUBLE,
        DS_FIELD_BOOLEAN
    };
    ds_str vs = ds_record_make_values_string(tvtok, thetypes);
    ds_record_destroy(tvtok);
    printf("Values string: %s\n", ds_str_cstr(vs));

    ds_str_destroy(initial_string);
    ds_str_destroy(lss);
    ds_str_destroy(rss);
    ds_str_destroy(lss2);
    ds_str_destroy(rss2);
    ds_str_destroy(main_string);
    ds_str_destroy(left);
    ds_str_destroy(right);
    ds_str_destroy(unt1);
    ds_str_destroy(unt2);
    ds_str_destroy(unt3);
    ds_str_destroy(str1);
    ds_str_destroy(str3);
    ds_str_destroy(str4);
    ds_str_destroy(str5);
    ds_str_destroy(str6);
    ds_str_destroy(str7);
    ds_str_destroy(str8);
    ds_str_destroy(str9);
    ds_str_destroy(list);
    ds_str_destroy(ld);
    ds_str_destroy(rd);
    ds_str_destroy(contents);
    ds_str_destroy(tag1);
    ds_str_destroy(tag2);
    ds_str_destroy(tv);
    ds_str_destroy(vs);
}

