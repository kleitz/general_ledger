/*!
 * \file            gl_reports_config.c
 * \brief           Implementation of GL reports program configuration
 * functionality.
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
#include "gl_reports_config.h"
#include "file_ops/file_ops.h"
#include "datastruct/data_structures.h"
#include "gl_general/gl_general.h"

bool get_cmdline_options(int argc, char **argv, struct params *params) {
    enum opts {
        CMDLINE_HELP = 1,
        CMDLINE_VERSION,
        CMDLINE_LISTUSERS,
        CMDLINE_LISTENTITIES,
        CMDLINE_LISTNOMACCTS,
        CMDLINE_LISTJES,
        CMDLINE_LISTJELINES,
        CMDLINE_LISTJESRCS,
        CMDLINE_SHOWSTANDINGDATA,
        CMDLINE_CURRENTTB,
        CMDLINE_ENTITY,
    };

    /*  Temporarily disable warning  */
    (void)params;

    static struct option long_options[] = {
        {"help", no_argument, NULL, CMDLINE_HELP},
        {"version", no_argument, NULL, CMDLINE_VERSION},
        {"listusers", no_argument, NULL, CMDLINE_LISTUSERS},
        {"listentities", no_argument, NULL, CMDLINE_LISTENTITIES},
        {"listnomaccts", no_argument, NULL, CMDLINE_LISTNOMACCTS},
        {"listjes", no_argument, NULL, CMDLINE_LISTJES},
        {"listjelines", no_argument, NULL, CMDLINE_LISTJELINES},
        {"listjesrcs", no_argument, NULL, CMDLINE_LISTJESRCS},
        {"standingdata", no_argument, NULL, CMDLINE_SHOWSTANDINGDATA},
        {"currenttb", no_argument, NULL, CMDLINE_CURRENTTB},
        {"entity", required_argument, NULL, CMDLINE_ENTITY},
        {NULL, 0, NULL, 0}
    };

    bool ret_val = true;
    int copt;
    ds_str key = ds_str_create("");
    ds_str value = ds_str_create("");

    while ((copt = getopt_long(argc, argv, "hvunje",
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

            case CMDLINE_SHOWSTANDINGDATA:
                assert(ds_str_assign_cstr(key, "login"));
                config_value_set(key, value);
                assert(ds_str_assign_cstr(key, "report"));
                assert(ds_str_assign_cstr(value, "standingdata"));
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

