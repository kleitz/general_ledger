/*!
 * \file            config_file_read.c
 * \brief           Implementation of configuration file reading functionality.
 * \details         This module reads configuration files in the format
 * "key = value" and makes those values available. Leading and trailing
 * whitespace is removed for both the key and the value. Blank lines and
 * lines starting with a '#' are ignored in the configuration file.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gl_general/gl_general.h"
#include "datastruct/data_structures.h"
#include "config_file_read.h"

/*!  Maximum size of buffers  */
#define MAX_BUFFER_SIZE 1024

/*!  Size to use for the hash map to contain the key-value pairs  */
#define CONFIG_MAP_SIZE 100

/*!  File scope variable for the hash map  */
static ds_map_str config_map = NULL;

bool config_init(void) {
    config_map = ds_map_str_init(CONFIG_MAP_SIZE);
    return config_map ? true : false;
}

int config_file_read(const char * filename) {
    FILE * config_file = fopen(filename, "r");
    if ( !config_file ) {
        gl_log_msg("Couldn't open log file '%s'.", filename);
        return CONFIG_FILE_NO_FILE;
    }

    int retval = CONFIG_FILE_OK;

    ds_str buffer = ds_str_create("");
    while ( ds_str_getline(buffer, MAX_BUFFER_SIZE, config_file) ) {
        if ( ds_str_is_empty(buffer) ||
             ds_str_char_at_index(buffer, 0) == '#' ) {
            continue;
        }

        ds_str key, value;
        ds_str_split(buffer, &key, &value, '=');

        if ( !key || !value ) {
            retval = CONFIG_FILE_MALFORMED_FILE;
            break;
        }

        ds_str_trim(key);
        ds_str_trim(value);
        ds_map_str_insert(config_map, key, value);

        ds_str_destroy(key);
        ds_str_destroy(value);
    }

    ds_str_destroy(buffer);
    fclose(config_file);
    return retval;
}

ds_str config_value_get(ds_str key) {
    return config_map ? ds_map_str_get_value(config_map, key) : NULL;
}

ds_str config_value_get_cstr(const char * key) {
    if ( !config_map ) {
        return NULL;
    }

    ds_str skey = ds_str_create(key);
    if ( !skey ) {
        return NULL;
    }

    ds_str value = ds_map_str_get_value(config_map, skey);
    ds_str_destroy(skey);

    return value;
}

void config_value_set(ds_str key, ds_str value) {
    ds_map_str_insert(config_map, key, value);
}

void config_free(void) {
    if ( config_map ) {
        ds_map_str_destroy(config_map);
        config_map = NULL;
    }
}

