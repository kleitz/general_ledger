#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "config_file_read/config_file_read.h"
#include "gl_general/gl_general.h"

static struct params * params_init(void);
static char * get_param_from_config(char * key);

static struct params * params_init(void) {
    struct params * new_params = malloc(sizeof *new_params);
    if ( new_params ) {
        new_params->hostname = NULL;
        new_params->database = NULL;
        new_params->username = NULL;
        new_params->password = NULL;
    }
    else {
        gl_log_msg("Couldn't allocate memory for parameters.");
    }

    return new_params;
}

void params_free(struct params * params) {
    if ( params ) {
        free(params->hostname);
        free(params->database);
        free(params->username);
        free(params->password);
        free(params);
    }
}

static char * get_param_from_config(char * key) {
    const char *value;
    char *new_param = NULL;

    if ( (value = config_file_value(key)) ) {
        new_param = strdup(value);
        if ( !new_param ) {
            gl_log_msg("Couldn't allocate memory for %s name.", key);
        }
        else {
            gl_log_msg("Name of %s from config file: %s", key, new_param);
        }
    }
    else {
        gl_log_msg("Name of %s not specified in configuration file.", key);
    }

    return new_param;
}

struct params * get_configuration(char * passwd) {
    int status = config_file_read("test_conf.conf");
    if ( status == CONFIG_FILE_NO_FILE ) {
        gl_log_msg("Couldn't open config file.");
        return NULL;
    }
    else if ( status == CONFIG_FILE_MALFORMED_FILE ) {
        gl_log_msg("Badly formed config file.");
        return NULL;
    }

    struct params * new_params = params_init();
    if ( new_params ) {
        new_params->hostname = get_param_from_config("hostname");
        new_params->database = get_param_from_config("database");
        new_params->username = get_param_from_config("username");

        if ( !new_params->hostname ||
             !new_params->database ||
             !new_params->username) {
            params_free(new_params);
            new_params = NULL;
        }
        else {
            new_params->password = passwd;
        }
    }

    config_file_free();
    return new_params;
}

