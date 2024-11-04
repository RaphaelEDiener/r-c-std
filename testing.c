/**
* implementation of testing function
*/
#include <stdio.h>
#include "testing.h"


char test_costume(const void* real, const void* expected, const truthy equals, const stringify to_str, const char* message){
    if (equals(real, expected)) {
        // printf("\x1B[32m%s\x1B[0m\n", message);
        return 0;
    } else {
        printf("\x1B[31mexpected: %s\nreceived: %s\n%s\x1B[0m\n", to_str(expected), to_str(real), message);
        return 1;
    }  
}

#define DEFINE_TEST_INT(type) \
    char test_##type(const type real, const type expected, const char* message){ \
        if (real == expected) { \
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
            return 0; \
        } else { \
            printf("\x1B[31mexpected: %lld\nreceived: %lld\n%s\x1B[0m\n", expected, real, message); \
            return 1; \
        } \
    }

DEFINE_TEST_LONG_LONG(llong)
DEFINE_TEST_LONG_LONG(ullong)

#define DEFINE_TEST_SHORT(type) \
    char test_##type(const type real, const type expected, const char* message){ \
        if (real == expected) { \
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
        return 0; 
    } else { 
        printf("\x1B[31mexpected: %f\nreceived: %f\n%s\x1B[0m\n", expected, real, message); 
        return 1; 
    } 
}

char test_double(const double real, const double expected, const char* message){ 
    double diff = real - expected; 
    if (-0.00000001 <= diff && diff <= 0.00000001) { 
        return 0; 
    } else { 
        printf("\x1B[31mexpected: %f\nreceived: %f\n%s\x1B[0m\n", expected, real, message); 
        return 1; 
    } 
}

char test_long_double(const ldouble real, const ldouble expected, const char* message){ 
    ldouble diff = real - expected; 
    if (-0.00000001 <= diff && diff <= 0.00000001) { 
        return 0; 
    } else { 
        printf("\x1B[31mexpected: %Lf\nreceived: %Lf\n%s\x1B[0m\n", expected, real, message); 
        return 1; 
    } 
}

char test_Compareable(const Compareable real, const Compareable expected, const char* message) {
    if (real == expected) {
        return 0; 
    } else {
        char* exp_s  = expected == LESS ? "LESS" : (expected == EQUAL) ? "EQUAL" : "GREATER";
        char* real_s = real     == LESS ? "LESS" : (real     == EQUAL) ? "EQUAL" : "GREATER";
        printf("\x1B[31mexpected: %s\nreceived: %s\n%s\x1B[0m\n", exp_s, real_s, message); 
        return 1; 
    }
}

char test_size_t(const size_t real, const size_t expected, const char* message) {
    if (real == expected) {
        return 0; 
    } else {
        printf("\x1B[31mexpected: %zu\nreceived: %zu\n%s\x1B[0m\n", expected, real, message); 
        return 1; 
    }
}

char test_ResultType(const ResultType real, const ResultType expected, const char* message) {
    if (real == expected) {
        return 0; 
    } else {
        char* exp_s  = expected == SUCCESS ? "SUCCESS" : "FAILURE";
        char* real_s = real     == SUCCESS ? "SUCCESS" : "FAILURE";
        printf("\x1B[31mexpected: %s\nreceived: %s\n%s\x1B[0m\n", exp_s, real_s, message); 
        return 1; 
    }
}
