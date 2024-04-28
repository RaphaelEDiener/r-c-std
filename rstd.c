/**
* Raphael Standard Library
* ________________________
*
* How does this work?
* I've preimplemented a default implementation
* for all the most common utility algorithms:
* - for each
* - all
* - map
* - ...
* 
* All utils work with widepointers.
* Create a new widepointer with the following call:
* `new_wp(name, type, amount); // the ';' at the end is not strictly nesseccary`
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
* -----------------------------
* Signatures
* -----------------------------
* new_wp(<name>, <type>, <count>)
* for_each_<type>(<wp>, <fn>)
* all_<type>(<wp>, <fn>)
* any_<type>(<wp>, <fn>)
* map<from type>_to_<to type>(<from wp>, <fn>, <to wp>)
* mapip<type>(<wp>, <fn>)
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

#define DEFAULT_TYPES(macro) \
    macro(char) \
    macro(signed_char) \
    macro(unsigned_char) \
    macro(short) \
    macro(unsigned_short) \
    macro(int) \
    macro(unsigned_int) \
    macro(long) \
    macro(unsigned_long) \
    macro(long_long) \
    macro(unsigned_long_long) \
    macro(float) \
    macro(double) \
    macro(long_double)


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

DEFAULT_TYPES(DEFINE_WP)

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

DEFAULT_TYPES(DEFINE_FOR_EACH)

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

DEFAULT_TYPES(DEFINE_ALL)

/* ##################################################
*  Any
*  ##################################################
*/

char _any(Wp ptr, truthy_fn fn) {
    for (int i = 0; i < ptr.count; i++){
        char res = (*fn) ((void*) ptr.address+i*ptr.size);
        if ( res ) return 1;
    }
    return 0;
}

#define DEFINE_ANY(t) \
    char any_##t(t##Wp ptr, truthy_##t##_fn fn) { \
        for (int i = 0; i < ptr.count; i++){ \
            char res = (*fn) ((t*) ptr.address+i); \
            if ( res ) return 1; \
        } \
        return 0; \
    }

DEFAULT_TYPES(DEFINE_ANY)

/* ##################################################
*  TODO: Join
*  ##################################################
*/

// join("hi", "my", "name", "is")
// joinp(&"hi", &"my", &"name", &"is")
// joinwp(wp)

/* ##################################################
*  TODO: Split
*  ##################################################
*/

/* ##################################################
*  Map
*  TODO: generic map
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

DEFAULT_TYPES(DEFINE_MAP_TO_STD)

/* ##################################################
*  Map in Place
*  TODO: generic mapip
*  ##################################################
*/

#define DEFINE_MAPIP(type) \
    void mapip_##type(type##Wp wptr, type##_to_##type fn) { \
        for (int i = 0; i < wptr.count; i++){\
            wptr.address[i] = (*fn) (wptr.address+i);\
        }\
    }

DEFAULT_TYPES(DEFINE_MAPIP)

/* ##################################################
*  Fold
*  TODO: generic fold
*  ##################################################
*/

#define DEFINE_FOLD(from_t, to_t) \
    typedef to_t (*collapse_##from_t##_to_##to_t)(to_t*, from_t*); \
    int fold_##from_t##_to_##to_t(from_t##Wp wptr, collapse_##from_t##_to_##to_t fn, to_t start){ \
        for (int i = 0; i < wptr.count; i++) { \
            start = (*fn) (&start, wptr.address+i); \
        } \
        return start; \
    }

#define DEFINE_FOLD_TO_STD(type) \
    DEFINE_FOLD(type, char) \
    DEFINE_FOLD(type, signed_char) \
    DEFINE_FOLD(type, unsigned_char) \
    DEFINE_FOLD(type, short) \
    DEFINE_FOLD(type, unsigned_short) \
    DEFINE_FOLD(type, int) \
    DEFINE_FOLD(type, unsigned_int) \
    DEFINE_FOLD(type, long) \
    DEFINE_FOLD(type, unsigned_long) \
    DEFINE_FOLD(type, long_long) \
    DEFINE_FOLD(type, unsigned_long_long) \
    DEFINE_FOLD(type, float) \
    DEFINE_FOLD(type, double) \
    DEFINE_FOLD(type, long_double)


DEFAULT_TYPES(DEFINE_FOLD_TO_STD)

/* ##################################################
*  TODO: Curry
*  Needs to be done at runtime with a struct maintaining stuff.
*  But how do I pass that stuff into the function pointer?
*  Can I construct a curry object with a macro which is tailor made for the function?
*  ##################################################
*/


/* ##################################################
*  TODO: Iterator
*  ##################################################
*/


