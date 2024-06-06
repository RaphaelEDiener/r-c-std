#include "dynamic_array.h"

/**
 * redefining private macros here, to avoid the type doesn't exist problem
 * when defining function with and from and to those types
 *
 * They are an exact copy of the #DEFINE_DA macro split up
 */

#define _DEFINE_PRIMITIVE_FUNCTIONS(type) \
    _DA_IMPL_INSERT(type) \
    _DA_DEFINE_FOR_EACH(type) \
    _DA_DEFINE_ALL(type) \
    _DA_DEFINE_ANY(type) \
    _DA_DEFINE_IN(type) \
    _DA_DEFINE_MAPIP(type) \
    DEFAULT_TTYPES(_DA_DEFINE_FOLD, type); \
    DEFAULT_TTYPES(_DA_DEFINE_MAP, type)

#define _DEFINE_PRIMITIVE_IN(type) \
    char pin_##type##Da(type##Da ptr, type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } \
    char pin_##type##Sa(type##Sa ptr, type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } 

DEFAULT_TYPES(_DEFINE_PRIMITIVE_FUNCTIONS);
DEFAULT_TYPES(_DEFINE_PRIMITIVE_IN);
