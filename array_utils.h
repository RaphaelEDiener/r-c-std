#ifndef FOR_EACH
#define FOR_EACH(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        fn(arr[i]); \
    } 
#define FOR_EACHP(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        fn(arr + i); \
    } 
#endif

#ifndef ANY
#define ANY(arr, len, fn, exp) \
    for (size_t i = 0; i < len; i++) { \
        uchar res = fn(arr[i]); \
        if (res) {exp; break;} \
    } 
#define ANYP(arr, len, fn, exp) \
    for (size_t i = 0; i < len; i++) { \
        uchar res = fn(arr + i); \
        if (res) {exp; break;} \
    } 
#endif

#ifndef ALL
#define ALL(arr, len, fn, exp) \
    size_t _res = 0; \
    for (size_t i = 0; i < len; i++) { \
        _res += fn(arr[i]); \
    } \
    if (_res == len) {exp;} 
#define ALLP(arr, len, fn, exp) \
    size_t _res = 0; \
    for (size_t i = 0; i < len; i++) { \
        _res += fn(arr + i); \
    } \
    if (_res == len) {exp;} 
#endif

#ifndef IN
#define IN(arr, len, elem, exp) \
    for (size_t i = 0; i < len; i++) { \
        if (arr[i] == elem) {exp; break;} \
    }
#endif

#ifndef MAP
#define MAPP(from, len, fn, target) \
    for (size_t i = 0; i < len; i++) { \
        target[i] = fn(from + i) \
    }
#define MAP(from, len, fn, target) \
    for (size_t i = 0; i < len; i++) { \
        target[i] = fn(from[i]) \
    }
#endif

#ifndef MAP_IP
#define MAP_IP(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        arr[i] = fn(arr[i]) \
    }
#define MAP_IPP(arr, len, fn) \
    for (size_t i = 0; i < len; i++) { \
        arr[i] = fn(arr + i) \
    }
#endif 

#ifndef FOLD
#define FOLD(arr, len, fn, type, name, start) \
    type name = start; \
    for (size_t i = 0; i < len; i++) { \
        name = fn(name, arr[i]); \
    } 
#define FOLDP(arr, len, fn, type, name, start) \
    type name = start; \
    for (size_t i = 0; i < len; i++) { \
        fn(name, arr+i); \
    } 
#endif
