/*!
 * \file            ds_kvpair.h
 * \brief           Interface to string key-value pair data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_STR_KVPAIR_H
#define PG_GENERAL_LEDGER_DS_STR_KVPAIR_H

#include "data_structures.h"

/*!  Opaque data type for kvpair  */
typedef struct ds_kvpair * ds_kvpair;

/*!
 * \brief           Makes a new key-value pair node.
 * \param key       The key.
 * \param value     The value.
 * \returns         A pointer to the newly-created node.
 */
ds_kvpair ds_kvpair_create(ds_str key, ds_str value);

/*!
 * \brief           Frees a key-value pair.
 * \param pair      The key-value pair to free.
 */
void ds_kvpair_destroy(ds_kvpair pair);

/*!
 * \brief           Destructor function.
 * \details         This function is useful for passing a destructor function
 * to a data structure which expects a prototype conforming to `free()`.
 * \param pair      A pointer to the node to free.
 */
void ds_kvpair_destructor(void * pair);

/*!
 * \brief           Returns the key in a key-value pair.
 * \param pair      The key-value pair.
 * \returns         The key. The caller should not destroy this string.
 */
ds_str ds_kvpair_get_key(ds_kvpair pair);

/*!
 * \brief           Returns the value in a key-value pair.
 * \param pair      The key-value pair.
 * \returns         The value. The caller should not destroy this string.
 */
ds_str ds_kvpair_get_value(ds_kvpair pair);

#endif      /*  PG_GENERAL_LEDGER_DS_MAP_STR_KVPAIR_H  */

