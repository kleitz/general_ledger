/*!
 * \file            config_file_read.h
 * \brief           Interface to configuration file reading functionality.
 * \details         This module reads configuration files in the format
 * "key = value" and makes those values available. Leading and trailing
 * whitespace is removed for both the key and the value. Blank lines and
 * lines starting with a '#' are ignored in the configuration file.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_CONFIG_FILE_READ_H
#define PG_GENERAL_LEDGER_CONFIG_FILE_READ_H

#include "datastruct/ds_str.h"

/*!  Return status for success  */
#define CONFIG_FILE_OK 0

/*!  Return status when unable to open file for reading  */
#define CONFIG_FILE_NO_FILE 1

/*!  Return status when configuration file is improperly formed  */
#define CONFIG_FILE_MALFORMED_FILE 2

/*!
 * \brief           Reads a configuration file and stores the key-value pairs.
 * \param filename  The name of the configuration file.
 * \returns         CONFIG_FILE_OK on success, CONFIG_FILE_NO_FILE if the
 * specified file could not be opened for reading, CONFIG_FILE_MALFORMED_FILE
 * if the configuration file was improperly formed.
 */
int config_file_read(const char * filename);

/*!
 * \brief           Frees the resources used by this module.
 * \details         The user should make copies of any required keys or values
 * prior to calling this function. This function need not be called if
 * `config_file_read()` returned an error.
 */
void config_file_free(void);

/*!
 * \brief           Returns the value associated with a key.
 * \param key       The specified key.
 * \returns         A pointer to the associated value, or `NULL` if the key
 * was not present in the configuration file. The caller should not modify
 * the string to which the pointer points.
 */
ds_str config_file_value(ds_str key);

#endif      /*  PG_GENERAL_LEDGER_CONFIG_FILE_READ_H  */

