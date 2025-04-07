/**
 * Testing functions 
 *
 * All test functions return 1 for failing, and 0 for success.
 * Asserts are functions by defautl so the compiler works fast.
 * The optimizing compilers 
 * can eliminate the dead code from dead functions.
 * This is faster than the preprocessor.
 * The asserts are comiling slow because preprocessor.
 */

#include "default_types.h"
#include "cmp.h"
#include "result.h" 
#include <stdlib.h> 

#ifndef TEST_SIGNATURES
#define TEST_SIGNATURES

typedef char  (*truthy)   (const void*, const void*);
typedef char* (*stringify)(const void*);

char test_costume(
    const void* real, 
    const void* expected, 
    const truthy equals, 
    const stringify to_str, 
    const char* message
);

char test_eq(
    const void* real, 
    const void* expected, 
    const char* message
);

#if defined(RELEASE)
    void w_assert(const char truthy, const char* msg);
    void e_assert(const char truthy, const char* msg);
#elif defined(DEBUG)
    #define e_assert(truthy, msg) \
    if (!(truthy)) { \
        redln( \
            "Assert\n\t%s\nfailed in %s @ line %u:\n\t%s",  \
            #truthy, \
            __FILE__, __LINE__, \
            msg \
        ) \
        err_redln( \
            "Assert\n\t%s\nfailed in %s @ line %u:\n\t%s",  \
            #truthy, \
            __FILE__, __LINE__, \
            msg \
        ) \
        exit(-1); \
    }
    #define w_assert(truthy, msg) \
    if (!(truthy)) { \
        err_yellowln( \
            "Assert\n\t%s\nfailed in %s @ line %u:\n\t%s",  \
            #truthy, \
            __FILE__, __LINE__, \
            msg \
        ) \
    }
#else 
    void w_assert(const char truthy, const char* msg);
    void e_assert(const char truthy, const char* msg);
#endif

#define DEFINE_TEST_SIG(type) \
    char test_##type(const type real, const type expected, const char* message);

DEFAULT_TYPES(DEFINE_TEST_SIG);
DEFINE_TEST_SIG(Compareable)
DEFINE_TEST_SIG(ResultType)

#endif

