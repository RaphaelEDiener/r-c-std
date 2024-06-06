/**
 * Iterators
 * TODO: document and test
 */

#include "default_types.h"
#include "result.h"

#ifndef ITER
#define ITER

#define DEFINE_ITER(type) \
    typedef char (*_iter_sig_break)(type*, type*); \
    typedef type (*_iter_sig_step)(type*); \
    typedef struct { \
        type _to; \
        type _i;  \
        _iter_sig_break brk; \
        _iter_sig_step step; \
    } type##Iterator; \
    type##Res next(type##Iterator iter); \
    char is_empty(type##Iterator iter); 

#define DEFINE_ITER_D(type, step_t) \
    typedef char (*_iter_sig_break)(step_t*, step_t*); \
    typedef type (*_iter_sig_d_step)(step_t*, step_t*); \
    typedef struct { \
        type _start; \
        type _end; \
        step_t _i;  \
        step_t _to; \
        _iter_sig_break brk; \
        _iter_sig_d_step stepd; \
    } type##_step_t##Iterator; \
    type##Res next(type##_step_t##Iterator iter, step_t* d); \
    char is_empty(type##_step_t##Iterator iter); 

#define IMPL_ITER(type) \
    type##Res next(type##Iterator iter) { \
        type##Res ans = {FAILURE, 0}; \
        if (iter.brk(iter._i, iter._to)) {return ans;} \
        else { \
            iter._i = iter.step(iter._i); \
            ans.val = iter._i; \
            return ans; \
        } \
    } \
    char is_empty(type##Iterator iter) { \
        return iter.brk(iter.i, iter._to); \
    }
#define IMPL_ITER_D(type, step_t) \
    type##_step_t##Res next(type##_step_t##Iterator iter, step_t* d) { \
        type##_step_t##Res ans = {FAILURE, 0}; \
        if (iter.brk(iter._i, iter._to)) {return ans;} \
        else { \
            iter.i = iter.step(iter.i, iter._to, d); \
            ans.val = iter.i; \
            return ans; \
        } \
    } \
    char is_empty(type##_step_t##Iterator iter) { \
        return iter.brk(iter.i, iter._to); \
    }

DEFAULT_TYPES(DEFINE_ITER);
DEFAULT_TTYPES(DEFINE_ITER_D);

#endif
