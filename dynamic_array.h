#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h> 
#include "result.h"
#include "rmath.h"
#include "default_types.h"
#include "color_print.h"
#include "cmp.h"

#ifndef DEFINE_DA

#define _DA_IMPL_NEW(t) \
    t##DaRes new_##t##Da(const size_t capacity) { \
        t##Da ans = {capacity, sizeof(t), 0, (t*) calloc(capacity, sizeof(t))}; \
        t##DaRes res = {FAILURE, ans}; \
        if (ans.ptr == NULL) { \
            err_redln("failed to allocated for with capacity of %zu", capacity); \
            return res; \
        } \
        else { \
        res.type = SUCCESS; \
        return res; \
        } \
    }

#define new_sa(name, type, capacity) \
    type _##name[capacity]; \
    type##Sa name = {capacity, sizeof(type), 0, _##name}; \
    assert(name.ptr != NULL);

/**
 * I've removed checking for inserting into something which reached its
 * theoretical maximum.
 * Thats in the zetabytes.
 * Not hitting zetabyre ram sticks anytime soon~
 */
#define _DA_IMPL_INSERT(type) \
    type##DaRes insert_##type##Da(const type##Da arr, const type elem) { \
        type##Da new_arr = {arr.capacity, sizeof(type), arr.count, arr.ptr}; \
        type##DaRes ans = {FAILURE, arr}; \
        if (arr.count == arr.capacity) { \
            type* prev = arr.ptr; \
            size_t new_cap = (arr.capacity == 0) ? 8 : arr.capacity * 2; \
            type* new_ptr = (type*) calloc(new_cap, sizeof(type)); \
            if (new_ptr == NULL) { \
                err_redln("failed to allocated for new capacity of %zu", new_cap); \
                return ans; \
            } \
            memcpy(new_ptr, prev, arr.capacity * sizeof(type)); \
            free(prev); \
            new_arr.ptr = new_ptr; \
            new_arr.capacity = new_cap; \
        } \
        new_arr.ptr[new_arr.count] = elem; \
        new_arr.count++; \
        type##DaRes ans2 = {SUCCESS, new_arr}; \
        return ans2; \
    } \
    voidRes insert_##type##Sa(type##Sa arr, const type elem) { \
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
    void for_each_##type##Da(const type##Da wptr, const _da_##type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    } \
    void for_each_##type##Sa(const type##Sa wptr, const _da_##type##_to_void fn) { \
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
    to_t##DaRes map_##from_t##Da_to_##to_t##Da(const from_t##Da from_ptr, const _da_sig_##from_t##_to_##to_t fn);

#define _DA_DEFINE_MAP(from_t, to_t) \
    typedef to_t (*_da_##from_t##_to_##to_t)(from_t*); \
    to_t##DaRes map_##from_t##Da_to_##to_t##Da(const from_t##Da from_ptr, const _da_##from_t##_to_##to_t fn) { \
        to_t##DaRes ans = new_##to_t##Da(from_ptr.count); \
        if (ans.type == FAILURE) return ans; \
        for (size_t i = 0; i < from_ptr.count; i++){\
            ans.result.ptr[i] = (*fn) (from_ptr.ptr+i);\
        } \
        ans.result.count = from_ptr.count; \
        return ans; \
    }

/**
 * I can fearlessly take the result since it accepts a valid DA
 * and there can never be unique elements than elements in the argument
 * TODO: change up algorithm to overallocate and then shrink to size afterward
 */
#define _DA_DEFINE_UNIQUE(t) \
    t##DaRes unique_##t##Da(const t##Da wptr, const _da_##t##_equality_fn fn) { \
        t##DaRes vals = new_##t##Da(2); \
        if (vals.type == FAILURE) return vals; \
        for (size_t i = 0; i < wptr.count; i++) { \
            if (!in_##t##Da(vals.result, wptr.ptr+i, fn)) { \
                vals = insert_##t##Da(vals.result, wptr.ptr[i]); \
                if (vals.type == FAILURE) return vals; \
            } \
        } \
        return vals; \
    }

#define _DA_DEFINE_SORT(type) \
    DEFINE_SWAP(type) \
    void _quick_sort_##type(type* arr, size_t low, size_t high, _da_comperator_##type cmp) { \
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
    void sort_##type##Da(type##Da arr, _da_comperator_##type cmp){ \
        if (arr.count == 0) return; \
        _quick_sort_##type(arr.ptr, 0, arr.count-1, cmp); \
    }

#define _DA_DEFINE_RADIX(type) \
    void radix_##type##DA(type##Da arr) { \
        size_t size = sizeof(type); \
        new_sa(buff0, type, arr.count); \
        new_sa(buff1, type, arr.count); \
        new_sa(buff2, type, arr.count); \
        new_sa(buff3, type, arr.count); \
        for (size_t b = 0; b < size; b++) { \
            for (uchar shift = 0; shift < 4; shift++) { \
                for (size_t i = 0; i < arr.count; i++) { \
                    type elem = arr.ptr[i]; \
                    uchar* ptr = (uchar*) &elem; \
                    uchar byte = *(ptr+(size-(b+1))); \
                    byte >>= 2 * shift; \
                    uchar masked = byte & 3; \
                    switch (masked) { \
                        case 0: insert_##type##Sa(buff0, elem); break; \
                        case 1: insert_##type##Sa(buff1, elem); break; \
                        case 2: insert_##type##Sa(buff2, elem); break; \
                        case 3: insert_##type##Sa(buff3, elem); break; \
                    } \
                } \
                arr.count = 0; \
                for (size_t i = 0; i < buff0.count; i++) insert_##type##Da(arr, buff0.ptr[i]); \
                for (size_t i = 0; i < buff1.count; i++) insert_##type##Da(arr, buff1.ptr[i]); \
                for (size_t i = 0; i < buff2.count; i++) insert_##type##Da(arr, buff2.ptr[i]); \
                for (size_t i = 0; i < buff3.count; i++) insert_##type##Da(arr, buff3.ptr[i]); \
                buff0.count = 0; \
                buff1.count = 0; \
                buff2.count = 0; \
                buff3.count = 0; \
            } \
        } \
    }


// Since I can't define (type -> type) maps without macro collision, 
// user has to do that manually, if he needs that (basically solved in the array utils)
#define DEFINE_MAPDA(type) _DA_DEFINE_MAP(type, type)
#define DEFINE_FOLDDA(type) _DA_DEFINE_FOLD(type, type)

#define _DA_DEFINE_FN_SIGS(type) \
    type##DaRes new_##type##Da(const size_t capacity); \
    type##DaRes insert_##type##Da(const type##Da arr, const type elem); \
    voidRes insert_##type##Sa(type##Sa arr, const type elem); \
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
    type##DaRes unique_##type##Da(const type##Da wptr, const _da_##type##_equality_fn fn); \
    void sort_##type##Da(type##Da arr, _da_comperator_##type cmp); \
    DEFAULT_TTYPES(_DA_DEFINE_FOLD_SIG, type); \
    DEFAULT_TTYPES(_DA_DEFINE_MAP_SIG, type); \
    void radix_##type##DA(type##Da arr);


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
    typedef Compareable (*_da_comperator_##type)(type*, type*); \
    typedef char (*_da_truthy_##type##_fn)(type*);

#define DEFINE_DA(type) \
    _DA_DEFINE_TYPE_SIGS(type) \
    _DA_DEFINE_FN_SIGS(type)

#define IMPL_DA(type) \
    _DA_IMPL_NEW(type) \
    _DA_IMPL_INSERT(type) \
    _DA_DEFINE_FOR_EACH(type) \
    _DA_DEFINE_ALL(type) \
    _DA_DEFINE_ANY(type) \
    _DA_DEFINE_IN(type) \
    _DA_DEFINE_MAPIP(type) \
    _DA_DEFINE_UNIQUE(type) \
    _DA_DEFINE_SORT(type) \
    DEFAULT_TTYPES(_DA_DEFINE_FOLD, type); \
    DEFAULT_TTYPES(_DA_DEFINE_MAP, type); \
    _DA_DEFINE_RADIX(type);


DEFAULT_TYPES(_DA_DEFINE_TYPE_SIGS);
DEFAULT_TYPES(_DA_DEFINE_FN_SIGS);

#endif



