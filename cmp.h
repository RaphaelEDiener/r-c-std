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
    Compareable cmp_##type(const type* x, const type* y);

#define DEFINE_EQ(type) \
    char eq_##type(const type* x, const type* y);
#define DEFINE_GT(type) \
    char gt_##type(const type* x, const type* y);
#define DEFINE_LT(type) \
    char lt_##type(const type* x, const type* y);

#define IMPL_EQ(type) \
    char eq_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] != b[i]) return 0; \
        } \
        return 1;  \
    }

#define IMPL_GT(type) \
    char gt_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] >  b[i]) return 1; \
            if (a[i] <  b[i]) return 0; \
        } \
        return 0;  \
    }

#define IMPL_LT(type) \
    char lt_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] >  b[i]) return 0; \
            if (a[i] <  b[i]) return 1; \
        } \
        return 0;  \
    }

#define _IMPL_CMP(type) \
    Compareable cmp_##type(const type* x, const type* y) { \
        size_t size = sizeof(type); \
        uchar* a = (uchar*) x; \
        uchar* b = (uchar*) y; \
        for (size_t i = 0; i < size ;i++) { \
            if (a[i] >  b[i]) return GREATER; \
            if (a[i] <  b[i]) return LESS; \
        } \
        return EQUAL;  \
    }

#define _IMPL_PRIM_CMP(type) \
    Compareable cmp_##type(const type* x, const type* y) { \
        if (*x > *y) return GREATER; \
        else if (*x < *y) return LESS; \
        else return EQUAL; \
    }

#define _IMPL_PRIM_EQ(type) \
    char eq_##type(const type* x, const type* y) { \
        return (*x == *y);  \
    }
#define _IMPL_PRIM_LT(type) \
    char gt_##type(const type* x, const type* y) { \
        return (*x  < *y);  \
    }
#define _IMPL_PRIM_GT(type) \
    char lt_##type(const type* x, const type* y) { \
        return (*x  > *y);  \
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
