/**
 * TODO: linked lists
 * TODO: document
 */
#include <stdint.h>
#include <stdlib.h>
#include "default_types.h"
#include "result.h"
#include "rmath.h"

#ifndef DEFINE_DLList
#define DEFINE_DLList(type) \
    typedef struct _##type##_node { \
        type val; \
        struct _##type##_node * prev; \
        struct _##type##_node * next; \
    } type##LLNode; \
    typedef struct { \
        type##LLNode* first; \
        type##LLNode* last; \
        size_t len; \
    } type##LL; \
    size_tRes append_##type##LL(type##LL list, type elem); \
    size_tRes prepend_##type##LL(type##LL list, type elem); \
    type##Res get_##type##LL(type##LL list, long i);

DEFAULT_TYPES(DEFINE_DLList);


#define IMPL_DLList(t) \
    size_tRes append_##t##LL(t##LL list, t elem) { \
        size_tRes ans = {FAILURE, list.len}; \
        if (list.len == SIZE_MAX) return ans; \
        t##LLNode* e = (t##LLNode*) malloc(sizeof(t##LLNode)); \
        e->prev = list.last; \
        e->next = list.first; \
        list.last->next = e; \
        list.first->prev = e; \
        list.last = e; \
        list.len++; \
        ans.type = SUCCESS; \
        return ans; \
    } \
    size_tRes prepend_##t##LL(t##LL list, t elem) { \
        size_tRes ans = {FAILURE, 0}; \
        if (list.len == SIZE_MAX) return ans; \
        t##LLNode* e = (t##LLNode*) malloc(sizeof(t##LLNode)); \
        e->prev = list.last; \
        e->next = list.first; \
        list.last->next = e; \
        list.first->prev = e; \
        list.first = e; \
        list.len++; \
        ans.type = SUCCESS; \
        return ans; \
    } \
    t##Res get_##t##LL(t##LL list, long i) { \
        t##Res ans = {FAILURE, 0}; \
        size_t target = save_sub(list.len,1); \
        if (i > target || -i > target || list.len == 0) return ans; \
        t##LLNode* res = list.first; \
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
        return ans; \
    } \
    voidRes del_##t##LL(t##LL list, t elem) { \
        voidRes ans = {FAILURE}; \
        t##LLNode* cur = list.first; \
        for (size_t i = 0; i < list.len; i++) { \
            if (cur->val == elem) { \
                ans.type = SUCCESS; \
                cur->prev->next = cur->next; \
                cur->next->prev = cur->prev; \
                return ans; \
            } \
        } \
        return ans; \
    }
#endif
