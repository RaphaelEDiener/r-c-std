#include "dynamic_array.h"

/**
 * redefining private macros here, to avoid the type doesn't exist problem
 * when defining function with and from and to those types
 *
 * They are an exact copy of the #DEFINE_WP macro split up
 */

#define _DEFINE_PRIMITIVE_FUNCTIONS(type) \
    _WP_DEFINE_INSERT(type) \
    _WP_DEFINE_FOR_EACH(type) \
    _WP_DEFINE_ALL(type) \
    _WP_DEFINE_ANY(type) \
    _WP_DEFINE_IN(type) \
    _WP_DEFINE_MAPIP(type) \
    DEFAULT_TTYPES(_WP_DEFINE_FOLD, type); \
    DEFAULT_TTYPES(_WP_DEFINE_MAP, type)

#define _DEFINE_PRIMITIVE_IN(type) \
    char pin_##type##Wp(type##Wp ptr, type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } \
    char pin_##type##Swp(type##Swp ptr, type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } 

DEFAULT_TYPES(_DEFINE_PRIMITIVE_FUNCTIONS);
DEFAULT_TYPES(_DEFINE_PRIMITIVE_IN);
