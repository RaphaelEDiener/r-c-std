/**
 * comperator for default datatypes
 */
#include "default_types.h"

#ifndef COMPARING
#define COMPARING
typedef enum {
    LESS,
    EQUAL,
    GREATER,
} Compareable;

#define _DEFINE_CMP(type) \
    Compareable cmp_##type (const type  x, const type  y); \
    Compareable pcmp_##type(const type* x, const type* y);
#define DEFINE_EQ(type) \
    char eq_##type (const type  x, const type  y); \
    char peq_##type(const type* x, const type* y);
#define DEFINE_GT(type) \
    char gt_##type (const type  x, const type  y); \
    char pgt_##type(const type* x, const type* y);
#define DEFINE_LT(type) \
    char lt_##type (const type  x, const type  y); \
    char plt_##type(const type* x, const type* y);

/**
 * inlining the value function, 
 * since compilers will optimize pointers more reliable
 * than the other way around
 */
#define IMPL_EQ(type) \
    char peq_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] != b[i]) return 0; \
        } \
        return 1;  \
    } \
    inline char eq_##type(const type x, const type y) { \
        return peq_##type(&x, &y); \
    }


#define IMPL_GT(type) \
    char pgt_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] >  b[i]) return 1; \
            if (a[i] <  b[i]) return 0; \
        } \
        return 0;  \
    } \
    inline char gt_##type(const type x, const type y) { \
        return pgt_##type(&x, &y); \
    }

#define IMPL_LT(type) \
    char plt_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] >  b[i]) return 0; \
            if (a[i] <  b[i]) return 1; \
        } \
        return 0;  \
    } \
    inline char lt_##type(const type x, const type y) { \
        return plt_##type(&x, &y); \
    }


#define _IMPL_CMP(type) \
    Compareable pcmp_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] >  b[i]) return GREATER; \
            if (a[i] <  b[i]) return LESS; \
        } \
        return EQUAL;  \
    } \
    inline Compareable cmp_##type(const type x, const type y) { \
        return pcmp_##type(&x, &y); \
    }


#define _IMPL_PRIM_CMP(type) \
    Compareable pcmp_##type(const type* x, const type* y) { \
        if (*x > *y) return GREATER; \
        else if (*x < *y) return LESS; \
        else return EQUAL; \
    } \
    inline Compareable cmp_##type(const type x, const type y) { \
        return pcmp_##type(&x, &y); \
    }


#define _IMPL_PRIM_EQ(type) \
    inline char peq_##type(const type* x, const type* y) { \
        return (*x == *y);  \
    } \
    inline char eq_##type (const type  x, const type  y) { \
        return ( x ==  y);  \
    }
#define _IMPL_PRIM_LT(type) \
    inline char pgt_##type(const type* x, const type* y) { \
        return (*x  < *y);  \
    } \
    inline char gt_##type (const type  x, const type  y) { \
        return ( x  <  y);  \
    }
#define _IMPL_PRIM_GT(type) \
    inline char plt_##type(const type* x, const type* y) { \
        return (*x  > *y);  \
    } \
    inline char lt_##type (const type  x, const type  y) { \
        return ( x  >  y);  \
    }

#define DEFINE_CMP(type) \
    _DEFINE_CMP(type) \
    DEFINE_EQ(type) \
    DEFINE_LT(type) \
    DEFINE_GT(type) \

DEFAULT_TYPES(DEFINE_CMP);

#define IMPL_CMP(type) \
    _IMPL_CMP(type) \
    IMPL_EQ(type) \
    IMPL_LT(type) \
    IMPL_GT(type) \

#endif
