/*
 * Option Data Type since I'm a monad guy
 */
#include "default_types.h"

#ifndef RESULT
#define RESULT
typedef enum {
    SUCCESS,
    FAILURE
} ResultType;

#define DEFINE_RESULT(t) \
    typedef struct { \
        ResultType type; \
        t result; \
    } t##Res;

DEFAULT_TYPES(DEFINE_RESULT)

typedef struct {
    ResultType type;
} voidRes;

#endif
