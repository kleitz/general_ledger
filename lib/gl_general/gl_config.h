/*!
 * \file            gl_config.h
 * \brief           Interface to configuration functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_GL_CONFIG_H
#define PG_GENERAL_LEDGER_GL_CONFIG_H

#include "datastruct/data_structures.h"

/*!  Structure to hold database login parameters  */
struct params {
    ds_str hostname;        /*!<  Database hostname                 */
    ds_str database;        /*!<  Database name                     */
    ds_str username;        /*!<  Username for database access      */
    ds_str password;        /*!<  Password for database access      */
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
 * \param conf_file The filename of the configuration file.
 * \returns         `true` on success, `false` otherwise.
 */
bool get_configuration(struct params * params, const char * conf_file);

#endif      /*  PG_GENERAL_LEDGER_GL_CONFIG_H  */

