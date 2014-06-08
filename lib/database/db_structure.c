/*!
 * \file            db_structure.c
 * \brief           Implementation of database structure functionality.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "db_internal.h"

bool db_create_database_structure(void) {
    static bool (*createfunc[])(void) = {
        db_create_users_table,
        db_create_entities_table,
        db_create_jesrcs_table,
        db_create_nomaccts_table,
        db_create_jes_table,
        db_create_jelines_table,
        NULL
    };

    bool status = true;
    for ( size_t i = 0; createfunc[i]; ++i ) {
        status = createfunc[i]();
    }

    return status;
}

bool db_delete_database_structure(void) {
    static bool (*dropfunc[])(void) = {
        db_drop_jelines_table,
        db_drop_jes_table,
        db_drop_nomaccts_table,
        db_drop_jesrcs_table,
        db_drop_entities_table,
        db_drop_users_table,
        NULL
    };

    bool status = true;
    for ( size_t i = 0; dropfunc[i]; ++i ) {
        status = dropfunc[i]();
    }

    return status;
}

