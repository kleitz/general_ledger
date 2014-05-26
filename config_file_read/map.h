/*!
 * \file            map.h
 * \brief           Interface to hash map data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_MAP_H
#define PG_GENERAL_LEDGER_MAP_H

#include <stdio.h>

/*!  Opaque data type for hash map  */
typedef struct map * hash_map;

/*!
 * \brief           Initializes a hash map.
 * \param hash_size The number of possible hash values.
 * \returns         A reference to the newly-created hash map.
 */
hash_map map_init(const size_t hash_size);

/*!
 * \brief           Destroys a hash map.
 * \param map       A reference to the map to destroy.
 */
void map_destroy(hash_map map);

/*!
 * \brief           Retrieves a value associated with a key in the map.
 * \param map       A reference to the hash map.
 * \param key       The key.
 * \returns         A pointer to the value associated with the key, or
 * `NULL` if the key is not in the map. The caller should not modify the
 * string to which this pointer points.
 */
const char * map_get_value(hash_map map, const char * key);

/*!
 * \brief           Inserts a key-value pair into a map.
 * \details         The key and value are copied, so the caller may modify
 * or `free()` them after calling this function.
 * \param map       A reference to the hash map.
 * \param key       The key.
 * \param value     The value.
 */
void map_insert(hash_map map, const char * key, const char * value);

/*!
 * \brief           Prints all the key-value pairs in a map to stdout.
 * \param map       A reference to the map.
 * \param outfile   A FILE pointer to which to print the output.
 */
void map_print_all(hash_map map, FILE * outfile);

#endif      /*  PG_GENERAL_LEDGER_MAP_H  */

