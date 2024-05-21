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
    uchar _res = 0; \
    for (size_t i = 0; i < len; i++) { \
        res += fn(arr[i]); \
    } \
    if (res == len) {exp;} \
#define ALLP(arr, len, fn, exp) \
    uchar _res = 0; \
    for (size_t i = 0; i < len; i++) { \
        res += fn(arr + i); \
    } \
    if (res == len) {exp;} \
#endif

#ifndef IN
#define IN(arr, len, elem, exp) \
    for (size_t i = 0; i < len; i++) { \
        if (arr[i] == elem) {exp; break;} \
    }
#endif

