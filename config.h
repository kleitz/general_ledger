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

/*!  Structure to hold program parameters  */
struct params {
    ds_str hostname;        /*!<  Database hostname                 */
    ds_str database;        /*!<  Database name                     */
    ds_str username;        /*!<  Username for database access      */
    ds_str password;        /*!<  Password for database access      */
    bool help;              /*!<  Help option set                   */
    bool version;           /*!<  Version option set                */
    bool create;            /*!<  Create structure option set       */
    bool delete_data;       /*!<  Delete structure option set       */
    bool sample;            /*!<  Load sample data option set       */
    bool list_users;        /*!<  List users option set             */
    bool list_entities;     /*!<  List entities option set          */
    bool list_nomaccts;     /*!<  List nominal accounts option set  */
    bool list_jes;          /*!<  List journal entries option set   */
    bool current_tb;        /*!<  Current trial balance option set  */
};

/*!
 * \brief           Initializes a parameters structure.
 * \returns         An initialized parameters structure.
 */
struct params *params_init(void);

/*!
 * \brief           Frees a parameter structure.
 * \param params    A pointer to the structure to free.
 */
void params_free(struct params * params);

/*!
 * \brief           Gets parameters from a configuration file.
 * \param params    A pointer to a parameters structure to populate.
 * \returns         `true` on success, `false` otherwise.
 */
bool get_configuration(struct params * params);

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

