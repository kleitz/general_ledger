/*!
 * \file            gl_db_config.c
 * \brief           Implementation of GL DB program configuration functionality.
 * \details         Gets program configuration options from the command line
 * and/or a configuration file.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  UNIX feature test macro  */
#define _XOPEN_SOURCE 500

#include <assert.h>
#include <getopt.h>
#include "gl_db_config.h"
#include "file_ops/file_ops.h"
#include "datastruct/data_structures.h"
#include "gl_general/gl_general.h"

bool get_cmdline_options(int argc, char **argv, struct params *params) {
    enum opts {
        CMDLINE_HELP = 1,
        CMDLINE_VERSION,
        CMDLINE_INIT,
        CMDLINE_CREATE,
        CMDLINE_DELETE,
        CMDLINE_SAMPLE,
    };

    /*  Temporarily disable warning  */
    (void)params;

    static struct option long_options[] = {
        {"help", no_argument, NULL, CMDLINE_HELP},
        {"version", no_argument, NULL, CMDLINE_VERSION},
        {"init", no_argument, NULL, CMDLINE_INIT},
        {"create", no_argument, NULL, CMDLINE_CREATE},
        {"delete", no_argument, NULL, CMDLINE_DELETE},
        {"loadsample", no_argument, NULL, CMDLINE_SAMPLE},
        {NULL, 0, NULL, 0}
    };

    bool ret_val = true;
    int copt;
    ds_str key = ds_str_create("");
    ds_str value = ds_str_create("");

    while ((copt = getopt_long(argc, argv, "hvicds",
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

            case 'i':
            case CMDLINE_INIT:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "init"));
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

            default:
                ret_val = false;
        }
    }

    ds_str_destroy(key);
    ds_str_destroy(value);

    return ret_val;
}

