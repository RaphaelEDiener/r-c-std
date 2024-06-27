#include <stdint.h>
#include <stdlib.h>
#include "default_types.h"
#include "result.h"
#include "rmath.h"
#include "rmath.h"
#include "color_print.h"

#ifndef DEFINE_DLlist
#define DEFINE_DLlist(type) \
    typedef struct _##type##_node { \
        type val; \
        struct _##type##_node * prev; \
        struct _##type##_node * next; \
    } type##LlNode; \
    typedef struct { \
        type##LlNode* first; \
        type##LlNode* last; \
        size_t count; \
    } type##Ll; \
    DEFINE_RESULT(type##Ll); \
    type##Ll new_##type##Ll(void); \
    type##LlRes append_##type##Ll(type##Ll list, const type elem); \
    type##LlRes prepend_##type##Ll(type##Ll list, const type elem); \
    type##Res get_##type##Ll(type##Ll list, long long i); \
    voidRes del_##type##Ll(type##Ll list, type elem); \
    void free_##type##Ll(type##Ll list); \
    type##LlRes rem_##type##Ll(type##Ll list, long long i);

DEFAULT_TYPES(DEFINE_DLlist);

#define IMPL_DLlist(t) \
    t##Ll new_##t##Ll(void) { \
        t##Ll ans = {NULL, NULL, 0}; \
        return ans; \
    } \
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
    } \
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
    } \
    t##Res get_##t##Ll(t##Ll list, long long i) { \
        t##Res ans = {FAILURE, 0}; \
        long long max_i = (long long) save_sub(list.count, 1); \
        if (i > max_i || i+1 < -max_i || list.count == 0) return ans; \
        t##LlNode* res = list.first; \
        while (i != 0) { \
            if (i > 0) { \
                res = res->next; \
                i--; \
            } else { \
                res = res->prev; \
                i++; \
            } \
        } \
        ans.result = res->val; \
        ans.type = SUCCESS; \
        return ans; \
    } \
    voidRes del_##t##Ll(t##Ll list, t elem) { \
        voidRes ans = {FAILURE}; \
        t##LlNode* cur = list.first; \
        for (size_t i = 0; i < list.count; i++) { \
            if (cur->val == elem) { \
                ans.type = SUCCESS; \
                cur->prev->next = cur->next; \
                cur->next->prev = cur->prev; \
                return ans; \
            } else { \
                cur = cur->next; \
            } \
        } \
        return ans; \
    } \
    t##LlRes rem_##t##Ll(t##Ll list, long long i) { \
        t##LlRes ans = {FAILURE, list}; \
        long long max_i = (long long) save_sub(list.count, 1); \
        if (i > max_i || i+1 < -max_i || list.count == 0) return ans; \
        if (list.count == 1) { \
            t##LlNode* res = list.first; \
            list.first = NULL; \
            list.last = NULL; \
            free(res); \
        } else { \
            t##LlNode* cur = list.first; \
            while (i != 0) { \
                if (i > 0) { \
                    cur = cur->next; \
                    i--; \
                } else { \
                    cur = cur->prev; \
                    i++; \
                } \
            } \
            cur->prev->next = cur->next; \
            cur->next->prev = cur->prev; \
            if (list.first == cur) {list.first = cur->next;}; \
            if (list.last == cur) {list.last = cur->prev;}; \
            free(cur); \
        } \
        ans.type = SUCCESS; \
        ans.result.count--; \
        return ans; \
    } \
    void free_##t##Ll(t##Ll list) { \
        while (list.count > 0) { \
            list = rem_##t##Ll(list, 0).result; \
        } \
    }

#endif
