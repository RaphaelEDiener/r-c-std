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

#define _VEC_DEF_VEC2(type) \
    typedef struct { \
        type x; \
        type y; \
    } type##Vec2; 
#define _VEC_DEF_VEC3(type) \
    typedef struct { \
        type x; \
        type y; \
        type z; \
    } type##Vec3; 
#define _VEC_DEF_VEC4(type) \
    typedef struct { \
        type x; \
        type y; \
        type z; \
        type w; \
    } type##Vec4; 

#define _VEC_DEF_ADD(type) \
    type##Vec2 add_##type##Vec2(const type##Vec2* a, const type##Vec2* b); \
    type##Vec3 add_##type##Vec3(const type##Vec3* a, const type##Vec3* b); \
    type##Vec4 add_##type##Vec4(const type##Vec4* a, const type##Vec4* b);

#define _VEC_IMPL_ADD(type) \
    type##Vec2 add_##type##Vec2(const type##Vec2* a, const type##Vec2* b) { \
        type##Vec2 ans = {a->x + b->x, a->y + b->y}; \
        return ans; \
    } \
    type##Vec3 add_##type##Vec3(const type##Vec3* a, const type##Vec3* b) { \
        type##Vec3 ans = {a->x + b->x, a->y + b->y, a->z + b->z}; \
        return ans; \
    } \
    type##Vec4 add_##type##Vec4(const type##Vec4* a, const type##Vec4* b) { \
        type##Vec4 ans = {a->x + b->x, a->y + b->y, a->z + b->z, a->w + b->w}; \
        return ans; \
    };

#define _VEC_DEF_SUB(type) \
    type##Vec2 sub_##type##Vec2(const type##Vec2* a, const type##Vec2* b); \
    type##Vec3 sub_##type##Vec3(const type##Vec3* a, const type##Vec3* b); \
    type##Vec4 sub_##type##Vec4(const type##Vec4* a, const type##Vec4* b);

#define _VEC_IMPL_SUB(type) \
    type##Vec2 sub_##type##Vec2(const type##Vec2* a, const type##Vec2* b) { \
        type##Vec2 ans = {a->x - b->x, a->y - b->y}; \
        return ans; \
    } \
    type##Vec3 sub_##type##Vec3(const type##Vec3* a, const type##Vec3* b) { \
        type##Vec3 ans = {a->x - b->x, a->y - b->y, a->z - b->z}; \
        return ans; \
    } \
    type##Vec4 sub_##type##Vec4(const type##Vec4* a, const type##Vec4* b) { \
        type##Vec4 ans = {a->x - b->x, a->y - b->y, a->z - b->z, a->w - b->w}; \
        return ans; \
    };

#define _VEC_DEF_MUL(type) \
    type##Vec2 mul_##type##Vec2(const type##Vec2* a, const type##Vec2* b); \
    type##Vec3 mul_##type##Vec3(const type##Vec3* a, const type##Vec3* b); \
    type##Vec4 mul_##type##Vec4(const type##Vec4* a, const type##Vec4* b);

#define _VEC_IMPL_MUL(type) \
    type##Vec2 mul_##type##Vec2(const type##Vec2* a, const type##Vec2* b) { \
        type##Vec2 ans = {a->x * b->x, a->y * b->y}; \
        return ans; \
    } \
    type##Vec3 mul_##type##Vec3(const type##Vec3* a, const type##Vec3* b) { \
        type##Vec3 ans = {a->x * b->x, a->y * b->y, a->z * b->z}; \
        return ans; \
    } \
    type##Vec4 mul_##type##Vec4(const type##Vec4* a, const type##Vec4* b) { \
        type##Vec4 ans = {a->x * b->x, a->y * b->y, a->z * b->z, a->w * b->w}; \
        return ans; \
    };

#define _VEC_DEF_DIV(type) \
    type##Vec2 div_##type##Vec2(const type##Vec2* a, const type##Vec2* b); \
    type##Vec3 div_##type##Vec3(const type##Vec3* a, const type##Vec3* b); \
    type##Vec4 div_##type##Vec4(const type##Vec4* a, const type##Vec4* b);

#define _VEC_IMPL_DIV(type) \
    type##Vec2 div_##type##Vec2(const type##Vec2* a, const type##Vec2* b) { \
        type##Vec2 ans = {a->x / b->x, a->y / b->y}; \
        return ans; \
    } \
    type##Vec3 div_##type##Vec3(const type##Vec3* a, const type##Vec3* b) { \
        type##Vec3 ans = {a->x / b->x, a->y / b->y, a->z / b->z}; \
        return ans; \
    } \
    type##Vec4 div_##type##Vec4(const type##Vec4* a, const type##Vec4* b) { \
        type##Vec4 ans = {a->x / b->x, a->y / b->y, a->z / b->z, a->w / b->w}; \
        return ans; \
    };

#define DEFINE_VEC(type) \
    _VEC_DEF_VEC2(type) \
    _VEC_DEF_VEC3(type) \
    _VEC_DEF_VEC4(type) \
    _VEC_DEF_ADD(type) \
    _VEC_DEF_MUL(type) \
    _VEC_DEF_DIV(type) \
    _VEC_DEF_SUB(type)

#define IMPL_VEC(type) \
    _VEC_IMPL_ADD(type) \
    _VEC_IMPL_MUL(type) \
    _VEC_IMPL_DIV(type) \
    _VEC_IMPL_SUB(type)

DEFAULT_TYPES(DEFINE_VEC);

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
