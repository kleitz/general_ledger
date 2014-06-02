#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "config.h"
#include "config_file_read/config_file_read.h"
#include "gl_general/gl_general.h"

static char *get_param_from_config(char *key);

struct params *params_init(void) {
    struct params *new_params = malloc(sizeof *new_params);
    if (new_params) {
        new_params->hostname = NULL;
        new_params->database = NULL;
        new_params->username = NULL;
        new_params->password = NULL;
        new_params->help = false;
        new_params->create = false;
    } else {
        gl_log_msg("Couldn't allocate memory for parameters.");
    }

    return new_params;
}

void params_free(struct params *params) {
    if (params) {
        free(params->hostname);
        free(params->database);
        free(params->username);
        free(params->password);
        free(params);
    }
}

static char *get_param_from_config(char *key) {
    const char *value;
    char *new_param = NULL;

    if ((value = config_file_value(key))) {
        new_param = strdup(value);
        if (!new_param) {
            gl_log_msg("Couldn't allocate memory for %s name.", key);
        } else {
            gl_log_msg("Name of %s from config file: %s", key, new_param);
        }
    } else {
        gl_log_msg("Name of %s not specified in configuration file.", key);
    }

    return new_param;
}

int get_configuration(struct params * params) {
    int ret_val = 0;

    int status = config_file_read("test_conf.conf");
    if (status == CONFIG_FILE_NO_FILE) {
        gl_log_msg("Couldn't open config file.");
        ret_val = -1;
    } else if (status == CONFIG_FILE_MALFORMED_FILE) {
        gl_log_msg("Badly formed config file.");
        ret_val = -1;
    }
    else {
        params->hostname = get_param_from_config("hostname");
        params->database = get_param_from_config("database");
        params->username = get_param_from_config("username");

        if (!params->hostname ||
            !params->database || !params->username) {
            ret_val = -1;
        }

        config_file_free();
    }

    return ret_val;
}

int get_cmdline_options(int argc, char **argv, struct params *params) {
    int opt;
    int ret_val = 0;

    enum opts {
        CMDLINE_HELP = 1,
        CMDLINE_VERSION,
        CMDLINE_CREATE,
        CMDLINE_LISTUSERS
    };

    static struct option long_options[] = {
        {"help", no_argument, NULL, CMDLINE_HELP},
        {"version", no_argument, NULL, CMDLINE_VERSION},
        {"create", no_argument, NULL, CMDLINE_CREATE},
        {"listusers", no_argument, NULL, CMDLINE_LISTUSERS}
    };

    while ((opt = getopt_long(argc, argv, "hv", long_options, NULL)) != -1) {
        switch ( opt ) {
            case 'h':
            case CMDLINE_HELP:
                params->help = true;
                break;

            case 'v':
            case CMDLINE_VERSION:
                params->version = true;
                break;

            case CMDLINE_CREATE:
                params->create = true;
                break;

            case CMDLINE_LISTUSERS:
                params->list_users = true;
                break;

            default:
                ret_val = -1;
        }

    }

    return ret_val;
}

