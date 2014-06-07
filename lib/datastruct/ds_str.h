/*!
 * \file            ds_str.h
 * \brief           Interface to string data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_STR_H
#define PG_GENERAL_LEDGER_DS_STR_H

#include <stdio.h>
#include <stdbool.h>

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
 * \param init_str      The allocated memory. IMPORTANT: If the construction
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
 * \brief           Assigns a string to another.
 * \param dst       The destination string.
 * \param src       The source string.
 * \returns         `dst` on success, `NULL` on failure.
 */
ds_str ds_str_assign(ds_str dst, ds_str src);

/*!
 * \brief           Assigns a C-style string to a string.
 * \param dst       The destination string.
 * \param src       The source C-style string.
 * \returns         `dst` on success, `NULL` on failure.
 */
ds_str ds_str_assign_cstr(ds_str dst, const char * src);

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
 * \brief           Reduces a string's capacity to fit its length.
 * \param str       The string to size.
 * \returns         `str`, or `NULL` on failure.
 */ 
ds_str ds_str_size_to_fit(ds_str str);

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
ds_str ds_str_concat_cstr(ds_str dst, const char * src);

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
unsigned long ds_str_hash(ds_str str);

/*!
 * \brief           Compares two strings.
 * \param s1        The first string.
 * \param s2        The second string.
 * \returns         Less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, equal to, or greater than s2.
 */
int ds_str_compare(ds_str s1, ds_str s2);

/*!
 * \brief           Compares a string with a C-style string.
 * \param s1        The first string.
 * \param s2        The second, C-Style string.
 * \returns         Less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, equal to, or greater than s2.
 */
int ds_str_compare_cstr(ds_str s1, const char * s2);

/*!
 * \brief           Returns index of first occurence of a character.
 * \param str       The string.
 * \param ch        The character for which to search.
 * \param start     The index of the string at which to start looking. Set
 * this to non-zero to begin searching from a point other than the first
 * character of the string.
 * \returns         The index of the first occurence, or -1 if the character
 * was not found.
 */
int ds_str_strchr(ds_str str, const char ch, const int start);

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

/*!
 * \brief           Clears (empties) a string.
 * \param str       The string.
 */
void ds_str_clear(ds_str str);

/*!
 * \brief           Gets the integer value of a string.
 * \param str       The string.
 * \param base      The base of the integer. This has the same meaning as
 * the third argument to standard C `strtol()`.
 * \param value     A pointer to the integer in which to store the value.
 * Zero is stored if the string does not contain a valid integer value.
 * \returns         `true` on successful conversion, `false` if the string
 * does not contain a valid integer value.
 */
bool ds_str_intval(ds_str str, const int base, int * value);

/*!
 * \brief           Gets the double value of a string.
 * \param str       The string.
 * \param value     A pointer to the double in which to store the value.
 * Zero is stored if the string does not contain a valid double value.
 * \returns         `true` on successful conversion, `false` if the string
 * does not contain a valid double value.
 */
bool ds_str_doubleval(ds_str str, double * value);

/*!
 * \brief           Gets a line from a file and assigns it to a string.
 * \details         Any trailing newline character is stripped.
 * \param str       The string.
 * \param size      The maximum number of bytes to read, including the null.
 * \param fp        The file pointer from which to read.
 * \returns         `dst`
 */
ds_str ds_str_getline(ds_str str, const size_t size, FILE * fp);

/*!
 * \brief           Brackets a string with decoration strings.
 * \param str       The string to decorate.
 * \param left_dec  The string to add to the left of `str`.
 * \param right_dec The string to add to the right of `str`, or `NULL`
 * to add `left_dec` to both sides.
 * \returns         The decorated string.
 */
ds_str ds_str_decorate(ds_str str, ds_str left_dec, ds_str right_dec);

#endif      /*  PG_GENERAL_LEDGER_DS_STR_H  */

