/*!
 * \file            gl_config.c
 * \brief           Implementation of configuration functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdlib.h>

#include "gl_general.h"
#include "file_ops/file_ops.h"

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

bool get_configuration(struct params * params, const char * conf_file) {
    bool ret_val = true;

    int status = config_file_read(conf_file);
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

static ds_str get_param_from_config(const char * key) {
    ds_str value;

    ds_str s_key = ds_str_create(key);
    if ( !(value = config_value_get(s_key)) ) {
        gl_log_msg("Name of %s not specified in configuration file.", key);
    }
    ds_str_destroy(s_key);

    return ds_str_dup(value);
}

