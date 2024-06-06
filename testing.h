/**
 * Testing functions 
 *
 * All test functions return 1 for failing, and 0 for success
 */

#include "default_types.h"
#include "cmp.h"
#include "result.h" 

#ifndef TEST_SIGNATURES
#define TEST_SIGNATURES

typedef char (*truthy)(const void*, const void*);
typedef char* (*stringify)(const void*);

char test_costume(
    const void* real, 
    const void* expected, 
    const truthy equals, 
    const stringify to_str, 
    const char* message
);

#define DEFINE_TEST_SIG(type) \
    char test_##type(const type real, const type expected, const char* message);

DEFAULT_TYPES(DEFINE_TEST_SIG);
DEFINE_TEST_SIG(Compareable)
DEFINE_TEST_SIG(ResultType)

#endif

