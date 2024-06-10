#include "dynamic_array.h"


#define _DEFINE_PRIMITIVE_IN(type) \
    char pin_##type##Da(const type##Da ptr, const type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } \
    char pin_##type##Sa(const type##Sa ptr, const type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } 

DEFAULT_TYPES(IMPL_DA);
DEFAULT_TYPES(_DEFINE_PRIMITIVE_IN);

/**
 * removes an element from the back of the dynamic array
 */ 
intDaRes pop(const intDa arr) {
    intDa ans = {arr.capacity, sizeof(int), arr.count, arr.ptr};
    intDaRes res = {FAILURE, ans};
    if (arr.count == 0) {
        
    }
}
