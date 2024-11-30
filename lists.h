#include <stdint.h>
#include <stdlib.h>
#include "default_types.h"
#include "result.h"
#include "rmath.h"
#include "cmp.h"
#include "color_print.h"

#ifndef DEFINE_DLlist
#define DEFINE_DLlist

#define _LL_DEF_NEW(t) \
    t##Ll new_##t##Ll(void);

#define _LL_IMPL_NEW(t) \
    t##Ll new_##t##Ll(void) { \
        t##Ll ans = {NULL, NULL, 0}; \
        return ans; \
    }

#define _LL_DEF_FREE(t) \
    void free_##t##Ll(t##Ll list);

#define _LL_IMPL_FREE(t) \
    void free_##t##Ll(t##Ll list) { \
        while (list.count > 0) { \
            list = rem_##t##Ll(list, 0).result; \
        } \
    }

#define _LL_DEF_APPEND(t) \
    t##LlRes append_##t##Ll(t##Ll list, const t elem);

#define _LL_IMPL_APPEND(t) \
    t##LlRes append_##t##Ll(t##Ll list, const t elem) { \
        t##LlRes ans = {FAILURE, list}; \
        t##LlNode* e = (t##LlNode*) malloc(sizeof(t##LlNode)); \
        if (e == NULL) return ans; \
        if (list.count == 0) { \
            list.last = e; \
            list.first = e; \
        } else { \
            e->val = elem; \
            e->prev = list.last; \
            e->next = list.first; \
            list.last->next = e; \
            list.first->prev = e; \
            list.last = e; \
        } \
        e->val = elem; \
        list.count++; \
        ans.result = list; \
        ans.type = SUCCESS; \
        return ans; \
    }

#define _LL_DEF_PREPEND(t) \
    t##LlRes prepend_##t##Ll(t##Ll list, const t elem);

#define _LL_IMPL_PREPEND(t) \
    t##LlRes prepend_##t##Ll(t##Ll list, const t elem) { \
        t##LlRes ans = {FAILURE, list}; \
        t##LlNode* e = (t##LlNode*) malloc(sizeof(t##LlNode)); \
        if (e == NULL) return ans; \
        if (list.count == 0) { \
            list.last = e; \
            list.first = e; \
        } else { \
            e->val = elem; \
            e->prev = list.last; \
            e->next = list.first; \
            list.last->next = e; \
            list.first->prev = e; \
            list.first = e; \
        } \
        e->val = elem; \
        list.count++; \
        ans.result = list; \
        ans.type = SUCCESS; \
        return ans; \
    }

#define _LL_DEF_GET(t) \
    t##Res get_##t##Ll(t##Ll list, llong i);

#define _LL_IMPL_GET(t) \
    t##Res get_##t##Ll(const t##Ll list, const llong i) { \
        t##Res ans = {0}; \
        ans.type = FAILURE; \
        llong max_i = (llong) save_sub(list.count, 1); \
        if (i > max_i || i+1 < -max_i || list.count == 0) return ans; \
        t##LlNode* res = list.first; \
        llong pos = i; \
        while (pos != 0) { \
            if (pos > 0) { \
                res = res->next; \
                pos--; \
            } else { \
                res = res->prev; \
                pos++; \
            } \
        } \
        ans.result = res->val; \
        ans.type = SUCCESS; \
        return ans; \
    }

#define _LL_DEF_DEL(t) \
    voidRes del_##t##Ll(t##Ll list, t elem);

#define _LL_IMPL_DEL(t) \
    voidRes del_##t##Ll(t##Ll list, const t elem) { \
        voidRes ans = {FAILURE}; \
        t##LlNode* cur = list.first; \
        for (size_t i = 0; i < list.count; i++) { \
            if (eq_##t(cur->val, elem)) { \
                ans.type = SUCCESS; \
                cur->prev->next = cur->next; \
                cur->next->prev = cur->prev; \
                return ans; \
            } else { \
                cur = cur->next; \
            } \
        } \
        return ans; \
    }

#define _LL_DEF_REM(t) \
    t##LlRes rem_##t##Ll(t##Ll list, llong i);

#define _LL_IMPL_REM(t) \
    t##LlRes rem_##t##Ll(t##Ll list, const llong i) { \
        t##LlRes ans = {FAILURE, list}; \
        llong max_i = (llong) save_sub(list.count, 1); \
        if (i > max_i || i+1 < -max_i || list.count == 0) return ans; \
        if (list.count == 1) { \
            t##LlNode* cur = list.first; \
            free(cur); \
            list.first = NULL; \
            list.last = NULL; \
        } else { \
            t##LlNode* cur = list.first; \
            llong pos = i; \
            while (pos != 0) { \
                if (pos > 0) { \
                    cur = cur->next; \
                    pos--; \
                } else { \
                    cur = cur->prev; \
                    pos++; \
                } \
            } \
            cur->prev->next = cur->next; \
            cur->next->prev = cur->prev; \
            if (list.first == cur) {list.first = cur->next;}; \
            if (list.last  == cur) {list.last  = cur->prev;}; \
            free(cur); \
        } \
        ans.type = SUCCESS; \
        list.count -= 1; \
        ans.result = list; \
        return ans; \
    } \

#define DEFINE_LL(t) \
    typedef struct _##t##_node { \
        t val; \
        struct _##t##_node * prev; \
        struct _##t##_node * next; \
    } t##LlNode; \
    typedef struct { \
        t##LlNode* first; \
        t##LlNode* last; \
        size_t count; \
    } t##Ll; \
    DEFINE_RESULT(t##Ll); \
    _LL_DEF_NEW(t) \
    _LL_DEF_FREE(t) \
    _LL_DEF_APPEND(t) \
    _LL_DEF_PREPEND(t) \
    _LL_DEF_GET(t) \
    _LL_DEF_DEL(t) \
    _LL_DEF_REM(t)

DEFAULT_TYPES(DEFINE_LL);
MATH_TYPES(DEFINE_LL);

#define IMPL_LL(t) \
    _LL_IMPL_NEW(t) \
    _LL_IMPL_FREE(t) \
    _LL_IMPL_APPEND(t) \
    _LL_IMPL_PREPEND(t) \
    _LL_IMPL_GET(t) \
    _LL_IMPL_DEL(t) \
    _LL_IMPL_REM(t)

#endif
