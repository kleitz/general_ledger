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
#include "gl_general/gl_general.h"
#include "database/database.h"
#include "config.h"
#include "datastruct/data_structures.h"
#include "delim_file_read/delim_file_read.h"

ds_str login(void);
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
    else if ( params->create || params->list_users ||
              params->delete_data || params->sample ||
              params->list_entities ) {
        if ( get_configuration(params) ) {
            gl_log_msg("Couldn't get parameters.");
        }
        else {
            params->password = login();
            if ( params->password ) {
                db_connect(ds_str_cstr(params->hostname),
                           ds_str_cstr(params->database),
                           ds_str_cstr(params->username),
                           ds_str_cstr(params->password));

                if ( params->create ) {
                    db_create_database_structure();
                }
                else if ( params->delete_data ) {
                    db_delete_database_structure();
                }
                else if ( params->sample ) {
                    db_load_sample_data();
                }
                else if ( params->list_users ) {
                    ds_str report = db_list_users_report();
                    printf("%s", ds_str_cstr(report));
                    ds_str_destroy(report);
                }
                else if ( params->list_entities ) {
                    ds_str report = db_list_entities_report();
                    printf("%s", ds_str_cstr(report));
                    ds_str_destroy(report);
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

ds_str login(void) {
    char buffer[30] = {0};
    ds_str passwd = NULL;

    printf("Enter password (*WILL BE VISIBLE*): ");
    fflush(stdout);

    if ( fgets(buffer, 30, stdin) ) {
        size_t length = strlen(buffer);
        if ( length && buffer[length - 1] == '\n' ) {
            buffer[length - 1] = '\0';
        }

        passwd = ds_str_create(buffer);
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
    printf("  --help            Display this information\n");
    printf("  --version         Display version information\n");
    printf("  --create          Create database structure\n");
    printf("  --delete          Delete database structure\n");
    printf("  --loadsample      Load sample data\n");
    printf("  --listusers       Show a list of users\n");
    printf("  --listentities    Show a list of entities\n");
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
}

