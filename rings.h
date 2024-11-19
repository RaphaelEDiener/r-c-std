#include "default_types.h"
#include "result.h"
#include "rmath.h"
#include "color_print.h"

#ifndef DEFINE_RING

/*
 * front pointer is always pointing to the next insert element.
 * back pointer is always pointing to a valid element or is equal front pointer.
 */

#define _RING_DEFINE_TYPES(type) \
    typedef struct { \
        size_t capacity; \
        size_t front; \
        size_t back; \
        type* ptr; \
    } type##Ring; \
    DEFINE_RESULT(type##Ring); 

#define _R_DEF_NEW(t) \
    t##RingRes new_##t##Ring(const size_t capacity);

// potential overflow caught by the capacity check
#define _R_IMPL_NEW(t) \
    t##RingRes new_##t##Ring(const size_t capacity) { \
        t##Ring ans = {capacity, 0, capacity - 1, (t*) calloc(capacity, sizeof(t))}; \
        t##RingRes res = {FAILURE, ans}; \
        if (capacity < 2) { \
            err_redln( \
                "Rings of capacity %zu are to small to exist meaningfully (expected > 2)",  \
                capacity \
            ); \
            return res; \
        } \
        if (ans.ptr == NULL) { \
            err_redln("failed to allocated for with capacity of %zu", capacity); \
            return res; \
        } \
        else { \
        res.type = SUCCESS; \
        return res; \
        } \
    }

#define _R_DEF_INSERT(t) \
    t##Ring insert_##t##Ring(t##Ring ring, t val);

#define _R_IMPL_INSERT(t) \
    t##Ring insert_##t##Ring(t##Ring ring, t val) { \
        ring.ptr[ring.front] = val; \
        ring.front = (ring.front + 1) % ring.capacity; \
        if (ring.front == ring.back) { \
            ring.back = (ring.back + 1) % ring.capacity; \
        } \
        return ring; \
    }

#define _R_DEF_SAVE_INSERT(t) \
    t##RingRes sinsert_##t##Ring(t##Ring ring, t val);

#define _R_IMPL_SAVE_INSERT(t) \
    t##RingRes sinsert_##t##Ring(t##Ring ring, t val) { \
        if (ring.back == (ring.front + 1) % ring.capacity) { \
            t##RingRes res = {FAILURE, ring}; \
            return res; \
        } else { \
            ring.ptr[ring.front] = val; \
            ring.front = (ring.front + 1) % ring.capacity; \
            t##RingRes res = {SUCCESS, ring}; \
            return res; \
        } \
    }

#define _R_DEF_PEAK(t) \
    t##Res peak_##t##Ring(const t##Ring ring);

#define _R_IMPL_PEAK(t) \
    t##Res peak_##t##Ring(const t##Ring ring) { \
        if (ring.front == ring.back) { \
            t##Res res = {FAILURE, ring.ptr[0]}; \
            return res; \
        } else { \
            t##Res res = {SUCCESS, ring.ptr[ring.back]}; \
            return res; \
        } \
    }

#define _R_DEF_POP(t) \
    t##RingRes pop_##t##Ring(t##Ring ring);

#define _R_IMPL_POP(t) \
    t##RingRes pop_##t##Ring(t##Ring ring) { \
        if (ring.front == ring.back) { \
            t##RingRes res = {FAILURE, ring}; \
            return res; \
        } else { \
            ring.back = (ring.back + 1) % ring.capacity; \
            t##RingRes res = {SUCCESS, ring}; \
            return res; \
        } \
    }

#define _R_DEF_COUNT(t) \
    size_t count_##t##Ring(const t##Ring ring);

#define _R_IMPL_COUNT(t) \
    size_t count_##t##Ring(const t##Ring ring) { \
        if (ring.front >= ring.back) { \
            return ring.front - ring.back; \
        } else { \
            return ring.front + ring.capacity - ring.back; \
        } \
    }

#define DEFINE_RING(type) \
    _RING_DEFINE_TYPES(type) \
    _R_DEF_NEW(type) \
    _R_DEF_INSERT(type) \
    _R_DEF_SAVE_INSERT(type) \
    _R_DEF_PEAK(type) \
    _R_DEF_POP(type) \
    _R_DEF_COUNT(type) \


#define IMPL_RING(type) \
    _R_IMPL_NEW(type) \
    _R_IMPL_INSERT(type) \
    _R_IMPL_SAVE_INSERT(type) \
    _R_IMPL_PEAK(type) \
    _R_IMPL_POP(type) \
    _R_IMPL_COUNT(type) \


DEFAULT_TYPES(DEFINE_RING);
MATH_TYPES(DEFINE_RING);

#endif
