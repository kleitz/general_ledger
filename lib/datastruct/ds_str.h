/*!
 * \file            ds_str.h
 * \brief           Interface to string data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_STR_H
#define PG_GENERAL_LEDGER_DS_STR_H

/*!  Opaque data type for string  */
typedef struct ds_str * ds_str;

/*!
 * \brief           Creates a new string from a C-style string.
 * \param init_str  The C-style string.
 * \returns         The new string, or `NULL` on failure.
 */
ds_str ds_str_create(const char * init_str);

/*!
 * \brief           Creates a new string from another string.
 * \param src       The other string.
 * \returns         The new string, or `NULL` on failure.
 */
ds_str ds_str_dup(ds_str src);

/*!
 * \brief           Creates a string with `sprintf()`-type format.
 * \param format    The format string.
 * \param ...       The subsequent arguments as specified by the format string.
 * \returns         The new string, or `NULL` on failure.
 */
ds_str ds_str_create_sprintf(const char * format, ...);

/*!
 * \brief               Creates a string using allocated memory.
 * \details             The normal construction functions duplicate the
 * string used to create it. In cases where allocated memory is already
 * available (e.g. in `ds_str_create_sprintf()`) this function allows
 * that memory to be directly assigned to the string, avoiding an
 * unnecessary duplication.
 * \param str           The allocated memory. IMPORTANT: If the construction
 * of the string fails, this memory will be `free()`d.
 * \param init_str_size The size of the allocated memory. IMPORTANT: The
 * string's length is assumed to be one less than this quantity, and a
 * call to `strlen()` is NOT performed.
 * \returns             The new string, or `NULL` on failure.
 */
ds_str ds_str_create_direct(char * init_str, const size_t init_str_size);

/*!
 * \brief           Destroys a string and releases allocated resources.
 * \param str       The string to destroy..
 */
void ds_str_destroy(ds_str str);

/*!
 * \brief           Destroys a string and releases allocated resources.
 * \details         This function calls `ds_str_destroy()`, and can be passed
 * to a data structure expecting a destructor function with the signature
 * void (*)(void *).
 * \param str       The string to destroy.
 */
void ds_str_destructor(void * str);

/*!
 * \brief           Returns a C-style string containing the string's contents.
 * \param str       The string.
 * \returns         The C-style string containing the string's contents. The
 * caller should not directly modify this string.
 */
const char * ds_str_cstr(ds_str str);

/*!
 * \brief           Returns the length of a string.
 * \param str       The string.
 * \returns         The length of the string.
 */
size_t ds_str_length(ds_str str);

/*!
 * \brief           Concatenates two strings.
 * \param dst       The destination string.
 * \param src       The source strings.
 * \returns         The destination string, or `NULL` on failure.
 */
ds_str ds_str_concat(ds_str dst, ds_str src);

/*!
 * \brief           Concatenates a C-style string to a string.
 * \param dst       The destination string.
 * \param src       The source strings.
 * \returns         The destination string, or `NULL` on failure.
 */
ds_str ds_str_concat_cstr(struct ds_str * dst, const char * src);

/*!
 * \brief           Truncates a string.
 * \param str       The string.
 * \param length    The new length to which to truncate.
 * \returns         The original string, or `NULL` on failure.
 */
ds_str ds_str_trunc(ds_str str, const size_t length);

#endif      /*  PG_GENERAL_LEDGER_DS_STR_H  */

