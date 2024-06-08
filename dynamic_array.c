#include "dynamic_array.h"


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

DEFAULT_TYPES(IMPL_DA);
DEFAULT_TYPES(_DEFINE_PRIMITIVE_IN);
