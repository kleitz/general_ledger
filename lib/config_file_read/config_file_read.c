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

    char buffer[MAX_BUFFER_SIZE];    
    while ( fgets(buffer, sizeof buffer, config_file) ) {
        ds_str input = ds_str_create(buffer);
        ds_str_trim_leading(input);

        if ( ds_str_is_empty(input) ||
             ds_str_char_at_index(input, 0) == '#' ) {
            ds_str_destroy(input);
            continue;
        }

        ds_str key, value;
        ds_str_split(input, &key, &value, '=');

        if ( !key || !value ) {
            retval = CONFIG_FILE_MALFORMED_FILE;
            config_file_free();
            ds_str_destroy(input);
            break;
        }

        ds_str_trim(key);
        ds_str_trim(value);
        ds_map_str_insert(config_map, key, value);

        ds_str_destroy(key);
        ds_str_destroy(value);
        ds_str_destroy(input);
    }

    fclose(config_file);
    return retval;
}

ds_str config_file_value(ds_str key) {
    if ( config_map ) {
        return ds_map_str_get_value(config_map, key);
    }
    else {
        return NULL;
    }
}

void config_file_free(void) {
    if ( config_map ) {
        ds_map_str_destroy(config_map);
        config_map = NULL;
    }
}

