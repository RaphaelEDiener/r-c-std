#ifndef INTEGER
#define INTEGER

#define _INT_DEF_FROM(t) \
    Integer new_from_##t(t value);

// FROM can't be implemented generically

#define _INT_DEF_ADD(t) \
    Integer add_Int(t value);

#define DEFINE_INTEGER \
    typedef struct {
        uchar  positive;
        uchar* 
    } Integer;
    DEFAULT_TYPES(_INT_DEF_FROM)


#define IMPL_INTEGER

#endif
