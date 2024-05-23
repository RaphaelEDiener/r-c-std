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

#define DEFINE_TEST_LONG(type) \
    char test_##type(const type real, const type expected, const char* message){ \
        if (real == expected) { \
            printf("\x1B[32m%s\x1B[0m\n", message); \
            return 0; \
        } else { \
            printf("\x1B[31mexpected: %ld\nreceived: %ld\n%s\x1B[0m\n", expected, real, message); \
            return 1; \
        } \
    }

DEFINE_TEST_LONG(long)
DEFINE_TEST_LONG(ulong)

#define DEFINE_TEST_LONG_LONG(type) \
    char test_##type(const type real, const type expected, const char* message){ \
        if (real == expected) { \
            printf("\x1B[32m%s\x1B[0m\n", message); \
            return 0; \
        } else { \
            printf("\x1B[31mexpected: %lld\nreceived: %lld\n%s\x1B[0m\n", expected, real, message); \
            return 1; \
        } \
    }

DEFINE_TEST_LONG_LONG(long_long)
DEFINE_TEST_LONG_LONG(ulong_long)

#define DEFINE_TEST_SHORT(type) \
    char test_##type(const type real, const type expected, const char* message){ \
        if (real == expected) { \
            printf("\x1B[32m%s\x1B[0m\n", message); \
            return 0; \
        } else { \
            printf("\x1B[31mexpected: %hd\nreceived: %hd\n%s\x1B[0m\n", expected, real, message); \
            return 1; \
        } \
    }

DEFINE_TEST_SHORT(short)
DEFINE_TEST_SHORT(ushort)

#define DEFINE_TEST_CHAR(type) \
    char test_##type(const type real, const type expected, const char* message){ \
        if (real == expected) { \
            printf("\x1B[32m%s\x1B[0m\n", message); \
            return 0; \
        } else { \
            printf("\x1B[31mexpected: %d\nreceived: %d\n%s\x1B[0m\n", expected, real, message); \
            return 1; \
        } \
    }

DEFINE_TEST_CHAR(char)
DEFINE_TEST_CHAR(uchar)
DEFINE_TEST_CHAR(schar);

char test_float(const float real, const float expected, const char* message){ 
    float diff = real - expected; 
    if (-0.0001 <= diff && diff <= 0.0001) { 
        printf("\x1B[32m%s\x1B[0m\n", message); 
        return 0; 
    } else { 
        printf("\x1B[31mexpected: %f\nreceived: %f\n%s\x1B[0m\n", expected, real, message); 
        return 1; 
    } 
}

char test_double(const double real, const double expected, const char* message){ 
    double diff = real - expected; 
    if (-0.00000001 <= diff && diff <= 0.00000001) { 
        printf("\x1B[32m%s\x1B[0m\n", message); 
        return 0; 
    } else { 
        printf("\x1B[31mexpected: %f\nreceived: %f\n%s\x1B[0m\n", expected, real, message); 
        return 1; 
    } 
}

char test_long_double(const long_double real, const long_double expected, const char* message){ 
    long_double diff = real - expected; 
    if (-0.00000001 <= diff && diff <= 0.00000001) { 
        printf("\x1B[32m%s\x1B[0m\n", message); 
        return 0; 
    } else { 
        printf("\x1B[31mexpected: %Lf\nreceived: %Lf\n%s\x1B[0m\n", expected, real, message); 
        return 1; 
    } 
}

