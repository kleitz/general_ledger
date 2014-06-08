/*!
 * \file            config.c
 * \brief           Implementation of program configuration functionality.
 * \details         Gets program configuration options from the command line
 * and/or a configuration file.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  UNIX feature test macro  */
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "config.h"
#include "file_ops/file_ops.h"
#include "datastruct/data_structures.h"
#include "gl_general/gl_general.h"

/*!
 * \brief           Gets a value from a configuration file key.
 * \param key       The key for the desired value.
 * \returns         The desired value, or `NULL` if the key is not set.
 */
static ds_str get_param_from_config(const char *key);

struct params *params_init(void) {
    struct params *new_params = malloc(sizeof *new_params);
    if (new_params) {
        new_params->hostname = NULL;
        new_params->database = NULL;
        new_params->username = NULL;
        new_params->password = NULL;
        new_params->help = false;
        new_params->create = false;
        new_params->delete_data = false;
        new_params->sample = false;
        new_params->version = false;
        new_params->list_users = false;
        new_params->list_entities = false;
        new_params->list_nomaccts = false;
        new_params->list_jes = false;
    } else {
        gl_log_msg("Couldn't allocate memory for parameters.");
    }

    return new_params;
}

void params_free(struct params *params) {
    if (params) {
        ds_str_destroy(params->hostname);
        ds_str_destroy(params->database);
        ds_str_destroy(params->username);
        ds_str_destroy(params->password);
        free(params);
    }
}

bool get_configuration(struct params * params) {
    bool ret_val = true;

    int status = config_file_read("test_conf.conf");
    if (status == CONFIG_FILE_NO_FILE) {
        gl_log_msg("Couldn't open config file.");
        ret_val = false;
    } else if (status == CONFIG_FILE_MALFORMED_FILE) {
        gl_log_msg("Badly formed config file.");
        ret_val = false;
    }
    else {
        params->hostname = get_param_from_config("hostname");
        params->database = get_param_from_config("database");
        params->username = get_param_from_config("username");

        if (!params->hostname ||
            !params->database || !params->username) {
            ret_val = false;
        }

        config_file_free();
    }

    return ret_val;
}

bool get_cmdline_options(int argc, char **argv, struct params *params) {
    enum opts {
        CMDLINE_HELP = 1,
        CMDLINE_VERSION,
        CMDLINE_CREATE,
        CMDLINE_DELETE,
        CMDLINE_SAMPLE,
        CMDLINE_LISTUSERS,
        CMDLINE_LISTENTITIES,
        CMDLINE_LISTNOMACCTS,
        CMDLINE_LISTJES,
    };

    static struct option long_options[] = {
        {"help", no_argument, NULL, CMDLINE_HELP},
        {"version", no_argument, NULL, CMDLINE_VERSION},
        {"create", no_argument, NULL, CMDLINE_CREATE},
        {"delete", no_argument, NULL, CMDLINE_DELETE},
        {"loadsample", no_argument, NULL, CMDLINE_SAMPLE},
        {"listusers", no_argument, NULL, CMDLINE_LISTUSERS},
        {"listentities", no_argument, NULL, CMDLINE_LISTENTITIES},
        {"listnomaccts", no_argument, NULL, CMDLINE_LISTNOMACCTS},
        {"listjes", no_argument, NULL, CMDLINE_LISTJES},
        {NULL, 0, NULL, 0}
    };

    bool ret_val = true;
    int opt;

    while ((opt = getopt_long(argc, argv, "hvcdsunj",
                              long_options, NULL)) != -1) {
        switch ( opt ) {
            case 'h':
            case CMDLINE_HELP:
                params->help = true;
                break;

            case 'v':
            case CMDLINE_VERSION:
                params->version = true;
                break;

            case 'c':
            case CMDLINE_CREATE:
                params->create = true;
                break;

            case 'd':
            case CMDLINE_DELETE:
                params->delete_data = true;
                break;

            case 's':
            case CMDLINE_SAMPLE:
                params->sample = true;
                break;

            case 'u':
            case CMDLINE_LISTUSERS:
                params->list_users = true;
                break;

            case 'e':
            case CMDLINE_LISTENTITIES:
                params->list_entities = true;
                break;

            case 'n':
            case CMDLINE_LISTNOMACCTS:
                params->list_nomaccts = true;
                break;

            case 'j':
            case CMDLINE_LISTJES:
                params->list_jes = true;
                break;

            default:
                ret_val = false;
        }
    }

    return ret_val;
}

static ds_str get_param_from_config(const char * key) {
    ds_str value;

    ds_str s_key = ds_str_create(key);
    if ( !(value = config_file_value(s_key)) ) {
        gl_log_msg("Name of %s not specified in configuration file.", key);
    }
    ds_str_destroy(s_key);

    return ds_str_dup(value);
}

