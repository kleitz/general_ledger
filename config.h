/*!
 * \file            config.h
 * \brief           Interface to program configuration functionality.
 * \details         Gets program configuration options from the command line
 * and/or a configuration file.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_CONFIG_H
#define PG_GENERAL_LEDGER_CONFIG_H

#include <stdbool.h>
#include "datastruct/ds_str.h"
#include "gl_general/gl_general.h"

/*!
 * \brief           Gets parameters from the command line.
 * \param argc      `argc` as passed to `main()`.
 * \param argv      `argv` as passed to `main()`.
 * \param params    A pointer to a parameters structure to populate.
 * \returns         `false` if an unrecognized command line option was
 * specified, `true` otherwise.
 */
bool get_cmdline_options(int argc, char ** argv, struct params * params);

#endif      /*  PG_GENERAL_LEDGER_CONFIG_H  */

