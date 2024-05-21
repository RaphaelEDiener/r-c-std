
/* ##################################################
*  TODO: Whidepointer promotions (with typeof)
*  ##################################################
*/


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
*  ##################################################
*/

#define DEFINE_MAP(from_t, to_t) \
    typedef char (*from_t##_to_##to_t)(from_t*); \
    void map_##from_t##_to_##to_t(from_t##Wp from_ptr, from_t##_to_##to_t fn, to_t##Wp to_ptr) { \
        for (size_t i = 0; i < from_ptr.count; i++){\
            char res = (*fn) (from_ptr.address+i);\
            to_ptr.address[i] = res;\
        }\
    }

DEFAULT_FOR_TTYPES(DEFINE_MAP)

/* ##################################################
*  Map in Place
*  ##################################################
*/

#define DEFINE_MAPIP(type) \
    void mapip_##type(type##Wp wptr, type##_to_##type fn) { \
        for (size_t i = 0; i < wptr.count; i++){\
            wptr.address[i] = (*fn) (wptr.address+i);\
        }\
    }

DEFAULT_TYPES(DEFINE_MAPIP)

/* ##################################################
*  Fold
*  ##################################################
*/

#define DEFINE_FOLD(from_t, to_t) \
    typedef to_t (*collapse_##from_t##_to_##to_t)(to_t*, from_t*); \
    int fold_##from_t##_to_##to_t(from_t##Wp wptr, collapse_##from_t##_to_##to_t fn, to_t start){ \
        for (size_t i = 0; i < wptr.count; i++) { \
            start = (*fn) (&start, wptr.address+i); \
        } \
        return start; \
    }

DEFAULT_FOR_TTYPES(DEFINE_FOLD_TO_STD)

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


