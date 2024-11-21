#ifndef ARRAY_UTILS
#define ARRAY_UTILS

#define FREE(ptr) \
    free(ptr); \
    ptr=NULL;

#define FOR_EACH(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        fn(arr[i]); \
    } 
#define FOR_EACHP(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        fn(arr + i); \
    } 

#define ANY(arr, len, fn, exp) \
    for (size_t i = 0; i < len; i++) { \
        uchar res_##arr = fn(arr[i]); \
        if (res_##arr) {exp; break;} \
    } 
#define ANYP(arr, len, fn, exp) \
    for (size_t i = 0; i < len; i++) { \
        uchar res_##arr = fn(arr + i); \
        if (res_##arr) {exp; break;} \
    } 

#define ALL(arr, len, fn, exp) \
    size_t _res##arr = 0; \
    for (size_t i = 0; i < len; i++) { \
        _res##arr += fn(arr[i]); \
    } \
    if (_res##arr == len) {exp;} 
#define ALLP(arr, len, fn, exp) \
    size_t _res##arr = 0; \
    for (size_t i = 0; i < len; i++) { \
        _res##arr += fn(arr + i); \
    } \
    if (_res##arr == len) {exp;} 

#define IN(arr, len, elem, exp) \
    for (size_t i = 0; i < len; i++) { \
        if (arr[i] == elem) {exp; break;} \
    }

#define MAPP(from, len, fn, target) \
    for (size_t i = 0; i < len; i++) { \
        target[i] = fn(from + i); \
    }
#define MAP(from, len, fn, target) \
    for (size_t i = 0; i < len; i++) { \
        target[i] = fn(from[i]); \
    }

#define MAP_IP(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        arr[i] = fn(arr[i]); \
    }
#define MAP_IPP(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        arr[i] = fn(arr + i); \
    }

#define FOLD(arr, len, fn, type, name, start) \
    type name = start; \
    for (size_t i = 0; i < len; i++) { \
        name = fn(name, arr[i]); \
    } 
#define FOLDP(arr, len, fn, type, name, start) \
    type name = start; \
    for (size_t i = 0; i < len; i++) { \
        name = fn(name, arr+i); \
    } 
#define FOLDPP(arr, len, fn, type, name, start) \
    type name = start; \
    for (size_t i = 0; i < len; i++) { \
        name = fn(&name, arr+i); \
    } 
#endif
