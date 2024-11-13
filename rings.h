#ifndef DEFINE_RING

#define _RING_DEFINE_TYPES(type) \
    typedef struct { \
        size_t capacity; \
        size_t front; \
        size_t back; \
        type* ptr; \
    } type##Ring; \

#define _R_DEF_NEW(t) \
    t##RingRes new_##t##Ring(const size_t capacity);

#define _R_IMPL_NEW(t) \
    t##RingRes new_##t##Ring(const size_t capacity) { \
        t##Ring ans = {capacity, sizeof(t), 0, (t*) calloc(capacity, sizeof(t))}; \
        t##DaRes res = {FAILURE, ans}; \
        if (ans.ptr == NULL) { \
            err_redln("failed to allocated for with capacity of %zu", capacity); \
            return res; \
        } \
        else { \
        res.type = SUCCESS; \
        return res; \
        } \
    }

#endif
