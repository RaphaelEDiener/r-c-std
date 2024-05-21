/**
* Raphael Standard Library
* ________________________
*
* How does this work?
* I've preimplemented a default implementation
* for all the most common utility algorithms:
* - for each
* - all
* - map
* - ...
* 
* All utils work with widepointers.
* Create a new widepointer with the following call:
* `new_wp(name, type, amount); // the ';' at the end is not strictly nesseccary`
*
* Since I want to leverage what little type safety there is in C,
* all the functions are postfixed with the type they operate on.
* E.g: for_each_int, for_each_char, ...
*
* The macros are called DEFINE_<function name>.
* E.g: DEFINE_WP(char) - defines a new wide pointer type for characters.
*      DEFINE_FOR_EACH(char) - defines a new for-each for characters.
*      ...
*
* -----------------------------
* Signatures
* -----------------------------
* new_wp(<name>, <type>, <count>)
* for_each_<type>(<wp>, <fn>)
* all_<type>(<wp>, <fn>)
* any_<type>(<wp>, <fn>)
* map<from type>_to_<to type>(<from wp>, <fn>, <to wp>)
* mapip<type>(<wp>, <fn>)

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

#define _WP_DEFINE_FOLD(from_t, to_t) \
    typedef to_t (*_wp_collapse_##from_t##_to_##to_t)(to_t*, from_t*); \
    int fold_##from_t##_to_##to_t(from_t##Wp wptr, _wp_collapse_##from_t##_to_##to_t fn, to_t start){ \
        for (size_t i = 0; i < wptr.count; i++) { \
            start = (*fn) (&start, wptr.address+i); \
        } \
        return start; \
    }

#define _WP_DEFINE_MAP(from_t, to_t) \
    typedef to_t (*_wp_##from_t##_to_##to_t)(from_t*); \
    to_t##Wp map_##from_t##Wp_to_##to_t##Wp(from_t##Wp from_ptr, _wp_##from_t##_to_##to_t fn) { \
        new_wp(ans, to_t, from_ptr.count) \
        for (size_t i = 0; i < from_ptr.count; i++){\
            char res = (*fn) (from_ptr.ptr+i);\
            to_ptr.address[i] = res;\
        } \
        return ans; \
    }

// Since I can't define type -> type maps without macro collision, 
// user has to do that manually, if he needs that (basically solved in the array utils)
#define DEFINE_MAPWP(type) _WP_DEFINE_MAP(type, type)
#define DEFINE_FOLDWP(type) _WP_DEFINE_FOLD(type, type)

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
    typedef char (*_wp_##type##_equality_fn)(type*, type*); \
    typedef void (*_wp_##type##_to_void)(type*) ; \
    typedef type (*_wp_##type##_to_##type)(type*) ; \
    typedef char (*_wp_truthy_##type##_fn)(type*); \
    type##WpRes insert_##type##Wp(type##Wp arr, type elem) { \
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
    voidRes insert_##type##Swp(type##Swp arr, type elem) { \
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
    void for_each_##type#Wp(type##Wp wptr, _wp_##type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    } \
    void for_each_##type##Wps(type##Swp wptr, _wp_##type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    } \
    char all_##type##Wp(type##Wp ptr, _wp_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    } \
    char all_##type##Swp(type##Swp ptr, _wp_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    } \
    char any_##type##Wp(type##Wp ptr, _wp_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 1; \
    } \
    char any_##type##Swp(type##Swp ptr, _wp_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 1; \
    } \
    char in_##type##Wp(type##Wp ptr, type* elem, _wp_##type##_equality_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) (elem, (type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    } \
    char in_##type##Swp(type##Swp ptr, type* elem, _wp_##type##_equality_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) (elem, (type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    } \
    DEFAULT_TTYPES(_WP_DEFINE_FOLD, type); \
    void mapip_##type##Wp(type##Wp wptr, _wp_##type##_to_##type fn) { \
        for (size_t i = 0; i < wptr.count; i++){\
            wptr.ptr[i] = (*fn) (wptr.ptr+i);\
        }\
    } \
    void mapip_##type##Swp(type##Swp wptr, _wp_##type##_to_##type fn) { \
        for (size_t i = 0; i < wptr.count; i++){\
            wptr.ptr[i] = (*fn) (wptr.ptr+i);\
        }\
    } \
    DEFAULT_TTYPES(_WP_DEFINE_MAP, type##Wp) \

// Mapping on the stack is done with the array lib

#define _DEFINE_PRIMITIVE_IN(type) \
    char pin_##type##Wp(type##Wp ptr, type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } \
    char pin_##type##Swp(type##Swp ptr, type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } 

DEFAULT_TYPES(DEFINE_WP);
DEFAULT_TYPES(_DEFINE_PRIMITIVE_IN);

#define new_wp(name, type, capacity) \
    type##Wp name = {capacity, sizeof(type), 0, calloc(capacity, sizeof(type))}; \

#define new_swp(name, type, count) \
    type _##name[count]; \
    type##Swp name = {sizeof(type), count, _##name}; 

#endif



