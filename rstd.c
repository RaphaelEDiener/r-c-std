/**
* Raphael Standard Library
* ________________________
*
* How does this work?
* For once, I've preimplemented a default implementation
* for all the most common utility algorithms:
* - for each
* - all
* 
* All utils work with widepointers.
* Create a new widepointer with the following call:
* `new_wp(name, type, amount); // the ';' at the end is not nesseccary`
*
* Since I want to leverage what little type safety there is in C,
* all the functions are postfixed with the type they operate on.
* E.g: for_each_int, for_each_char, ...
*
* While I've also implemented void implementations to work with generic data,
* it is recommended that you use the macros in your code 
* and define your costume types this way when needed.
* The macros are called DEFINE_<function name>.
* E.g: DEFINE_WP(char) - defines a new wide pointer type for characters.
*      DEFINE_FOR_EACH(char) - defines a new for-each for characters.
*      ...
*
* 
*/

// #include <stdio.h>

// typedef enum error_t { DEFAULT } Error;
// 
// typedef struct res {
//     Error error;
// } Result;

typedef signed char signed_char;
typedef unsigned char unsigned_char;
typedef unsigned short unsigned_short;
typedef unsigned int unsigned_int;
typedef unsigned long unsigned_long;
typedef long long long_long;
typedef unsigned long long unsigned_long_long;
typedef long double long_double;

/* ##################################################
*  Whidepointer
*  ##################################################
*/

#define DEFINE_WP(type) \
    typedef struct { \
        unsigned long long size; \
        unsigned int count; \
        type* address; \
    } type##Wp;

#define new_wp(name, type, count) \
    type _##name[count]; \
    type##Wp name = {sizeof(type), count, _##name}; \
    

typedef struct {
    unsigned long long size;
    unsigned int count;
    unsigned long long address;
} Wp;

DEFINE_WP(char)
DEFINE_WP(signed_char)
DEFINE_WP(unsigned_char)
DEFINE_WP(short)
DEFINE_WP(unsigned_short)
DEFINE_WP(int)
DEFINE_WP(unsigned_int)
DEFINE_WP(long)
DEFINE_WP(unsigned_long)
DEFINE_WP(long_long)
DEFINE_WP(unsigned_long_long)
DEFINE_WP(float)
DEFINE_WP(double)
DEFINE_WP(long_double)

/* ##################################################
*  TODO: Whidepointer promotions (with typeof)
*  ##################################################
*/


/* ##################################################
*  For Each
*  ##################################################
*/

typedef void (*any_to_void)(void*) ; 
void _for_each(Wp ptr, any_to_void fn) { 
    for (int i = 0; i < ptr.count; i++) { 
        (*fn)((void*) ptr.address + i*ptr.size); 
    } 
}


#define DEFINE_FOR_EACH(type) \
    typedef void (*type##_to_void)(type*) ; \
    void for_each_##type(type##Wp wptr, type##_to_void fn) { \
        for (int i = 0; i < wptr.count; i++) { \
            (*fn)(wptr.address + i); \
        } \
    }

DEFINE_FOR_EACH(char)
DEFINE_FOR_EACH(signed_char)
DEFINE_FOR_EACH(unsigned_char)
DEFINE_FOR_EACH(short)
DEFINE_FOR_EACH(unsigned_short)
DEFINE_FOR_EACH(int)
DEFINE_FOR_EACH(unsigned_int)
DEFINE_FOR_EACH(long)
DEFINE_FOR_EACH(unsigned_long)
DEFINE_FOR_EACH(long_long)
DEFINE_FOR_EACH(unsigned_long_long)
DEFINE_FOR_EACH(float)
DEFINE_FOR_EACH(double)
DEFINE_FOR_EACH(long_double)


/* ##################################################
*  All
*  ##################################################
*/

typedef char (*truthy_fn)(void*);
char _all(Wp ptr, truthy_fn fn) {
    for (int i = 0; i < ptr.count; i++){
        char res = (*fn) ((void*) ptr.address+i*ptr.size);
        if ( !res ) return 0;
    }
    return 1;
}

#define DEFINE_ALL(t) \
    typedef char (*truthy_##t##_fn)(t*); \
    char all_##t(t##Wp ptr, truthy_##t##_fn fn) { \
        for (int i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((t*) ptr.address+i); \
            if ( !res ) return 0; \
        } \
        return 1; \
    }

DEFINE_ALL(char)
DEFINE_ALL(signed_char)
DEFINE_ALL(unsigned_char)
DEFINE_ALL(short)
DEFINE_ALL(unsigned_short)
DEFINE_ALL(int)
DEFINE_ALL(unsigned_int)
DEFINE_ALL(long)
DEFINE_ALL(unsigned_long)
DEFINE_ALL(long_long)
DEFINE_ALL(unsigned_long_long)
DEFINE_ALL(float)
DEFINE_ALL(double)
DEFINE_ALL(long_double)


/* ##################################################
*  TODO: Join
*  ##################################################
*/

/* ##################################################
*  TODO: Map
*  ##################################################
*/

#define DEFINE_MAP(from_t, to_t) \
    typedef char (*from_t##_to_##to_t)(from_t*); \
    void map_##from_t##_to_##to_t(from_t##Wp from_ptr, from_t##_to_##to_t fn, to_t##Wp to_ptr) { \
        for (int i = 0; i < from_ptr.count; i++){\
            char res = (*fn) (from_ptr.address+i);\
            to_ptr.address[i] = res;\
        }\
    }

#define DEFINE_MAP_TO_STD(type) \
    DEFINE_MAP(type, char) \
    DEFINE_MAP(type, signed_char) \
    DEFINE_MAP(type, unsigned_char) \
    DEFINE_MAP(type, short) \
    DEFINE_MAP(type, unsigned_short) \
    DEFINE_MAP(type, int) \
    DEFINE_MAP(type, unsigned_int) \
    DEFINE_MAP(type, long) \
    DEFINE_MAP(type, unsigned_long) \
    DEFINE_MAP(type, long_long) \
    DEFINE_MAP(type, unsigned_long_long) \
    DEFINE_MAP(type, float) \
    DEFINE_MAP(type, double) \
    DEFINE_MAP(type, long_double)

DEFINE_MAP_TO_STD(char)
DEFINE_MAP_TO_STD(signed_char)
DEFINE_MAP_TO_STD(unsigned_char)
DEFINE_MAP_TO_STD(short)
DEFINE_MAP_TO_STD(unsigned_short)
DEFINE_MAP_TO_STD(int)
DEFINE_MAP_TO_STD(unsigned_int)
DEFINE_MAP_TO_STD(long)
DEFINE_MAP_TO_STD(unsigned_long)
DEFINE_MAP_TO_STD(long_long)
DEFINE_MAP_TO_STD(unsigned_long_long)
DEFINE_MAP_TO_STD(float)
DEFINE_MAP_TO_STD(double)
DEFINE_MAP_TO_STD(long_double)

/* ##################################################
*  TODO: Map in Place
*  ##################################################
*/

/* ##################################################
*  TODO: Fold
*  ##################################################
*/

/* ##################################################
*  TODO: Curry
*  ##################################################
*/




