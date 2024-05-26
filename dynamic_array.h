#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "result.h"
#include "rmath.h"
#include "default_types.h"
#include "color_print.h"

#ifndef COMPARING
#define COMPARING
typedef enum {
    LESS,
    EQUAL,
    GREATER,
} Compareable;
#endif

#ifndef DEFINE_DA

#define new_da(name, type, capacity) \
    type##Da name = {capacity, sizeof(type), 0, (type*) calloc(capacity, sizeof(type))}; \

#define new_sa(name, type, capacity) \
    type _##name[capacity]; \
    type##Sa name = {capacity, sizeof(type), 0, _##name}; 


#define _DA_DEFINE_INSERT(type) \
    type##DaRes insert_##type##Da(type##Da arr, type elem) { \
        size_t MAX = SIZE_MAX / arr.size; \
        type##DaRes ans = {FAILURE, arr}; \
        if (arr.count == arr.capacity) { \
            if (arr.capacity == MAX) { \
                err_redln("Tried to inser into max size and full array!"); \
                return ans; \
            } \
            type* prev = arr.ptr; \
            size_t new_cap = arr.capacity * 2; \
            if (new_cap < arr.capacity) new_cap = MAX; \
            type* new_ptr = (type*) calloc(new_cap, sizeof(type)); \
            memcpy(new_ptr, prev, arr.capacity * sizeof(type)); \
            free(prev); \
            arr.ptr = new_ptr; \
            arr.capacity = new_cap; \
        } \
        arr.ptr[arr.count] = elem; \
        arr.count++; \
        type##DaRes ans2 = {SUCCESS, arr}; \
        return ans2; \
    } \
    voidRes insert_##type##Sa(type##Sa arr, type elem) { \
        voidRes ans = {FAILURE}; \
        if (arr.count == arr.capacity) { \
            err_redln("Tried to inser into max size and full array!"); \
            return ans; \
        } \
        arr.ptr[arr.count] = elem; \
        arr.count++; \
        voidRes ans2 = {SUCCESS}; \
        return ans2; \
    }

#define _DA_DEFINE_FOR_EACH(type) \
    void for_each_##type##Da(type##Da wptr, _da_##type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    } \
    void for_each_##type##Sa(type##Sa wptr, _da_##type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    }

#define _DA_DEFINE_ALL(type) \
    char all_##type##Da(type##Da ptr, _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    } \
    char all_##type##Sa(type##Sa ptr, _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    }

#define _DA_DEFINE_ANY(type) \
    char any_##type##Da(type##Da ptr, _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 1; \
    } \
    char any_##type##Sa(type##Sa ptr, _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 1; \
    } 
    
#define _DA_DEFINE_IN(type) \
    char in_##type##Da(type##Da ptr, type* elem, _da_##type##_equality_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) (elem, (type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    } \
    char in_##type##Sa(type##Sa ptr, type* elem, _da_##type##_equality_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) (elem, (type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    } 
    
#define _DA_DEFINE_MAPIP(type) \
    void mapip_##type##Da(type##Da wptr, _da_##type##_to_##type fn) { \
        for (size_t i = 0; i < wptr.count; i++){\
            wptr.ptr[i] = (*fn) (wptr.ptr+i);\
        }\
    } \
    void mapip_##type##Sa(type##Sa wptr, _da_##type##_to_##type fn) { \
        for (size_t i = 0; i < wptr.count; i++){\
            wptr.ptr[i] = (*fn) (wptr.ptr+i);\
        }\
    }

#define _DA_DEFINE_FOLD_SIG(from_t, to_t) \
    typedef to_t (*_da_sig_collapse_##from_t##_to_##to_t)(to_t*, from_t*); \
    to_t fold_##from_t##Da_to_##to_t(from_t##Da wptr, _da_sig_collapse_##from_t##_to_##to_t fn, to_t start); \
    to_t fold_##from_t##Sa_to_##to_t(from_t##Sa wptr, _da_sig_collapse_##from_t##_to_##to_t fn, to_t start);

#define _DA_DEFINE_FOLD(from_t, to_t) \
    typedef to_t (*_da_collapse_##from_t##_to_##to_t)(to_t*, from_t*); \
    to_t fold_##from_t##Da_to_##to_t(from_t##Da wptr, _da_collapse_##from_t##_to_##to_t fn, to_t start){ \
        for (size_t i = 0; i < wptr.count; i++) { \
            start = (*fn) (&start, wptr.ptr+i); \
        } \
        return start; \
    } \
    to_t fold_##from_t##Sa_to_##to_t(from_t##Sa wptr, _da_collapse_##from_t##_to_##to_t fn, to_t start){ \
        for (size_t i = 0; i < wptr.count; i++) { \
            start = (*fn) (&start, wptr.ptr+i); \
        } \
        return start; \
    }

#define _DA_DEFINE_MAP_SIG(from_t, to_t) \
    typedef to_t (*_da_sig_##from_t##_to_##to_t)(from_t*); \
    to_t##Da map_##from_t##Da_to_##to_t##Da(from_t##Da from_ptr, _da_sig_##from_t##_to_##to_t fn);

#define _DA_DEFINE_MAP(from_t, to_t) \
    typedef to_t (*_da_##from_t##_to_##to_t)(from_t*); \
    to_t##Da map_##from_t##Da_to_##to_t##Da(from_t##Da from_ptr, _da_##from_t##_to_##to_t fn) { \
        new_da(ans, to_t, from_ptr.count) \
        for (size_t i = 0; i < from_ptr.count; i++){\
            ans.ptr[i] = (*fn) (from_ptr.ptr+i);\
        } \
        ans.count = from_ptr.count; \
        return ans; \
    }

// TODO: document
/**
 * I can fearlessly take the result since it accepts a valid DA
 * and there can never be unique elements than elements in the argument
 */
#define _DA_DEFINE_UNIQUE(type) \
    type##Da unique_##type##Da(type##Da wptr, _da_##type##_equality_fn fn) { \
        new_da(vals, type, 2); \
        for (size_t i = 0; i < wptr.count; i++) { \
            if (!in_##type##Da(vals, wptr.ptr+i, fn)) { \
                vals = insert_##type##Da(vals, wptr.ptr[i]).result; \
            } \
        } \
        return vals; \
    }

// TODO: document
#define _DA_DEFINE_SORT(type) \
    void swap_##type(type* ptr1, type* ptr2) { \
        uchar* p1 = (uchar*) ptr1; \
        uchar* p2 = (uchar*) ptr2; \
        for (size_t i = 0; i < sizeof(type); i++) { \
            swap(p1+i, p2+i); \
        } \
    } \
    void _quick_sort_##type(type* arr, size_t low, size_t high, _comperator_##type cmp) { \
        if (high <= low) return; \
        size_t p = high-low/2; \
        size_t h = high; \
        size_t l = low; \
        while (1) { \
            if (l == h) break; \
            if (cmp(arr+l, arr+h) == GREATER) { \
                if (p == h) p = l; \
                if (p == l) p = h; \
                swap_##type(arr+l, arr+h); \
                if (cmp(arr+h, arr+p) == GREATER) h--; \
            } else { \
                if (l != p) l++; \
                else h--; \
            } \
        } \
        _quick_sort_##type(arr, low, save_sub(p,1), cmp); \
        _quick_sort_##type(arr, save_add(p,1), high, cmp); \
    } \
    void sort_##type##Da(type##Da arr, _comperator_##type cmp){ \
        if (arr.count == 0) return; \
        _quick_sort_##type(arr.ptr, 0, arr.count-1, cmp); \
    }

// TODO: universal radix

// Since I can't define (type -> type) maps without macro collision, 
// user has to do that manually, if he needs that (basically solved in the array utils)
#define DEFINE_MAPDA(type) _DA_DEFINE_MAP(type, type)
#define DEFINE_FOLDDA(type) _DA_DEFINE_FOLD(type, type)

#define _DA_DEFINE_FN_SIGS(type) \
    type##DaRes insert_##type##Da(type##Da arr, type elem); \
    voidRes insert_##type##Sa(type##Sa arr, type elem); \
    void for_each_##type##Da(type##Da wptr, _da_##type##_to_void fn); \
    void for_each_##type##Das(type##Sa wptr, _da_##type##_to_void fn); \
    char all_##type##Da(type##Da ptr, _da_truthy_##type##_fn fn); \
    char all_##type##Sa(type##Sa ptr, _da_truthy_##type##_fn fn); \
    char any_##type##Da(type##Da ptr, _da_truthy_##type##_fn fn); \
    char any_##type##Sa(type##Sa ptr, _da_truthy_##type##_fn fn); \
    char in_##type##Da(type##Da ptr, type* elem, _da_##type##_equality_fn fn); \
    char in_##type##Sa(type##Sa ptr, type* elem, _da_##type##_equality_fn fn); \
    void mapip_##type##Da(type##Da wptr, _da_##type##_to_##type fn); \
    void mapip_##type##Sa(type##Sa wptr, _da_##type##_to_##type fn); \
    type##Da unique_##type##Da(type##Da wptr, _da_##type##_equality_fn fn); \
    void sort_##type##Da(type##Da arr, _comperator_##type cmp); \
    DEFAULT_TTYPES(_DA_DEFINE_FOLD_SIG, type); \
    DEFAULT_TTYPES(_DA_DEFINE_MAP_SIG, type);


#define _DA_DEFINE_TYPE_SIGS(type) \
    typedef struct { \
        size_t capacity; \
        unsigned int size; \
        size_t count; \
        type* ptr; \
    } type##Da; \
    typedef struct { \
        size_t capacity; \
        unsigned int size; \
        size_t count; \
        type* ptr; \
    } type##Sa; \
    DEFINE_RESULT(type##Da); \
    typedef char (*_da_##type##_equality_fn)(type*, type*); \
    typedef void (*_da_##type##_to_void)(type*) ; \
    typedef type (*_da_##type##_to_##type)(type*) ; \
    typedef Compareable (*_comperator_##type)(type*, type*); \
    typedef char (*_da_truthy_##type##_fn)(type*);

#define DEFINE_DA(type) \
    _DA_DEFINE_TYPE_SIGS(type) \
    _DA_DEFINE_FN_SIGS(type)

#define IMPL_DA(type) \
    _DA_DEFINE_INSERT(type) \
    _DA_DEFINE_FOR_EACH(type) \
    _DA_DEFINE_ALL(type) \
    _DA_DEFINE_ANY(type) \
    _DA_DEFINE_IN(type) \
    _DA_DEFINE_MAPIP(type) \
    _DA_DEFINE_UNIQUE(type) \
    _DA_DEFINE_SORT(type) \
    DEFAULT_TTYPES(_DA_DEFINE_FOLD, type); \
    DEFAULT_TTYPES(_DA_DEFINE_MAP, type)


DEFAULT_TYPES(_DA_DEFINE_TYPE_SIGS);
DEFAULT_TYPES(_DA_DEFINE_FN_SIGS);

#endif



