/*!
 * \file            delim_file_read.h
 * \brief           Interface to delimited file reading functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_FILE_OPS_DELIM_FILE_READ_H
#define PG_GENERAL_LEDGER_FILE_OPS_DELIM_FILE_READ_H

#include "datastruct/data_structures.h"

/*!
 * \brief           Constructs a ds_recordset from a delimited file.
 * \param filename  The name of the delimited file.
 * \param delim     The delimiting character.
 * \returns         The ds_recordset, or `NULL` on failure.
 */
ds_recordset delim_file_read(const char * filename, const char delim);

#endif      /*  PG_GENERAL_LEDGER_FILE_OPS_DELIM_FILE_READ_H  */

