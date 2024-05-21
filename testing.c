/**
* implementation of testing function
*/
#include <stdio.h>
#include "testing.h"
#include "default_types.h"

// char
// signed_char
// uchar
// short
// ushort
// int
// uint
// long
// ulong
// long_long
// ulong_long
// float
// double
// long_double

char test_costume(const void* real, const void* expected, const truthy equals, const stringify to_str, const char* message){
    if (equals(real, expected)) {
        printf("\x1B[32m%s\x1B[0m\n", message);
        return 0;
    } else {
        printf("\x1B[31mexpected: %s\nreceived: %s\n%s\x1B[0m\n", to_str(expected), to_str(real), message);
        return 1;
    }  
}

#define DEFINE_TEST_INT(type) \
        char test_##type(const type real, const type expected, const char* message){ \
        if (real == expected) { \
            printf("\x1B[32m%s\x1B[0m\n", message); \
            return 0; \
        } else { \
            printf("\x1B[31mexpected: %d\nreceived: %d\n%s\x1B[0m\n", expected, real, message); \
            return 1; \
        } \
    }

DEFINE_TEST_INT(int)
DEFINE_TEST_INT(uint)

char test_char(const char real, const char expected, const char* message){
    if (real == expected) {
        printf("\x1B[32m%s\x1B[0m\n", message);
        return 0;
    } else {
        printf("\x1B[31mexpected: %d\nreceived: %d\n%s\x1B[0m\n", expected, real, message);
        return 1;
    }  
}
