#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "result.h"
#include "rmath.h"
#include "default_types.h"
#include "color_print.h"
#include "cmp.h"
#include "array_utils.h"

#ifndef DEFINE_DA

#define _DA_DEF_NEW(t) \
    t##DaRes new_##t##Da(const size_t capacity);

#define _DA_IMPL_NEW(t) \
    t##DaRes new_##t##Da(const size_t capacity) { \
        if (capacity < 1) { \
            err_redln("can't work with empty DA's"); \
            t##Da ans = {0, 0, 0, NULL}; \
            t##DaRes res = {FAILURE, ans}; \
            return res; \
        } \
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
    type##Sa name = {capacity, sizeof(type), 0, _##name};

#define _DA_DEF_INSERT(type) \
    type##DaRes insert_##type##Da (const type##Da* arr, const type  elem); \
    voidRes     insert_##type##Sa (      type##Sa* arr, const type  elem); \
    type##DaRes pinsert_##type##Da(const type##Da* arr, const type* elem); \
    voidRes     pinsert_##type##Sa(      type##Sa* arr, const type* elem);

/**
 * I've removed checking for inserting into something which reached its
 * theoretical maximum.
 * Thats in the zetabytes.
 * Not hitting zetabyre ram sticks anytime soon~
 */
#define _DA_IMPL_INSERT(type) \
    type##DaRes insert_##type##Da(const type##Da* arr, const type elem) { \
        size_t new_cap = arr->capacity; \
        type*  new_ptr = arr->ptr; \
        type##DaRes failure = {FAILURE, {new_cap, arr->size, arr->count+1, new_ptr}}; \
        if (arr->count == arr->capacity) { \
            type* prev = arr->ptr; \
            new_cap = (arr->capacity == 0) ? 8 : arr->capacity * 2; \
            new_ptr = (type*) calloc(new_cap, arr->size); \
            if (new_ptr == NULL) { \
                err_redln("failed to allocated for new capacity of %zu", new_cap); \
                return failure; \
            } \
            memcpy(new_ptr, prev, arr->capacity * arr->size); \
            FREE(prev); \
        } \
        new_ptr[arr->count] = elem; \
        type##Da new_arr = {new_cap, arr->size, arr->count+1, new_ptr}; \
        type##DaRes ans2 = {SUCCESS, new_arr}; \
        return ans2; \
    } \
    voidRes insert_##type##Sa(type##Sa* arr, const type elem) { \
        voidRes ans = {FAILURE}; \
        if (arr->count == arr->capacity) { \
            err_redln("Tried to inser into max size and full array!"); \
            return ans; \
        } \
        arr->ptr[arr->count] = elem; \
        arr->count++; \
        voidRes ans2 = {SUCCESS}; \
        return ans2; \
    } \
    inline type##DaRes pinsert_##type##Da(const type##Da* arr, const type* elem) { \
        return insert_##type##Da(arr, *elem); \
    } \
    inline voidRes     pinsert_##type##Sa(      type##Sa* arr, const type* elem) { \
        return insert_##type##Sa(arr, *elem); \
    } ;

#define _DA_DEF_FOR_EACH(type) \
    void for_each_##type##Da(const type##Da wptr, const _da_##type##_to_void fn); \
    void for_each_##type##Sa(const type##Sa wptr, const _da_##type##_to_void fn);

#define _DA_IMPL_FOR_EACH(type) \
    inline void for_each_##type##Da(const type##Da wptr, const _da_##type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    } \
    inline void for_each_##type##Sa(const type##Sa wptr, const _da_##type##_to_void fn) { \
        for (size_t i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.ptr + i); \
        } \
    }

#define _DA_DEF_ALL(type) \
    char all_##type##Da(const type##Da ptr, const _da_truthy_##type##_fn fn); \
    char all_##type##Sa(const type##Sa ptr, const _da_truthy_##type##_fn fn);

#define _DA_IMPL_ALL(type) \
    char all_##type##Da(const type##Da ptr, const _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    } \
    char all_##type##Sa(const type##Sa ptr, const _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    }

#define _DA_DEF_ANY(type) \
    char any_##type##Da(const type##Da ptr, const _da_truthy_##type##_fn fn); \
    char any_##type##Sa(const type##Sa ptr, const _da_truthy_##type##_fn fn);

#define _DA_IMPL_ANY(type) \
    char any_##type##Da(const type##Da ptr, const _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    } \
    char any_##type##Sa(const type##Sa ptr, const _da_truthy_##type##_fn fn) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((type*) ptr.ptr+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    } 

#define _DA_DEF_IN(type) \
    char in_##type##Da( \
        const type##Da ptr, const type* elem, const _da_comperator_##type fn \
    ); \
    char in_##type##Sa( \
        const type##Sa ptr, const type* elem, const _da_comperator_##type fn \
    );

#define _DA_IMPL_IN(type) \
    char in_##type##Da( \
        const type##Da ptr, const type* elem, const _da_comperator_##type fn \
    ) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) (elem, (type*) ptr.ptr+i); \
            if ( res == EQUAL ) return 1; \
        } \
        return 0; \
    } \
    char in_##type##Sa( \
        const type##Sa ptr, const type* elem, const _da_comperator_##type fn \
    ) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            char res = (*fn) (elem, (type*) ptr.ptr+i); \
            if ( res == EQUAL ) return 1; \
        } \
        return 0; \
    } 

#define _DA_DEF_MAPIP(type) \
    void mapip_##type##Da(type##Da wptr, const _da_##type##_to_##type fn); \
    void mapip_##type##Sa(type##Sa wptr, const _da_##type##_to_##type fn);

#define _DA_IMPL_MAPIP(type) \
    void mapip_##type##Da(type##Da wptr, const _da_##type##_to_##type fn) { \
        for (size_t i = 0; i < wptr.count; i++){\
            wptr.ptr[i] = (*fn) (wptr.ptr+i);\
        }\
    } \
    void mapip_##type##Sa(type##Sa wptr, const _da_##type##_to_##type fn) { \
        for (size_t i = 0; i < wptr.count; i++){\
            wptr.ptr[i] = (*fn) (wptr.ptr+i);\
        }\
    }

#define _DA_DEF_FOLD(t) \
    typedef t (*_da_sig_collapse_##t) (const t*, const t*); \
    t fold_##t##Da( \
        const t##Da wptr, \
        const _da_sig_collapse_##t fn, \
        const t start \
    );

#define _DA_IMPL_FOLD(t) \
    typedef t (*_da_collapse_##t) (const t*, const t*); \
    t fold_##t##Da( \
        const t##Da wptr, \
        const _da_sig_collapse_##t fn, \
        const t start \
    ){ \
        t res = start; \
        for (size_t i = 0; i < wptr.count; i++) { \
            res = (*fn) (&res, wptr.ptr+i); \
        } \
        return res; \
    }

#define _DA_DEF_FOLD_TO(from_t, to_t) \
    typedef to_t (*_da_sig_collapse_##from_t##_to_##to_t) \
                 (const to_t*, const from_t*); \
    to_t fold_##from_t##Da_to_##to_t( \
        const from_t##Da wptr, \
        const _da_sig_collapse_##from_t##_to_##to_t fn, \
        const to_t start \
    ); \
    to_t fold_##from_t##Sa_to_##to_t( \
        const from_t##Sa wptr, \
        const _da_sig_collapse_##from_t##_to_##to_t fn, \
        const to_t start \
    );

#define _DA_IMPL_FOLD_TO(from_t, to_t) \
    typedef to_t (*_da_collapse_##from_t##_to_##to_t) \
                 (const to_t*, const from_t*); \
    to_t fold_##from_t##Da_to_##to_t( \
        const from_t##Da wptr, \
        const _da_collapse_##from_t##_to_##to_t fn, \
        const to_t start \
    ){ \
        to_t res = start; \
        for (size_t i = 0; i < wptr.count; i++) { \
            res = (*fn) (&res, wptr.ptr+i); \
        } \
        return res; \
    } \
    to_t fold_##from_t##Sa_to_##to_t( \
        const from_t##Sa wptr, \
        const _da_collapse_##from_t##_to_##to_t fn, \
        const to_t start \
    ){ \
        to_t res = start; \
        for (size_t i = 0; i < wptr.count; i++) { \
            res = (*fn) (&res, wptr.ptr+i); \
        } \
        return res; \
    }

#define _DA_DEF_MAP(from_t, to_t) \
    typedef to_t (*_da_##from_t##_to_##to_t)(const from_t*); \
    to_t##DaRes map_##from_t##Da_to_##to_t##Da( \
        const from_t##Da from_ptr, const _da_##from_t##_to_##to_t fn \
    );

#define _DA_IMPL_MAP(from_t, to_t) \
    to_t##DaRes map_##from_t##Da_to_##to_t##Da( \
        const from_t##Da from_ptr, const _da_##from_t##_to_##to_t fn \
    ) { \
        to_t##DaRes ans = new_##to_t##Da(from_ptr.count); \
        if (ans.type == FAILURE) return ans; \
        for (size_t i = 0; i < from_ptr.count; i++){\
            ans.result.ptr[i] = (*fn) (from_ptr.ptr+i);\
        } \
        ans.result.count = from_ptr.count; \
        return ans; \
    }

#define _DA_DEF_UNIQUE(t) \
    t##DaRes unique_##t##Da(const t##Da wptr, const _da_##t##_equality_fn eq);

#define _DA_IMPL_UNIQUE(t) \
    t##DaRes unique_##t##Da(const t##Da wptr, const _da_##t##_equality_fn eq) { \
        const t##DaRes failure = {FAILURE, wptr}; \
        size_t count = 0; \
        t* vals = malloc(wptr.count * sizeof(t)); \
        if (vals == NULL) return failure; \
        for (size_t i = 0; i < wptr.count; i++) { \
            char in = 0; \
            for (size_t v = 0; v < count; v++) { \
                if (eq(vals+v, wptr.ptr+i)) { \
                    in = 1;  \
                    break; \
                } \
            } \
            if (!in) { \
                vals[count] = wptr.ptr[i]; \
                count++; \
            } \
        } \
        t* new_ptr = realloc(vals, count * sizeof(t)); \
        if (new_ptr == NULL) return failure; \
        const t##Da ans = {count, wptr.size, count, new_ptr}; \
        const t##DaRes success = {SUCCESS, ans}; \
        return success; \
    }

#define _DA_DEF_SORT(type) \
    void sort_##type##Da(type##Da arr, const _da_comperator_##type cmp);

#define _DA_IMPL_SORT(type) \
    void _quick_sort_##type( \
        type* arr, \
        const size_t low, \
        const size_t high, \
        const _da_comperator_##type cmp \
    ) { \
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
    void sort_##type##Da(type##Da arr, const _da_comperator_##type cmp) { \
        if (arr.count == 0) return; \
        _quick_sort_##type(arr.ptr, 0, arr.count-1, cmp); \
    }

#define _DA_DEF_RADIX(type) \
    void radix_##type##Da(type##Da arr); 

#define _DA_IMPL_RADIX(type) \
    void radix_##type##Da(type##Da arr) { \
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
                        case 0: insert_##type##Sa(&buff0, elem); break; \
                        case 1: insert_##type##Sa(&buff1, elem); break; \
                        case 2: insert_##type##Sa(&buff2, elem); break; \
                        case 3: insert_##type##Sa(&buff3, elem); break; \
                    } \
                } \
                arr.count = 0; \
                for (size_t i = 0; i < buff0.count; i++) { \
                    type##Da res = insert_##type##Da(&arr, buff0.ptr[i]).result; \
                    arr.ptr = res.ptr; \
                    arr.count = res.count; \
                } \
                for (size_t i = 0; i < buff1.count; i++) { \
                    type##Da res = insert_##type##Da(&arr, buff1.ptr[i]).result; \
                    arr.ptr = res.ptr; \
                    arr.count = res.count; \
                } \
                for (size_t i = 0; i < buff2.count; i++) { \
                    type##Da res = insert_##type##Da(&arr, buff2.ptr[i]).result; \
                    arr.ptr = res.ptr; \
                    arr.count = res.count; \
                } \
                for (size_t i = 0; i < buff3.count; i++) { \
                    type##Da res = insert_##type##Da(&arr, buff3.ptr[i]).result; \
                    arr.ptr = res.ptr; \
                    arr.count = res.count; \
                } \
                buff0.count = 0; \
                buff1.count = 0; \
                buff2.count = 0; \
                buff3.count = 0; \
            } \
        } \
    }

#define _DA_DEF_REVERSE(type) \
    void reverse_##type##Da(type##Da arr);

#define _DA_IMPL_REVERSE(type) \
    void reverse_##type##Da(type##Da arr) { \
        for (size_t i = 0; i < (arr.count / 2); i++) { \
            swap_##type(arr.ptr + i, arr.ptr + arr.count - i - 1); \
        } \
    }

#define _DA_DEF_GET(type) \
    type##Res get_##type##Da(const type##Da arr, const llong i);

// Accessing [0] always works since min len == 1
#define _DA_IMPL_GET(t) \
    t##Res get_##t##Da(const t##Da arr, const llong i) { \
        t##Res res = {FAILURE, arr.ptr[0]}; \
        if ( \
            (i >= 0 && (i > (llong) arr.count - 1)) || \
            (-i) > (llong) arr.count \
        ) { \
            err_redln("position %llu is out side of bounds. current len is %zu", i, arr.count); \
            return res; \
        } \
        size_t real_i = i >= 0 ? (size_t) i : (size_t) (arr.count + i); \
        res.result = arr.ptr[real_i]; \
        res.type = SUCCESS; \
        return res; \
    }

#define _DEFINE_DA_PRIMITIVE_IN(type) \
    char pin_##type##Da(type##Da ptr, const type* elem); \
    char pin_##type##Sa(type##Sa ptr, const type* elem);

#define _IMPL_DA_PRIMITIVE_IN(type) \
    char pin_##type##Da(type##Da ptr, const type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } \
    char pin_##type##Sa(type##Sa ptr, const type* elem) { \
        for (size_t i = 0; i < ptr.count; i++){ \
            if ( *elem == ptr.ptr[i] ) return 1; \
        } \
        return 0; \
    } 

#define _DA_DEF_FIRST(type) \
    type##Res first_##type##Da(const type##Da arr, const _da_truthy_##type##_fn fn);

#define _DA_IMPL_FIRST(t) \
    t##Res first_##t##Da(const t##Da arr, const _da_truthy_##t##_fn fn) { \
        t##Res ans = {0};\
        ans.type   = FAILURE; \
        for (size_t i = 0; i < arr.count; i++){ \
            char found = (*fn) ((t*) arr.ptr+i); \
            if ( found ) { \
                ans.result = arr.ptr[i]; \
                ans.type   = SUCCESS; \
                return ans; \
            }; \
        } \
        return ans; \
    }

// Since I can't define (type -> type) maps without macro collision, 
// user has to do that manually, 
// if he needs that (basically solved in the array utils)
#define DEFINE_MAPDA(type) _DA_DEFINE_MAP(type, type)
#define DEFINE_FOLDDA(type) _DA_DEFINE_FOLD(type, type)

#define _DA_DEFINE_FN_SIGS(type) \
    _DA_DEF_NEW(type) \
    _DA_DEF_INSERT(type) \
    _DA_DEF_FOR_EACH(type) \
    _DA_DEF_ALL(type) \
    _DA_DEF_ANY(type) \
    _DA_DEF_IN(type) \
    _DA_DEF_MAPIP(type) \
    _DA_DEF_FOLD(type) \
    DEFAULT_TTYPES(_DA_DEF_FOLD_TO, type); \
    DEFAULT_TTYPES(_DA_DEF_MAP, type); \
    _DA_DEF_UNIQUE(type) \
    _DA_DEF_SORT(type) \
    _DA_DEF_RADIX(type) \
    _DA_DEF_GET(type) \
    _DA_DEF_FIRST(type) \
    _DA_DEF_REVERSE(type)

#define _DA_DEFINE_TYPE_SIGS(type) \
    typedef struct { \
        size_t capacity; \
        size_t size; \
        size_t count; \
        type* ptr; \
    } type##Da; \
    typedef struct { \
        const size_t capacity; \
        const size_t size; \
        size_t count; \
        type* ptr; \
    } type##Sa; \
    DEFINE_RESULT(type##Da); \
    typedef char (*_da_##type##_equality_fn)(const type*, const type*); \
    typedef void (*_da_##type##_to_void)(const type*) ; \
    typedef type (*_da_##type##_to_##type)(const type*) ; \
    typedef Compareable (*_da_comperator_##type)(const type*, const type*); \
    typedef char (*_da_truthy_##type##_fn)(const type*);

#define DEFINE_DA(type) \
    _DA_DEFINE_TYPE_SIGS(type) \
    _DA_DEFINE_FN_SIGS(type)

#define IMPL_DA(type) \
    _DA_IMPL_NEW(type) \
    _DA_IMPL_INSERT(type) \
    _DA_IMPL_FOR_EACH(type) \
    _DA_IMPL_ALL(type) \
    _DA_IMPL_ANY(type) \
    _DA_IMPL_IN(type) \
    _DA_IMPL_MAPIP(type) \
    _DA_IMPL_FOLD(type) \
    DEFAULT_TTYPES(_DA_IMPL_FOLD_TO, type); \
    DEFAULT_TTYPES(_DA_IMPL_MAP,  type); \
    _DA_IMPL_UNIQUE(type) \
    _DA_IMPL_SORT(type) \
    _DA_IMPL_REVERSE(type) \
    _DA_IMPL_GET(type) \
    _DA_IMPL_FIRST(type) \
    _DA_IMPL_RADIX(type);

DEFAULT_TYPES(_DA_DEFINE_TYPE_SIGS);
DEFAULT_TYPES(_DA_DEFINE_FN_SIGS);
DEFAULT_TYPES(_DEFINE_DA_PRIMITIVE_IN);
MATH_TYPES(DEFINE_DA);

#endif



