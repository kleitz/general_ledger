/*!
 * \file            ds_str.c
 * \brief           Implementation of string data structure.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>

#include "data_structures.h"

/*!  Structure to contain string  */
struct ds_str {
    char * data;        /*!<  The data in C-style string format     */
    size_t length;      /*!<  The length of the string              */
    size_t capacity;    /*!<  The size of the `data` buffer         */
};

/*!
 * \brief           Directly assigns dynamically allocated data to a string.
 * \param dst       The string to which to assign.
 * \param src       The dynamically allocated C-style string to assign.
 * \param size      The size of the allocated memory.
 * \param length    The length of the C-style string.
 * \returns         `dst`.
 */
static ds_str ds_str_assign_cstr_direct(ds_str dst,
                                        char * src,
                                        const size_t size,
                                        const size_t length);

/*!
 * \brief           Assigns a C-style string to a string with length.
 * \details         Providing the length avoids a call to `strlen()`, which
 * is more efficient if the length is already known.
 * \param dst       The string to which to assign.
 * \param src       The C-style string to be assigned.
 * \param length    The length of `src`, excluding the terminating null.
 * \returns         `dst` on success, `NULL` on failure.
 */
static ds_str ds_str_assign_cstr_length(ds_str dst,
                                        const char * src,
                                        const size_t length);

/*!
 * \brief           Duplicates a C-style string.
 * \details         This can be used in place of POSIX's `strdup()`.
 * \param src       The string to duplicate.
 * \param length    A pointer to a `size_t` variable to contain the length
 * of the duplicated string. This is provided for efficiency purposes, as
 * the length of the string needs to be calculated to duplicate it, so
 * modifying this parameter may help to avoid a second unnecessary call to
 * `strlen()`. This argument is ignored if set to `NULL`.
 * \returns         A pointer to the duplicated string, or `NULL` on failure.
 * The caller is responsible for `free()`ing this string.
 */
static char * duplicate_cstr(const char * src, size_t * length);

/*!
 * \brief               Changes the capacity of a string.
 * \param str           The string.
 * \param new_capacity  The new capacity.
 * \returns             `true` if the capacity was successfully changed,
 * `false` otherwise.
 */
static bool change_capacity(ds_str str, const size_t new_capacity);

/*!
 * \brief                   Changes the capacity of a string if needed.
 * \details                 If the string's existing capacity exceeds the
 * requirement capacity, it remains unchanged. Otherwise, the strings capacity
 * is increased to the required capacity.
 * \param str               The string.
 * \param required_capacity The required capacity.
 * \returns                 `true` if the capacity was successfully changed,
 * or if no change was needed, `false` if a capacity change was needed but
 * was not successful.
 */
static bool change_capacity_if_needed(ds_str str,
                                      const size_t required_capacity);

/*!
 * \brief           Truncates a string if necessary.
 * \details         This function truncates the length of a string, and
 * adds a terminating null character in the last place, if the string's
 * capacity is not sufficient to contain the string's current length.
 * This function would normally be called after a reduction in the capacity
 * of the string.
 * \param str       The string.
 */
static void truncate_if_needed(ds_str str);

/*!
 * \brief           Concatenates a C-style string to a string, with length.
 * \details         Passing the length avoids the need to call `strlen()`,
 * which is more efficient when we already know the length.
 * \param dst       The destination string.
 * \param src       The C-style string to concentate with `dst`.
 * \param length    The length of `src`, not including the terminating null.
 * \returns         `dst` on success, `NULL` on failure.
 */
static ds_str ds_str_concat_cstr_size(ds_str dst,
                                      const char * src,
                                      const size_t src_length);

/*!
 * \brief           Removes characters at the start of a string, in place.
 * \param str       The string.
 * \param numchars  The number of characters to remove.
 */
static void ds_str_remove_left(ds_str str, const size_t numchars);

/*!
 * \brief           Removes characters at the end of a string, in place.
 * \param str       The string.
 * \param numchars  The number of characters to remove.
 */
static void ds_str_remove_right(ds_str str, const size_t numchars);

ds_str ds_str_create_direct(char * init_str, const size_t init_str_size) {
    assert(init_str && init_str_size > 0);

    ds_str new_str = malloc(sizeof *new_str);
    if ( !new_str ) {
        free(init_str);
        return NULL;
    }

    new_str->data = init_str;
    new_str->capacity = init_str_size;
    new_str->length = init_str_size - 1;

    return new_str;
}

ds_str ds_str_create(const char * init_str) {
    size_t length;
    char * new_data = duplicate_cstr(init_str, &length);
    if ( !new_data ) {
        return NULL;
    }
    return ds_str_create_direct(new_data, length + 1);
}

ds_str ds_str_dup(ds_str src) {
    return ds_str_create(src->data);
}

ds_str ds_str_create_sprintf(const char * format, ...) {
    static char dummy_buffer[1];

    /*  Determine amount of memory needed  */

    va_list ap;
    va_start(ap, format);
    size_t num_written = vsnprintf(dummy_buffer, 1, format, ap);
    va_end(ap);

    /*  Allocate correct amount of memory  */

    const size_t required_alloc = num_written + 1;
    char * new_data = malloc(required_alloc);
    if ( !new_data ) {
        return NULL;
    }

    /*  Write formatted string  */

    va_start(ap, format);
    num_written = vsnprintf(new_data, required_alloc, format, ap);
    va_end(ap);

    /*  Create and return new string  */

    assert((num_written + 1) == required_alloc);
    return ds_str_create_direct(new_data, required_alloc);
}

void ds_str_destroy(ds_str str) {
    if ( str ) {

        /*  Debug sanity checks  */
        assert(strlen(str->data) == str->length);
        assert(str->capacity > str->length);

        free(str->data);
        free(str);
    }
}

void ds_str_destructor(void * str) {
    ds_str_destroy(str);
}

ds_str ds_str_assign(ds_str dst, ds_str src) {
    return ds_str_assign_cstr_length(dst, src->data, src->length);
}

ds_str ds_str_assign_cstr(ds_str dst, const char * src) {
    return ds_str_assign_cstr_length(dst, src, strlen(src));
}

const char * ds_str_cstr(ds_str str) {
    return str->data;
}

size_t ds_str_length(ds_str str) {
    return str->length;
}

ds_str ds_str_size_to_fit(ds_str str) {
    const size_t max_capacity = str->length + 1;
    if ( str->capacity > max_capacity ) {
        if ( !change_capacity(str, max_capacity) ) {
            return NULL;
        }
    }

    return str;
}

ds_str ds_str_concat(ds_str dst, ds_str src) {
    return ds_str_concat_cstr_size(dst, src->data, src->length);
}

ds_str ds_str_concat_cstr(ds_str dst, const char * src) {
    return ds_str_concat_cstr_size(dst, src, strlen(src));
}

ds_str ds_str_trunc(ds_str str, const size_t length) {
    const size_t new_capacity = length + 1;
    if ( new_capacity < str->capacity ) {
        if ( !change_capacity(str, new_capacity) ) {
            return NULL;
        }
    }

    return str;
}

unsigned long ds_str_hash(ds_str str) {
    unsigned long hash = 5381;
    int c;
    const char * c_str = str->data;

    while ( (c = *c_str++) ) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int ds_str_compare(ds_str s1, ds_str s2) {
    return strcmp(ds_str_cstr(s1), ds_str_cstr(s2));
}

int ds_str_strchr(ds_str str, const char ch) {
    int i = 0;
    while ( str->data[i] && str->data[i] != ch ) {
        ++i;
    }
    return str->data[i] ? i : -1;
}

ds_str ds_str_substr_left(ds_str str, const size_t numchars) {
    ds_str new_substr = ds_str_dup(str);
    ds_str_remove_right(new_substr, new_substr->length - numchars);
    return new_substr;
}

ds_str ds_str_substr_right(ds_str str, const size_t numchars) {
    ds_str new_substr = ds_str_dup(str);
    ds_str_remove_left(new_substr, new_substr->length - numchars);
    return new_substr;
}

void ds_str_split(ds_str src, ds_str * left, ds_str * right, const char sc) {
    int idx = ds_str_strchr(src, sc);
    if ( idx == -1 ) {
        *left = NULL;
        *right = NULL;
    }
    else {
        *left = ds_str_substr_left(src, idx);
        *right = ds_str_substr_right(src, src->length - idx - 1);
    }
}
 
void ds_str_trim_leading(ds_str str) {
    size_t i = 0;
    while ( str->data[i] && isspace(str->data[i]) ) {
        ++i;
    }
    ds_str_remove_left(str, i);
}

void ds_str_trim_trailing(ds_str str) {
    assert(str);

    int i = str->length - 1;
    size_t num = 0;

    while ( i >= 0 && isspace(str->data[i]) ) {
        --i;
        ++num;
    }
    ds_str_remove_right(str, num);
}

void ds_str_trim(ds_str str) {
    ds_str_trim_trailing(str);
    ds_str_trim_leading(str);
}

char ds_str_char_at_index(ds_str str, const size_t index) {
    return str->data[index];
}

bool ds_str_is_empty(ds_str str) {
    return str->length == 0;
}

void ds_str_clear(ds_str str) {
    str->data[0] = '\0';
    str->length = 0;
}

bool ds_str_intval(ds_str str, const int base, int * value) {
    char * endptr;
    const long n = strtol(str->data, &endptr, base);
    if ( *endptr ) {
        *value = 0;
        return false;
    }
    else {
        *value = (int) n;
        return true;
    }
}

bool ds_str_doubleval(ds_str str, double * value) {
    char * endptr;
    const double n = strtod(str->data, &endptr);
    if ( *endptr ) {
        *value = 0;
        return false;
    }
    else {
        *value = n;
        return true;
    }
}

ds_str ds_str_getline(ds_str str, const size_t size, FILE * fp) {
    char * buffer = malloc(size);
    if ( !buffer ) {
        return NULL;
    }

    if ( !fgets(buffer, size, fp) ) {
        free(buffer);
        return NULL;
    }

    size_t length = strlen(buffer);
    if ( length && buffer[length - 1] == '\n' ) {
        buffer[length - 1] = '\0';
        --length;
    }
    return ds_str_assign_cstr_direct(str, buffer, size, length);
}

static ds_str ds_str_assign_cstr_direct(ds_str dst,
                                        char * src,
                                        const size_t size,
                                        const size_t length) {
    assert(size > 0 && length < size);

    free(dst->data);
    dst->data = src;
    dst->capacity = size;
    dst->length = length;

    return dst;
}

static ds_str ds_str_assign_cstr_length(ds_str dst,
                                        const char * src,
                                        const size_t length) {
    const size_t req_cap = length + 1;
    if ( !change_capacity_if_needed(dst, req_cap) ) {
        return NULL;
    }

    memcpy(dst->data, src, req_cap);
    dst->length = length;
    return dst;
}

static char * duplicate_cstr(const char * src, size_t * length) {
    const size_t src_length = strlen(src);
    char * new_str = malloc(src_length + 1);
    if ( !new_str ) {
        return NULL;
    }

    memcpy(new_str, src, src_length + 1);
    if ( length ) {
        *length = src_length;
    }

    return new_str;
}

static bool change_capacity(ds_str str, const size_t new_capacity) {
    assert(new_capacity > 0);

    bool did_reallocate = true;

    char * temp = realloc(str->data, new_capacity);
    if ( temp ) {
        str->data = temp;
        str->capacity = new_capacity;
        truncate_if_needed(str);
    }
    else {
        did_reallocate = false;
    }

    return did_reallocate;
}

static bool change_capacity_if_needed(ds_str str,
                                      const size_t required_capacity) {
    assert(required_capacity > 0);

    if ( required_capacity > str->capacity ) {
        return change_capacity(str, required_capacity);
    }

    return false;
}

static void truncate_if_needed(ds_str str) {
    if ( str->length >= str->capacity ) {
        str->length = str->capacity - 1;
        str->data[str->length] = '\0';
    }
}

static ds_str ds_str_concat_cstr_size(ds_str dst,
                                      const char * src,
                                      const size_t src_length) {
    const size_t req_cap = dst->length + src_length + 1;
    if ( !change_capacity_if_needed(dst, req_cap) ) {
        return NULL;
    }
    memcpy(dst->data + dst->length, src, src_length + 1);
    dst->length += src_length;
    return dst;
}

static void ds_str_remove_right(ds_str str, const size_t numchars) {
    if ( numchars > 0 && numchars <= str->length ) {
        const size_t remaining = str->length - numchars;
        str->data[remaining] = '\0';
        str->length -= numchars;
    }
}

static void ds_str_remove_left(ds_str str, const size_t numchars) {
    if ( numchars > 0 && numchars <= str->length ) {
        const size_t remaining = str->length - numchars;
        memmove(str->data, str->data + numchars, remaining + 1);
        str->length -= numchars;
    }
}

