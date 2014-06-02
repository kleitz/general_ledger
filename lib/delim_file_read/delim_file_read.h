/*!
 * \file            delim_file_read.h
 * \brief           Interface to delimited file reading functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DELIM_FILE_READ_H
#define PG_GENERAL_LEDGER_DELIM_FILE_READ_H

#include "datastruct/ds_result_set.h"

/*!  Return status for success  */
#define DELIM_FILE_OK 0

/*!  Return status when unable to open file for reading  */
#define DELIM_FILE_NO_FILE 1

/*!  Return status when delimited file is improperly formed  */
#define DELIM_FILE_MALFORMED_FILE 2

/*!
 * \brief           Reads a delimited file and stores the key-value pairs.
 * \param filename  The name of the delimited file.
 * \returns         DELIM_FILE_OK on success, DELIM_FILE_NO_FILE if the
 * specified file could not be opened for reading, DELIM_FILE_MALFORMED_FILE
 * if the delimited file was improperly formed.
 */
ds_result_set delim_file_read(const char * filename);

/*!
 * \brief           Frees the resources used by this module.
 * \details         The user should make copies of any required keys or values
 * prior to calling this function. This function need not be called if
 * `delim_file_read()` returned an error.
 */
void delim_file_free(void);

/*!
 * \brief           Returns the value associated with a key.
 * \param key       The specified key.
 * \returns         A pointer to the associated value, or `NULL` if the key
 * was not present in the delimited file. The caller should not modify
 * the string to which the pointer points.
 */
const char * delim_file_value(const char * key);

/*!
 * \brief           Prints all the key-value pairs to stdout.
 */
void delim_file_print_all();

#endif      /*  PG_GENERAL_LEDGER_DELIM_FILE_READ_H  */

