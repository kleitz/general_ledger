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
#include <assert.h>
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
        CMDLINE_LISTJELINES,
        CMDLINE_LISTJESRCS,
        CMDLINE_CURRENTTB,
        CMDLINE_ENTITY,
    };

    /*  Temporarily disable warning  */
    (void)params;

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
        {"listjelines", no_argument, NULL, CMDLINE_LISTJELINES},
        {"listjesrcs", no_argument, NULL, CMDLINE_LISTJESRCS},
        {"currenttb", no_argument, NULL, CMDLINE_CURRENTTB},
        {"entity", required_argument, NULL, CMDLINE_ENTITY},
        {NULL, 0, NULL, 0}
    };

    bool ret_val = true;
    int copt;
    ds_str key = ds_str_create("");
    ds_str value = ds_str_create("");

    while ((copt = getopt_long(argc, argv, "hvcdsunj",
                              long_options, NULL)) != -1) {
        switch ( copt ) {
            case 'h':
            case CMDLINE_HELP:
                assert(ds_str_assign_cstr(key, "help"));
                config_value_set(key, value);
                break;

            case 'v':
            case CMDLINE_VERSION:
                assert(ds_str_assign_cstr(key, "version"));
                config_value_set(key, value);
                break;

            case 'c':
            case CMDLINE_CREATE:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "create"));
                config_value_set(key, value);
                break;

            case 'd':
            case CMDLINE_DELETE:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "delete"));
                config_value_set(key, value);
                break;

            case 's':
            case CMDLINE_SAMPLE:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "loadsample"));
                config_value_set(key, value);
                break;

            case 'u':
            case CMDLINE_LISTUSERS:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "listusers"));
                config_value_set(key, value);
                break;

            case 'e':
            case CMDLINE_LISTENTITIES:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "listentities"));
                config_value_set(key, value);
                break;

            case 'n':
            case CMDLINE_LISTNOMACCTS:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "listnomaccts"));
                config_value_set(key, value);
                break;

            case 'j':
            case CMDLINE_LISTJES:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "listjes"));
                config_value_set(key, value);
                break;

            case CMDLINE_LISTJELINES:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "listjelines"));
                config_value_set(key, value);
                break;

            case CMDLINE_LISTJESRCS:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "listjesrcs"));
                config_value_set(key, value);
                break;

            case CMDLINE_CURRENTTB:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "currenttb"));
                config_value_set(key, value);
                break;

            case CMDLINE_ENTITY:
                assert(ds_str_assign_cstr(key, "entity"));
                assert(ds_str_assign_cstr(value, optarg));
                if ( ds_str_intval(value, 10, NULL) ) {
                    config_value_set(key, value);
                }
                else {
                    gl_log_msg("Invalid entity number: %s", ds_str_cstr(value));
                    ret_val = false;
                }
                break;

            default:
                ret_val = false;
        }
    }

    ds_str_destroy(key);
    ds_str_destroy(value);

    return ret_val;
}

static ds_str get_param_from_config(const char * key) {
    ds_str value;

    ds_str s_key = ds_str_create(key);
    if ( !(value = config_value_get(s_key)) ) {
        gl_log_msg("Name of %s not specified in configuration file.", key);
    }
    ds_str_destroy(s_key);

    return ds_str_dup(value);
}

