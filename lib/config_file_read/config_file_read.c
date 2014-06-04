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

int config_file_read(const char * filename) {
    FILE * config_file = fopen(filename, "r");
    if ( !config_file ) {
        gl_log_msg("Couldn't open log file '%s'.", filename);
        return CONFIG_FILE_NO_FILE;
    }

    int retval = CONFIG_FILE_OK;
    config_map = ds_map_str_init(CONFIG_MAP_SIZE);

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
            config_file_free();
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

ds_str config_file_value(ds_str key) {
    return config_map ? ds_map_str_get_value(config_map, key) : NULL;
}

void config_file_free(void) {
    if ( config_map ) {
        ds_map_str_destroy(config_map);
        config_map = NULL;
    }
}

