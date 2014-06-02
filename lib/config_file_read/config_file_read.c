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
#include "gl_general/gl_general.h"
#include "stringhelp/string_functions.h"
#include "datastruct/ds_map.h"
#include "config_file_read.h"

/*!  Maximum size of buffers  */
#define MAX_BUFFER_SIZE 1024

/*!  Size to use for the hash map to contain the key-value pairs  */
#define CONFIG_MAP_SIZE 100

/*!  File scope variable for the hash map  */
static ds_map config_map = NULL;

int config_file_read(const char * filename) {
    FILE * config_file = fopen(filename, "r");
    if ( !config_file ) {
        gl_log_msg("Couldn't open log file '%s'.", filename);
        return CONFIG_FILE_NO_FILE;
    }

    int retval = CONFIG_FILE_OK;
    config_map = ds_map_init(CONFIG_MAP_SIZE);

    char buffer[MAX_BUFFER_SIZE];    
    while ( fgets(buffer, sizeof buffer, config_file) ) {
        char key[MAX_BUFFER_SIZE] = {0};
        char value[MAX_BUFFER_SIZE] = {0};

        trim(buffer);
        if ( buffer[0] == '#' || buffer[0] == '\0' ) {
            continue;
        }

        size_t buf_idx = 0, key_idx = 0;
        while ( buffer[buf_idx] && buffer[buf_idx] != '=' ) {
            key[key_idx++] = buffer[buf_idx++];
        }
        if ( buffer[buf_idx++] == '=' ) {
            size_t val_idx = 0;
            while ( buffer[buf_idx] ) {
                value[val_idx++] = buffer[buf_idx++];
            }
        }

        if ( value[0] == '\0' ) {
            retval = CONFIG_FILE_MALFORMED_FILE;
            config_file_free();
            break;
        }

        trim(key);
        trim(value);
        ds_map_insert(config_map, key, value);
    }

    fclose(config_file);
    return retval;
}

const char * config_file_value(const char * key) {
    if ( config_map ) {
        return ds_map_get_value(config_map, key);
    }
    else {
        return NULL;
    }
}

void config_file_free(void) {
    if ( config_map ) {
        ds_map_destroy(config_map);
        config_map = NULL;
    }
}

void config_file_print_all(void) {
    if ( config_map ) {
        ds_map_print_all(config_map, stdout);
    }
}

