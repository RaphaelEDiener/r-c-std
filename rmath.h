#include <stdint.h>
#include <stddef.h>
#include "default_types.h"

#ifndef RMATH
#define RMATH
void swap(uchar* p1, uchar* p2);

size_t save_sub(size_t x, size_t y);
size_t save_add(size_t x, size_t y);

// TODO: document vecs and mats
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
