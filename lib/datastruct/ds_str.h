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

/*!
 * \brief           Calculates a hash of a string.
 * \details         Uses Dan Bernstein's djb2 algorithm.
 * \param str       The string.
 * \returns         The hash value
 */
unsigned long ds_str_hash(struct ds_str * str);

/*!
 * \brief           Compares two strings.
 * \param s1        The first string.
 * \param s2        The second string.
 * \returns         Less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, equal to, or greater than s2.
 */
int ds_str_compare(ds_str s1, ds_str s2);

/*!
 * \brief           Returns a left substring.
 * \param str       The string.
 * \param numchars  The number of left characters to return. If this is
 * greater than the length of the string, the whole string is returned.
 * \returns         A new string representing the substring.
 */
ds_str ds_str_substr_left(ds_str str, const size_t numchars);

/*!
 * \brief           Returns a right substring.
 * \param str       The string.
 * \param numchars  The number of right characters to return. If this is
 * greater than the length of the string, the whole string is returned.
 * \returns         A new string representing the substring.
 */
ds_str ds_str_substr_right(ds_str str, const size_t numchars);

/*!
 * \brief           Splits a string
 * \param src       The string to split.
 * \param left      Pointer to left substring (modified)
 * \param right     Pointer to right substring (modified)
 * \param sc        Split character.
 */
void ds_str_split(ds_str src, ds_str * left, ds_str * right, const char sc);

/*!
 * \brief           Trims leading whitespace in-place.
 * \param str       The string.
 */
void ds_str_trim_leading(ds_str str);

/*!
 * \brief           Trims trailing whitespace in-place.
 * \param str       The string.
 */
void ds_str_trim_trailing(ds_str str);

/*!
 * \brief           Trims leading and trailing whitespace in-place.
 * \param str       The string.
 */
void ds_str_trim(ds_str str);

/*!
 * \brief           Returns the character at a specified index.
 * \param str       The string.
 * \param index     The specified index.
 * \returns         The character at the specified index.
 */
char ds_str_char_at_index(ds_str str, const size_t index);

/*!
 * \brief           Checks if a string is empty.
 * \param str       The string.
 * \returns         `true` is the string is empty, `false` otherwise.
 */
bool ds_str_is_empty(ds_str str);

#endif      /*  PG_GENERAL_LEDGER_DS_STR_H  */

