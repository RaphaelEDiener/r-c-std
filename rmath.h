#include <stdint.h>
#include <stddef.h>
#include "default_types.h"
// #include "iterator.h"

#ifndef RMATH
#define RMATH
void swap(uchar* p1, uchar* p2);

#define DEFINE_SWAP(type) \
    void swap_##type(type* ptr1, type* ptr2);

#define IMPL_SWAP(type) \
    void swap_##type(type* ptr1, type* ptr2) { \
        uchar* p1 = (uchar*) ptr1; \
        uchar* p2 = (uchar*) ptr2; \
        for (size_t i = 0; i < sizeof(type); i++) { \
            swap(p1+i, p2+i); \
        } \
    }

DEFAULT_TYPES(DEFINE_SWAP)

size_t save_sub(size_t x, size_t y);
size_t save_add(size_t x, size_t y);

#define DEFINE_VEC2(type) \
    typedef struct { \
        type x; \
        type y; \
    } type##Vec2; 
#define DEFINE_VEC3(type) \
    typedef struct { \
        type x; \
        type y; \
        type z; \
    } type##Vec3; 
#define DEFINE_VEC4(type) \
    typedef struct { \
        type x; \
        type y; \
        type z; \
        type w; \
    } type##Vec4; 

DEFAULT_TYPES(DEFINE_VEC2);
DEFAULT_TYPES(DEFINE_VEC3);
DEFAULT_TYPES(DEFINE_VEC4);

#define DEFINE_MATRIX2(type) \
    typedef struct { \
        type* ptr; \
        size_t x; \
        size_t y; \
    } type##Mat2;
#define DEFINE_MATRIX3(type) \
    typedef struct { \
        type* ptr; \
        size_t x; \
        size_t y; \
        size_t z; \
    } type##Mat3;
#define DEFINE_MATRIX4(type) \
    typedef struct { \
        type* ptr; \
        size_t x; \
        size_t y; \
        size_t z; \
        size_t w; \
    } type##Mat4;

DEFAULT_TYPES(DEFINE_MATRIX2);
DEFAULT_TYPES(DEFINE_MATRIX3);
DEFAULT_TYPES(DEFINE_MATRIX4);

#endif
