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
    Compareable cmp_##type(type* x, type* y);

#define _IMPL_PRIM_CMP(type) \
    Compareable cmp_##type(type* x, type* y) { \
        if (*x > *y) return GREATER; \
        else if (*x < *y) return LESS; \
        else return EQUAL; \
    }

DEFAULT_TYPES(DEFINE_CMP);

#endif
