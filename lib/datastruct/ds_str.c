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

#include "ds_str.h"

/*!  Structure to contain string  */
struct ds_str {
    char * data;        /*!<  The data in C-style string format     */
    size_t length;      /*!<  The length of the string              */
    size_t capacity;    /*!<  The size of the `data` buffer         */
};

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
static bool change_capacity(struct ds_str * str, const size_t new_capacity);

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
static bool change_capacity_if_needed(struct ds_str * str,
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
static void truncate_if_needed(struct ds_str * str);

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

struct ds_str * ds_str_create(const char * init_str) {
    struct ds_str * new_str = malloc(sizeof *new_str);
    if ( !new_str ) {
        return NULL;
    }

    new_str->data = duplicate_cstr(init_str, &new_str->length);
    if ( !new_str->data ) {
        free(new_str);
        return NULL;
    }
    new_str->capacity = new_str->length + 1;

    return new_str;
}

struct ds_str * ds_str_dup(struct ds_str * src) {
    assert(src);

    return ds_str_create(src->data);
}

struct ds_str * ds_str_create_sprintf(const char * format, ...) {
    assert(format);

    /*  Determine amount of memory needed  */

    char dummy_buffer[1];
    va_list ap;
    va_start(ap, format);
    size_t num_written = vsnprintf(dummy_buffer, 1, format, ap);
    va_end(ap);

    /*  Allocate memory and write  */

    const size_t required_alloc = num_written + 1;
    char * new_data = malloc(required_alloc);
    if ( !new_data ) {
        return NULL;
    }

    va_start(ap, format);
    num_written = vsnprintf(new_data, required_alloc, format, ap);
    va_end(ap);

    /*  Create and return new string  */

    assert((num_written + 1) == required_alloc);
    return ds_str_create_direct(new_data, required_alloc);
}

 struct ds_str * ds_str_create_direct(char * init_str,
                                      const size_t init_str_size) {
    assert(init_str && init_str_size > 0);

    struct ds_str * new_str = malloc(sizeof *new_str);
    if ( !new_str ) {
        free(init_str);
        return NULL;
    }

    new_str->data = init_str;
    new_str->capacity = init_str_size;
    new_str->length = init_str_size - 1;

    return new_str;
}

void ds_str_destroy(struct ds_str * str) {
    assert(str && str->data);

    if ( str ) {
        free(str->data);
        free(str);
    }
}

void ds_str_destructor(void * str) {
    ds_str_destroy(str);
}

const char * ds_str_cstr(struct ds_str * str) {
    return str->data;
}

size_t ds_str_length(struct ds_str * str) {
    return str->length;
}

struct ds_str * ds_str_size_to_fit(struct ds_str * str) {
    assert(str);

    const size_t max_capacity = str->length + 1;
    if ( str->capacity > max_capacity ) {
        if ( change_capacity(str, max_capacity) ) {
            return str;
        }
    }

    return NULL;
}

struct ds_str * ds_str_concat(struct ds_str * dst, struct ds_str * src) {
    assert(dst && src);

    const size_t req_cap = dst->length + src->length + 1;
    if ( !change_capacity_if_needed(dst, req_cap) ) {
        return NULL;
    }
    memcpy(dst->data + dst->length, src->data, src->length + 1);
    dst->length += src->length;
    return dst;
}

struct ds_str * ds_str_concat_cstr(struct ds_str * dst, const char * src) {
    assert(dst && src);

    ds_str src_str = ds_str_create(src);
    if ( !src_str ) {
        return NULL;
    }

    ds_str return_str = ds_str_concat(dst, src_str);
    ds_str_destroy(src_str);

    return return_str;
}

struct ds_str * ds_str_trunc(struct ds_str * str, const size_t length) {
    assert(str);

    const size_t new_capacity = length + 1;
    if ( new_capacity < str->capacity ) {
        if ( !change_capacity(str, new_capacity) ) {
            return NULL;
        }
    }

    return str;
}

unsigned long ds_str_hash(struct ds_str * str) {
    unsigned long hash = 5381;
    int c;
    const char * c_str = ds_str_cstr(str);

    while ( (c = *c_str++) ) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int ds_str_compare(ds_str s1, ds_str s2) {
    return strcmp(ds_str_cstr(s1), ds_str_cstr(s2));
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
    const char * cptr = src->data;

    size_t idx = 0;
    while ( *cptr && *cptr != sc ) {
        ++cptr;
        ++idx;
    }

    if ( !*cptr ) {
        *left = NULL;
        *right = NULL;
    }
    else {
        *left = ds_str_substr_left(src, idx);
        *right = ds_str_substr_right(src, src->length - idx - 1);
    }
}
 
void ds_str_trim_left(ds_str str) {
    assert(str);

    char * cptr = str->data;
    size_t i = 0;

    while ( *cptr && isspace(*cptr) ) {
        ++cptr;
        ++i;
    }

    if ( i ) {
        ds_str_remove_left(str, i);
    }
}

void ds_str_trim_right(ds_str str) {
    assert(str);

    const char * cptr = str->data;
    int i = str->length - 1;
    size_t num = 0;

    while ( i >= 0 && isspace(cptr[i]) ) {
        --i;
        ++num;
    }

    if ( i >= 0 ) {
        ds_str_remove_right(str, num);
    }
}

void ds_str_trim(ds_str str) {
    ds_str_trim_left(str);
    ds_str_trim_right(str);
}

char ds_str_char_at_index(ds_str str, const size_t index) {
    assert(str && index < str->length);

    return str->data[index];
}

bool ds_str_is_empty(ds_str str) {
    assert(str);

    return str->length == 0;
}

static char * duplicate_cstr(const char * src, size_t * length) {
    assert(src);

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

static bool change_capacity(struct ds_str * str, const size_t new_capacity) {
    assert(str && new_capacity > 0);

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

static bool change_capacity_if_needed(struct ds_str * str,
                                      const size_t required_capacity) {
    assert(str && required_capacity > 0);

    if ( required_capacity > str->capacity ) {
        return change_capacity(str, required_capacity);
    }

    return false;
}

static void truncate_if_needed(struct ds_str * str) {
    assert(str);

    if ( str->length >= str->capacity ) {
        str->length = str->capacity - 1;
        str->data[str->length] = '\0';
    }
}

static void ds_str_remove_right(ds_str str, const size_t numchars) {
    if ( numchars <= str->length ) {
        const size_t remaining = str->length - numchars;
        str->data[remaining] = '\0';
        str->length -= numchars;
    }
}

static void ds_str_remove_left(ds_str str, const size_t numchars) {
    if ( numchars <= str->length ) {
        const size_t remaining = str->length - numchars;
        memmove(str->data, str->data + numchars, remaining + 1);
        str->length -= numchars;
    }
}

