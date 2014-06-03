/*!
 * \file            ds_map_str.h
 * \brief           Interface to string-string hash map data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_MAP_STR_H
#define PG_GENERAL_LEDGER_DS_MAP_STR_H

#include "ds_str.h"

/*!  Opaque data type for hash map  */
typedef struct ds_map_str * ds_map_str;

/*!
 * \brief           Initializes a hash map.
 * \param hash_size The number of possible hash values.
 * \returns         A reference to the newly-created hash map.
 */
ds_map_str ds_map_str_init(const size_t hash_size);

/*!
 * \brief           Destroys a hash map.
 * \param map       A reference to the map to destroy.
 */
void ds_map_str_destroy(ds_map_str map);

/*!
 * \brief           Retrieves a value associated with a key in the map.
 * \param map       A reference to the hash map.
 * \param key       The key.
 * \returns         A pointer to the value associated with the key, or
 * `NULL` if the key is not in the map. The caller should not modify the
 * string to which this pointer points.
 */
ds_str ds_map_str_get_value(ds_map_str map, ds_str key);

/*!
 * \brief           Inserts a key-value pair into a map.
 * \details         The key and value are copied, so the caller may modify
 * or `free()` them after calling this function.
 * \param map       A reference to the hash map.
 * \param key       The key.
 * \param value     The value.
 */
void ds_map_str_insert(ds_map_str map, ds_str key, ds_str value);

#endif      /*  PG_GENERAL_LEDGER_DS_MAP_STR_H  */

