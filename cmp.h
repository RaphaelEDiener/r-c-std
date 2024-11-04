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

#define DEFINE_CMP(type) \
    Compareable cmp_##type(const type* x, const type* y);

#define DEFINE_EQ(type) \
    char eq_##type(const type* x, const type* y);
#define DEFINE_GT(type) \
    char gt_##type(const type* x, const type* y);
#define DEFINE_LT(type) \
    char lt_##type(const type* x, const type* y);

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

DEFAULT_TYPES(DEFINE_CMP);
DEFAULT_TYPES(DEFINE_EQ);
DEFAULT_TYPES(DEFINE_GT);
DEFAULT_TYPES(DEFINE_LT);

#endif
