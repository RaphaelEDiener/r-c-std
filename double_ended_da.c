#include "double_ended_da.h"
#include "array_utils.h"

intDdaRes new_intDda(const size_t capacity) { 
    intDda ans = {
        capacity, 
        sizeof(t), 
        capacity / 2, 
        capacity / 2, 
        (t*) calloc(capacity, sizeof(t))
    }; 
    intDdaRes res = {FAILURE, ans}; 
    if (ans.ptr == NULL) { 
        err_redln("failed to allocated for with capacity of %zu", capacity); 
        return res; 
    } 
    else { 
        res.type = SUCCESS; 
        return res; 
    } 
}
size_t count_intDda(intDda arr) {
    return arr.back_i - arr.front_i;
}

intDdaRes append_intDda(const intdDa arr, const type elem) { 
    intDda new_arr = {arr.capacity, sizeof(int), arr.front_i, arr.back_i, arr.ptr}; 
    intDdaRes ans = {FAILURE, arr}; 
    if (arr.back_i == arr.capacity - 1) { 
        type* prev = arr.ptr; 
        size_t new_cap = (arr.capacity == 0) ? 8 : arr.capacity + arr.capacity / 2; 
        type* new_ptr = (type*) calloc(new_cap, sizeof(type)); 
        if (new_ptr == NULL) { 
            err_redln("failed to allocated for new capacity of %zu", new_cap); 
            return ans; 
        } 
        memcpy(new_ptr+arr.front_i, prev+arr.front_i, count_intDda(arr) * sizeof(type)); 
        FREE(prev); 
        new_arr.ptr = new_ptr; 
        new_arr.capacity = new_cap; 
    } 
    new_arr.back_i++;
    new_arr.ptr[new_arr.back_i] = elem; 
    intDdaRes ans2 = {SUCCESS, new_arr}; 
    return ans2; 
}

intDdaRes prepend_intDda(const intdDa arr, const type elem) { 
    intDda new_arr = {arr.capacity, sizeof(int), arr.front_i, arr.back_i, arr.ptr}; 
    intDdaRes ans = {FAILURE, arr}; 
    if (arr.front_i == 0) { 
        type* prev = arr.ptr; 
        size_t increase = arr.capacity / 2;
        size_t new_cap = (arr.capacity == 0) ? 8 : arr.capacity + increase; 
        type* new_ptr = (type*) calloc(new_cap, sizeof(type)); 
        if (new_ptr == NULL) { 
            err_redln("failed to allocated for new capacity of %zu", new_cap); 
            return ans; 
        } 
        memcpy(new_ptr+increase, prev, count_intDda(arr) * sizeof(type)); 
        FREE(prev); 
        new_arr.front_i = increase;
        new_arr.ptr = new_ptr; 
        new_arr.capacity = new_cap; 
    } 
    new_arr.front_i--;
    new_arr.ptr[new_arr.front_i] = elem; 
    intDdaRes ans2 = {SUCCESS, new_arr}; 
    return ans2; 
}

