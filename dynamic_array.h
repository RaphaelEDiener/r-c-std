/**
 * array operations which take care of resizing
 * typedef struct { 
 *     size_t capacity;
 *     unsigned int size; 
 *     size_t count; 
 *     type* ptr; 
 *  } type##Wp; 
 *
 *  also defines corresponding result type
 *
 *  insert(wp, elem) -> res
 *  in case of inserting into a max full wp,
 *  does nothing and returns wp.
 *
 *  In case one is working with stack wide pointers,
 *  inserstion becomes a side effect function
 *  and automatically resizing is not supported anymore.
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "result.h"
#include "default_types.h"
#include "color_print.h"

#ifndef DEFINE_WP
#define DEFINE_WP(type) \
    typedef struct { \
        size_t capacity; \
        unsigned int size; \
        size_t count; \
        type* ptr; \
    } type##Wp; \
    typedef struct { \
        size_t capacity; \
        unsigned int size; \
        size_t count; \
        type* ptr; \
    } type##Swp; \
    DEFINE_RESULT(type##Wp); \
    type##WpRes insert_##type(type##Wp arr, type elem) { \
        size_t MAX = SIZE_MAX / arr.size; \
        type##WpRes ans = {FAILURE, arr}; \
        if (arr.count == arr.capacity) { \
            if (arr.capacity == MAX) { \
                err_redln("Tried to inser into max size and full array!"); \
                return ans; \
            } \
            type* prev = arr.ptr; \
            size_t new_cap = arr.capacity * 2; \
            if (new_cap < arr.capacity) new_cap = MAX; \
            type* new_ptr = calloc(new_cap, sizeof(type)); \
            memcpy(new_ptr, prev, arr.capacity * sizeof(type)); \
            free(prev); \
            arr.ptr = new_ptr; \
            arr.capacity = new_cap; \
        } \
        arr.ptr[arr.count] = elem; \
        arr.count++; \
        type##WpRes ans2 = {SUCCESS, arr}; \
        return ans2; \
    } \
    voidRes s_insert_##type(type##Swp arr, type elem) { \
        voidRes ans = {FAILURE}; \
        if (arr.count == arr.capacity) { \
            err_redln("Tried to inser into max size and full array!"); \
            return ans; \
        } \
        arr.ptr[arr.count] = elem; \
        arr.count++; \
        voidRes ans2 = {SUCCESS}; \
        return ans2; \
    } \
    typedef void (*type##_to_void)(type*) ; \
    void for_each_##type(type##Wp wptr, type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    } \
    void s_for_each_##type(type##Swp wptr, type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    } \
    typedef char (*truthy_##type##_fn)(type*); \
    char all_##type(type##Wp ptr, truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    } \
    char s_all_##type(type##Swp ptr, truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    } \
    typedef char (*type##_equality_fn)(type*, type*); \
    char in_##type##Wp(type##Wp ptr, type* elem, type##_equality_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) (elem, (type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    }

DEFAULT_TYPES(DEFINE_WP);

#define new_wp(name, type, capacity) \
    type##Wp name = {capacity, sizeof(type), 0, calloc(capacity, sizeof(type))}; \

#define new_swp(name, type, count) \
    type _##name[count]; \
    type##Swp name = {sizeof(type), count, _##name}; 

#endif



