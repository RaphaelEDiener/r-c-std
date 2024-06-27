#include "rstd.h"

void add1p(int* x) {
    (*x)++;
}
int add2(int x) {
    return x+2;
}
int add2p(const int* x) {
    return (*x)+2;
}
char eq1(int x) {
    return x == 1;
}
char false(int x) {
    return 0 && (char) x;
}
char eq1p(const int* x) {
    return *x == 1;
}
char falsep(const int* x) {
    return 0 && (char) *x;
}
char positive(int x) {
    return x >= 0;
}
char positivep(const int* x) {
    return *x >= 0;
}
char negative(int x) {
    return x <= 0;
}
char negativep(const int* x) {
    return *x <= 0;
}
uchar int_to_uchar(int x) {
    return (char) (x % 256);
}
uchar intp_to_uchar(const int* x) {
    return (char) ((*x) % 256);
}
int add(int x, int y) {
    return x + y;
}
int addp(int x, const int* y) {
    return x + (*y);
}
int addpp(const int* x, const int* y) {
    return (*x) + (*y);
}
static int counter_ = 0;
void inc_counter(const int* _ignore) {
    (void)_ignore;
    counter_++;
}
char to_zero(const char* ignore) {
    (void)ignore;
    return 0;
}
char is_zero(const char* x) {
    return 0 == *x;
}
char is_one(const char* x) {
    return 1 == *x;
}


int test_array_macros(void) {
    int fails = 0;
    // can't test side effects on FOR_EACH

    int arr0[10] = {0,1,2,3,4,5,6,7,8,9};
    FOR_EACHP(arr0, 10, add1p);
    for (size_t i = 0; i < 10; i++) {
        test_int(arr0[i], i+1, "FOR_EACH mutates the result for a mutating function");
    }

    int arr1[10] = {0,1,2,3,4,5,6,7,8,9};
    uchar yes = 0;
    ANY(arr1, 10, eq1, yes = 1;);
    fails += test_char(yes, 1, "ANY finds matching value in array");

    int arr2[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    ANY(arr2, 10, false, yes = 1;);
    fails += test_char(yes, 0, "ANY doesn't find false in array");

    int arr3[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    ANYP(arr3, 10, eq1p, yes = 1;);
    fails += test_char(yes, 1, "ANYP finds matching value in array");

    int arr4[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    ANYP(arr4, 10, falsep, yes = 1;);
    fails += test_char(yes, 0, "ANYP doesn't find false in array");

    int arr5[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    ALL(arr5, 10, positive, yes = 1;);
    fails += test_char(yes, 1, "ALL finds everything it should");

    int arr6[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    ALLP(arr6, 10, positivep, yes = 1;);
    fails += test_char(yes, 1, "ALLP finds everything it should");

    int arr7[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    ALL(arr7, 10, negative, yes = 1;);
    fails += test_char(yes, 0, "ALL doesn't find things it should't");

    int arr8[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    ALLP(arr8, 10, negativep, yes = 1;);
    fails += test_char(yes, 0, "ALLP doesn't find things it shouldn't");

    int arr9[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    IN(arr9, 10, 10, yes = 1;);
    fails += test_char(yes, 0, "IN doesn't find things it shouldn't");

    int arr10[10] = {0,1,2,3,4,5,6,7,8,9};
    yes = 0;
    IN(arr10, 10, 9, yes = 1;);
    fails += test_char(yes, 1, "IN finds things it should");

    int arr11[10] = {256,257,258,259,260,261,262,263,264,265};
    uchar target0[10];
    MAP(arr11, 10, int_to_uchar, target0);
    for (size_t i = 0; i < 10; i++) {
        test_char(target0[i], (char) i, "MAP transforms the element in the new array");
        test_int(arr11[i], 256 + (int) i, "MAP doesn't alter the original array");
    }
    int arr12[10] = {256,257,258,259,260,261,262,263,264,265};
    uchar target1[10];
    MAPP(arr12, 10, intp_to_uchar, target1);
    for (size_t i = 0; i < 10; i++) {
        test_char(target1[i], (char) i, "MAPP transforms the element in the new array");
        test_int(arr11[i], 256 + (int) i, "MAPP doesn't alter the original array");
    }

    int arr13[10] = {0,1,2,3,4,5,6,7,8,9};
    MAP_IP(arr13, 10, add2);
    for (size_t i = 0; i < 10; i++) {
        test_int(arr13[i], 2 + (int) i, "MAP_IP transforms the elements");
    }

    int arr14[10] = {0,1,2,3,4,5,6,7,8,9};
    MAP_IPP(arr14, 10, add2p);
    for (size_t i = 0; i < 10; i++) {
        test_int(arr14[i], 2 + (int) i, "MAP_IPP transforms the elements");
    }

    int arr15[10] = {0,1,2,3,4,5,6,7,8,9};
    FOLD(arr15, 10, add, int, res0, 0);
    test_int(res0, 45, "Folds correctly");

    int arr16[10] = {0,1,2,3,4,5,6,7,8,9};
    FOLDP(arr16, 10, addp, int, res1, 0);
    test_int(res0, 45, "Folds correctly");

    int arr17[10] = {0,1,2,3,4,5,6,7,8,9};
    FOLDPP(arr17, 10, addpp, int, res2, 0);
    test_int(res0, 45, "Folds correctly");

    return fails;
}


int test_cmp(void) {
    int fails = 0;
    char x0 = '0';
    char y0 = '9';
    test_Compareable(cmp_char(&x0, &y0), LESS, "0 is less than 9");
    char x1 = '0';
    char y1 = '0';
    test_Compareable(cmp_char(&x1, &y1), EQUAL, "0 equal 0");
    char x2 = '9';
    char y2 = '0';
    test_Compareable(cmp_char(&x2, &y2), GREATER, "9 is greater than 0");
    return fails;
}

int test_da_creation(void) {
    int fails = 0;
    intDaRes da0 = new_intDa(1);
    fails += test_ResultType(da0.type, SUCCESS, "can create new dynamic array with cap 1");
    free(da0.result.ptr);

    intDaRes da1 = new_intDa(SIZE_MAX);
    fails += test_ResultType(da1.type, FAILURE, "can't create new dynamic array with cap > ram space");
    return fails;
}

int test_da_insertion(void) {
    int fails = 0;
    const intDa da0 = new_intDa(16).result;
    fails += test_size_t(da0.count, 0, "new dynamic arrays are empty");
    fails += test_size_t(da0.size, sizeof(int), "new dynamic arrays have the element size gets correctly inferred");
    fails += test_size_t(da0.capacity, 16, "new dynamic arrays have the given capacity");
    free(da0.ptr);

    const charDa da1 = new_charDa(0).result;
    fails += test_size_t(da1.capacity, 0, "new dynamic arrays can be empty");
    charDaRes suc = insert_charDa(da1, '0');
    fails += test_ResultType(suc.type, SUCCESS, "Inserting into empty DA succeeds");
    size_t zero = 0;
    fails += test_Compareable(cmp_size_t(&suc.result.capacity, &zero), GREATER, "inserting into empty DA increases capacity");
    free(suc.result.ptr);

    charDa da2 = new_charDa(1).result;
    charDa da2a = insert_charDa(da2, '0').result;
    fails += test_size_t(da2a.capacity, 1, "inserting into DA while not at full capacity doesn't increase capacity");
    charDa da2b = insert_charDa(da2a, '1').result;
    size_t one = 1;
    fails += test_Compareable(cmp_size_t(&da2b.capacity, &one), GREATER, "inserting into DA while at full capacity increases capacity");
    fails += test_char(da2b.ptr[0], '0', "capacity increase doesn't modify old data");
    fails += test_char(da2b.ptr[1], '1', "capacity increase inserts correctly");
    free(da2b.ptr);

    // this will be invalid and pointing to null, ensuring that the new size, will also point to null 
    charDa da4 = new_charDa(SIZE_MAX / 4).result;
    da4.count = SIZE_MAX / 4;
    charDaRes faill = insert_charDa(da4, '0');
    fails += test_ResultType(faill.type, FAILURE, "Fail if can't allocate new memory for size increase");

    return fails;
}
int test_da_for_each(void) {
    int fails = 0;
    intDa da0 = new_intDa(8).result;
    da0.count = 8;
    for_each_intDa(da0, inc_counter);
    fails += test_int(counter_, 8, "for each DA executes the right amount of times");
    free(da0.ptr);
    return fails;
} 
int test_da_all(void) {
    int fails = 0;

    charDa da0 = new_charDa(8).result;
    da0.count = 8;
    mapip_charDa(da0, to_zero);
    fails += test_char(all_charDa(da0, is_zero), 1, "all succeeds if it finds all cases");

    charDa da1 = new_charDa(8).result;
    da1.count = 8;
    mapip_charDa(da1, to_zero);
    da1.ptr[4] = 123;
    fails += test_char(all_charDa(da1, is_zero), 0, "all fails if one doesn't fit");

    charDa da2 = new_charDa(0).result;
    fails += test_char(all_charDa(da2, is_zero), 1, "all succeeds for the empty case");

    free(da0.ptr);
    return fails;
}
int test_da_any(void) {
    int fails = 0;

    charDa da0 = new_charDa(8).result;
    da0.count = 8;
    mapip_charDa(da0, to_zero);
    da0.ptr[7] = 1;
    fails += test_char(any_charDa(da0, is_one), 1, "any succeeds if it finds one case");
    free(da0.ptr);

    charDa da1 = new_charDa(8).result;
    da1.count = 8;
    mapip_charDa(da1, to_zero);
    fails += test_char(any_charDa(da1, is_one), 0, "any fails if all don't fit");
    free(da1.ptr);

    charDa da2 = new_charDa(0).result;
    fails += test_char(any_charDa(da2, is_zero), 0, "any fails for the empty case");

    return fails;
}

int test_da_pin(void) {
    int fails = 0;
    const char seven = 7;
    const char ten = 10;

    charDa da0 = new_charDa(8).result;
    da0.count = 8;
    for (size_t i = 0; i < da0.count; i++) {
        da0.ptr[i] = i;
    }
    fails += test_char(pin_charDa(da0, &seven), 1, "pin finds element in da");
    free(da0.ptr);

    charDa da1 = new_charDa(8).result;
    da1.count = 8;
    for (size_t i = 0; i < da1.count; i++) {
        da1.ptr[i] = i;
    }
    fails += test_char(pin_charDa(da1, &ten), 0, "pin can't find element that are not in da");
    free(da1.ptr);

    charDa da2 = new_charDa(0).result;
    fails += test_char(pin_charDa(da2, &ten), 0, "pin can't find element in the empty da");
    free(da2.ptr);

    return fails;
}
int test_da_in(void) {
    int fails = 0;
    const char seven = 7;
    const char ten = 10;

    charDa da0 = new_charDa(8).result;
    da0.count = 8;
    for (size_t i = 0; i < da0.count; i++) {
        da0.ptr[i] = i;
    }
    fails += test_char(in_charDa(da0, &seven, cmp_char), 1, "in finds element in da");
    free(da0.ptr);

    charDa da1 = new_charDa(8).result;
    da1.count = 8;
    for (size_t i = 0; i < da1.count; i++) {
        da1.ptr[i] = i;
    }
    fails += test_char(in_charDa(da1, &ten, cmp_char), 0, "in can't find element that are not in da");
    free(da1.ptr);

    charDa da2 = new_charDa(0).result;
    fails += test_char(in_charDa(da2, &ten, cmp_char), 0, "in can't find element in the empty da");
    free(da2.ptr);

    return fails;
}
int test_da_unique(void) {
    int fails = 0;

    charDa da0 = new_charDa(8).result;
    for (size_t i = 0; i < 7; i++) {
        da0.ptr[i] = i;
    }
    da0.ptr[7] = 1;
    da0.count = 8;
    charDa un0 = unique_charDa(da0, eq_char).result;
    fails += test_size_t(un0.count, 7, "unique removes dulpicates");
    for (char i = 0; i < 7; i++) {
        fails += test_char(un0.ptr[(size_t)i], i, "unique preseves unique elements");
    }
    free(da0.ptr);

    charDa da1 = new_charDa(8).result;
    for (size_t i = 0; i < 7; i++) {
        da1.ptr[i] = i;
    }
    da1.ptr[7] = 1;
    da1.count = 8;
    charDa un1 = unique_charDa(da1, eq_char).result;
    fails += test_size_t(
        un1.capacity, 
        7, 
        "when making unique, resulting capacity equals unique elements"
    );
    free(da1.ptr);

    charDa da2 = new_charDa(8).result;
    da2.ptr[2] = 1;
    da2.count = 4;
    charDa un2 = unique_charDa(da2, eq_char).result;
    fails += test_char((da2.ptr != un2.ptr), 1, "unique da's return a copy of it");
    free(da2.ptr);

    charDa da3 = new_charDa(0).result;
    charDa un3 = unique_charDa(da3, eq_char).result;
    fails += test_size_t(un3.capacity, 0, "unique da elements of the empty da is also empty");
    fails += test_size_t(un3.count, 0, "unique da elements of the empty da is also empty");
    free(da3.ptr);

    return fails;
}
int test_da_sort(void) {
    int fails = 0;

    ucharDa da0 = new_ucharDa(128).result;
    da0.count = 128;
    for (uchar i = 0; i < 128; i++) {
        da0.ptr[i] = 127-i;
    }
    sort_ucharDa(da0, cmp_uchar);
    uchar sorted0 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted0 += da0.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted0, 128, "reverse da becomes sorted");
    fails += test_size_t(da0.count, 128, "sorting doesn't impact count");
    fails += test_size_t(da0.capacity, 128, "sorting doesn't impact capacity");
    free(da0.ptr);

    ucharDa da1 = new_ucharDa(0).result;
    sort_ucharDa(da1, cmp_uchar);
    fails += test_uchar(da1.capacity, 0, "sorting empty da leaves it empty");
    fails += test_uchar(da1.count, 0, "sorting empty da leaves it empty");
    free(da1.ptr);

    ucharDa da2 = new_ucharDa(8).result;
    da2.count = 8;
    for (uchar i = 0; i < 8; i++) {
        da2.ptr[i] = 7-i;
    }
    sort_ucharDa(da2, cmp_uchar);
    uchar contains = 0;
    for (uchar i = 0; i < 8; i++) {
        contains += pin_ucharDa(da2, &i);
    }
    fails += test_uchar(contains, 8, "sorting contains the same elements as before");
    free(da2.ptr);

    ucharDa da3 = new_ucharDa(128).result;
    da3.count = 128;
    for (uchar i = 0; i < 128; i++) {
        da3.ptr[i] = i;
    }
    sort_ucharDa(da3, cmp_uchar);
    uchar sorted3 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted3 += da3.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted3, 128, "sorted da stays sorted");
    free(da3.ptr);

    ucharDa da4 = new_ucharDa(128).result;
    da4.count = 128;
    free(da4.ptr); // cursed but easiest way to test
    uchar arr0[128] = {
        55, 82, 107, 44, 83, 12, 110, 67, 10, 7, 89, 62, 21, 65, 111, 69, 52, 27, 34, 117, 105,
        70, 19, 72, 121, 38, 14, 46, 23, 79, 41, 47, 35, 85, 43, 118, 122, 64, 54, 114, 80, 56,
        9, 81, 104, 66, 87, 32, 127, 1, 84, 68, 22, 8, 73, 99, 125, 45, 48, 4, 20, 94, 6, 58,
        75, 102, 74, 115, 108, 42, 16, 17, 86, 113, 106, 101, 50, 120, 112, 96, 33, 60, 91, 30,
        0, 40, 37, 59, 15, 100, 126, 28, 57, 2, 31, 123, 61, 36, 116, 51, 5, 95, 93, 92, 103, 78, 
        88, 24, 29, 63, 71, 90, 3, 13, 77, 124, 97, 25, 53, 49, 98, 109, 119, 11, 18, 76, 26, 39
    };
    da4.ptr = arr0;
    sort_ucharDa(da4, cmp_uchar);
    uchar sorted4 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted4 += da4.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted4, 128, "sorts 'random' da 0");
    uchar arr1[128] = {
        28, 64, 38, 106, 62, 4, 75, 108, 111, 45, 117, 50, 109, 85, 82, 90, 101, 66, 31, 33, 10,
        13, 60, 69, 79, 46, 51, 93, 119, 53, 121, 37, 72, 91, 115, 43, 97, 88, 73, 20, 120, 27, 126,
        112, 5, 25, 67, 83, 48, 57, 2, 70, 42, 58, 100, 124, 107, 29, 7, 39, 56, 81, 36, 89, 34,
        11, 123, 59, 127, 21, 9, 114, 49, 122, 18, 65, 125, 87, 76, 103, 54, 99, 74, 41, 61, 23, 
        84, 16, 6, 32, 8, 95, 96, 19, 52, 77, 26, 110, 3, 71, 40, 113, 105, 30, 104, 68, 102, 14,
        55, 92, 24, 118, 94, 80, 44, 63, 22, 12, 47, 0, 98, 86, 15, 78, 17, 116, 35, 1 
    };
    da4.ptr = arr1;
    sort_ucharDa(da4, cmp_uchar);
    sorted4 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted4 += da4.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted4, 128, "sorts 'random' da 1");
    uchar arr2[128] = {
        79, 121, 83, 35, 33, 73, 18, 20, 67, 90, 105, 66, 111, 106, 8, 57, 120, 114, 42, 77, 23,
        85, 55, 63, 69, 86, 95, 24, 11, 82, 74, 127, 103, 89, 60, 84, 81, 110, 115, 112, 6, 9, 126,
        119, 43, 97, 80, 15, 102, 71, 64, 123, 39, 98, 44, 61, 49, 92, 72, 29, 5, 51, 117, 125, 3,
        25, 32, 54, 107, 16, 45, 53, 4, 70, 36, 10, 88, 26, 75, 91, 17, 13, 56, 14, 108, 47, 19, 122,
        48, 65, 113, 22, 34, 94, 58, 76, 78, 87, 12, 96, 41, 2, 62, 68, 116, 100, 46, 0, 30, 59,
        31, 52, 7, 118, 38, 124, 28, 104, 37, 50, 109, 101, 21, 27, 99, 1, 40, 93 
    };
    da4.ptr = arr2;
    sort_ucharDa(da4, cmp_uchar);
    sorted4 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted4 += da4.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted4, 128, "sorts 'random' da 2");

    ucharDa da5 = new_ucharDa(16).result;
    da5.count = 16;
    free(da5.ptr); // cursed but easiest way to test
    uchar arr5[16] = {
        15, 0, 14, 1, 13, 2, 12, 3, 11, 4, 10, 5, 9, 6, 8, 7
    };
    da5.ptr = arr5;
    sort_ucharDa(da5, cmp_uchar);
    uchar sorted5 = 0;
    for (uchar i = 0; i < 16; i++) {
        sorted5 += da5.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted5, 16, "sorts shuffeled da");

    return fails;
}
int test_da_radix(void) {
    int fails = 0;

    ucharDa da0 = new_ucharDa(128).result;
    da0.count = 128;
    for (uchar i = 0; i < 128; i++) {
        da0.ptr[i] = 127-i;
    }
    radix_ucharDa(da0);
    uchar sorted0 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted0 += da0.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted0, 128, "radix reverse da becomes sorted");
    fails += test_size_t(da0.count, 128, "radix doesn't impact count");
    fails += test_size_t(da0.capacity, 128, "radix doesn't impact capacity");
    free(da0.ptr);

    ucharDa da1 = new_ucharDa(0).result;
    radix_ucharDa(da1);
    fails += test_uchar(da1.capacity, 0, "radix empty da leaves it empty");
    fails += test_uchar(da1.count, 0, "radix empty da leaves it empty");
    free(da1.ptr);

    ucharDa da2 = new_ucharDa(8).result;
    da2.count = 8;
    for (uchar i = 0; i < 8; i++) {
        da2.ptr[i] = 7-i;
    }
    radix_ucharDa(da2);
    uchar contains = 0;
    for (uchar i = 0; i < 8; i++) {
        contains += pin_ucharDa(da2, &i);
    }
    fails += test_uchar(contains, 8, "radix contains the same elements as before");
    free(da2.ptr);

    ucharDa da3 = new_ucharDa(128).result;
    da3.count = 128;
    for (uchar i = 0; i < 128; i++) {
        da3.ptr[i] = i;
    }
    radix_ucharDa(da3);
    uchar sorted3 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted3 += da3.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted3, 128, "radix sorted da stays sorted");
    free(da3.ptr);

    ucharDa da4 = new_ucharDa(128).result;
    da4.count = 128;
    free(da4.ptr); // cursed but easiest way to test
    uchar arr0[128] = {
        55, 82, 107, 44, 83, 12, 110, 67, 10, 7, 89, 62, 21, 65, 111, 69, 52, 27, 34, 117, 105,
        70, 19, 72, 121, 38, 14, 46, 23, 79, 41, 47, 35, 85, 43, 118, 122, 64, 54, 114, 80, 56,
        9, 81, 104, 66, 87, 32, 127, 1, 84, 68, 22, 8, 73, 99, 125, 45, 48, 4, 20, 94, 6, 58,
        75, 102, 74, 115, 108, 42, 16, 17, 86, 113, 106, 101, 50, 120, 112, 96, 33, 60, 91, 30,
        0, 40, 37, 59, 15, 100, 126, 28, 57, 2, 31, 123, 61, 36, 116, 51, 5, 95, 93, 92, 103, 78, 
        88, 24, 29, 63, 71, 90, 3, 13, 77, 124, 97, 25, 53, 49, 98, 109, 119, 11, 18, 76, 26, 39
    };
    da4.ptr = arr0;
    radix_ucharDa(da4);
    uchar sorted4 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted4 += da4.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted4, 128, "radix sorts 'random' da 0");
    uchar arr1[128] = {
        28, 64, 38, 106, 62, 4, 75, 108, 111, 45, 117, 50, 109, 85, 82, 90, 101, 66, 31, 33, 10,
        13, 60, 69, 79, 46, 51, 93, 119, 53, 121, 37, 72, 91, 115, 43, 97, 88, 73, 20, 120, 27, 126,
        112, 5, 25, 67, 83, 48, 57, 2, 70, 42, 58, 100, 124, 107, 29, 7, 39, 56, 81, 36, 89, 34,
        11, 123, 59, 127, 21, 9, 114, 49, 122, 18, 65, 125, 87, 76, 103, 54, 99, 74, 41, 61, 23, 
        84, 16, 6, 32, 8, 95, 96, 19, 52, 77, 26, 110, 3, 71, 40, 113, 105, 30, 104, 68, 102, 14,
        55, 92, 24, 118, 94, 80, 44, 63, 22, 12, 47, 0, 98, 86, 15, 78, 17, 116, 35, 1 
    };
    da4.ptr = arr1;
    radix_ucharDa(da4);
    sorted4 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted4 += da4.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted4, 128, "radix sorts 'random' da 1");
    uchar arr2[128] = {
        79, 121, 83, 35, 33, 73, 18, 20, 67, 90, 105, 66, 111, 106, 8, 57, 120, 114, 42, 77, 23,
        85, 55, 63, 69, 86, 95, 24, 11, 82, 74, 127, 103, 89, 60, 84, 81, 110, 115, 112, 6, 9, 126,
        119, 43, 97, 80, 15, 102, 71, 64, 123, 39, 98, 44, 61, 49, 92, 72, 29, 5, 51, 117, 125, 3,
        25, 32, 54, 107, 16, 45, 53, 4, 70, 36, 10, 88, 26, 75, 91, 17, 13, 56, 14, 108, 47, 19, 122,
        48, 65, 113, 22, 34, 94, 58, 76, 78, 87, 12, 96, 41, 2, 62, 68, 116, 100, 46, 0, 30, 59,
        31, 52, 7, 118, 38, 124, 28, 104, 37, 50, 109, 101, 21, 27, 99, 1, 40, 93 
    };
    da4.ptr = arr2;
    radix_ucharDa(da4);
    sorted4 = 0;
    for (uchar i = 0; i < 128; i++) {
        sorted4 += da4.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted4, 128, "radix sorts 'random' da 2");
    // free(da4.ptr); <- local array = no free!

    ucharDa da5 = new_ucharDa(16).result;
    da5.count = 16;
    free(da5.ptr); // cursed but easiest way to test
    uchar arr5[16] = {
        15, 0, 14, 1, 13, 2, 12, 3, 11, 4, 10, 5, 9, 6, 8, 7
    };
    da5.ptr = arr5;
    radix_ucharDa(da5);
    uchar sorted5 = 0;
    for (uchar i = 0; i < 16; i++) {
        sorted5 += da5.ptr[(size_t)i] == i;
    }
    fails += test_uchar(sorted5, 16, "radix sorts shuffeled da");
    // free(da5.ptr); <- local array = no free!

    return fails;
}
int test_da_mapip(void) {
    int fails = 0;

    intDa da0 = new_intDa(8).result;
    da0.count = 8;
    int* op = da0.ptr;
    mapip_intDa(da0, add2p);
    uchar is_twos = 0;
    for (size_t i = 0; i < 8; i++) { 
        is_twos += da0.ptr[i] == 2;
    }
    fails += test_uchar(is_twos, 8, "mapip's all elements correctly");
    fails += test_char(op == da0.ptr, 1, "in place mapping is in place");
    free(da0.ptr);

    intDa da1 = new_intDa(0).result;
    mapip_intDa(da1, add2p);
    fails += test_size_t(da1.count, 0, "empty mapip works");

    return fails;
}
int test_da_map(void) {
    int fails = 0;

    intDa da0 = new_intDa(8).result;
    for (size_t i = 0; i < 8; i++) {
        da0 = insert_intDa(da0, (int) i).result;
    }
    intDa res0 = map_intDa_to_intDa(da0, add2p).result;
    for (size_t i = 0; i < 8; i++) { 
        fails += test_int(res0.ptr[i], 2 + (int) i, "Da maps all elements correctly within same type");
    }
    fails += test_char(res0.ptr[1] == da0.ptr[1], 0 , "map da doesn't alter original da");
    free(da0.ptr);
    free(res0.ptr);

    intDa da1 = new_intDa(8).result;
    for (size_t i = 0; i < 8; i++) {
        da1 = insert_intDa(da1, (int) i).result;
    }
    ucharDa res1 = map_intDa_to_ucharDa(da0, intp_to_uchar).result;
    for (size_t i = 0; i < 8; i++) {
        fails += test_uchar(res1.ptr[i], (uchar) i, "maps all elements correctly within different types");
    }
    free(da1.ptr);
    free(res1.ptr);

    intDa da2 = new_intDa(0).result;
    intDa res2 = map_intDa_to_intDa(da2, add2p).result;
    fails += test_size_t(res2.count, 0, "empty map da works");

    return fails;
}
int test_da_fold(void) {
    int fails = 0;

    intDa da0 = new_intDa(8).result;
    for (size_t i = 0; i < 8; i++) {
        da0 = insert_intDa(da0, 1).result;
    }
    int res0 = fold_intDa_to_int(da0, addpp, 0);
    fails += test_int(res0, 8, "fold da correctly folds");

    intDa da1 = new_intDa(0).result;
    int res1 = fold_intDa_to_int(da1, addpp, 0);
    fails += test_int(res1, 0, "empty fold works");

    return fails;
}

int test_dynamic_arrays(void) {
    int fails = 0;
    fails += test_da_creation();
    fails += test_da_insertion();
    fails += test_da_for_each();
    fails += test_da_all();
    fails += test_da_any();
    fails += test_da_in();
    fails += test_da_pin();
    fails += test_da_unique();
    fails += test_da_sort();
    fails += test_da_radix();
    fails += test_da_mapip();
    fails += test_da_map();
    fails += test_da_fold();
    return fails;
}

int test_save_sub(void) {
    int fails = 0;
    fails += test_size_t(save_sub(10, 20), 0, "save sub doesn't go's bellow zero");
    fails += test_size_t(save_sub(20, 10), 10, "save subbing inside bound works normally");
    return fails;
}
int test_save_add(void) {
    int fails = 0;
    fails += test_size_t(save_add(SIZE_MAX - 10, 20), SIZE_MAX, "save add doesn't go's above max");
    fails += test_size_t(save_add(20, 10), 30, "save adding inside bound works");
    return fails;
}
int test_math(void) {
    int fails = 0;
    fails += test_save_sub();
    fails += test_save_add();
    return fails;
}

int test_is_lower(void) {
    int fails = 0;
    
    for (char c = '!'; c <= '@'; c++) {
        fails += test_char(is_lower(c), 1, "Special char is lowercase");
    }
    for (char c = '['; c <= '`'; c++) {
        fails += test_char(is_lower(c), 1, "Special char is lowercase");
    }
    for (char c = '{'; c <= '~'; c++) {
        fails += test_char(is_lower(c), 1, "braces are lowercase");
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        fails += test_char(is_lower(c), 0, "Uppercase not lowercase");
    }
    for (char c = 'a'; c <= 'z'; c++) {
        fails += test_char(is_lower(c), 1, "lowercase is lowecase");
    }
    for (char c = 0; c < '!'; c++) {
        fails += test_char(is_lower(c), 0, "controll code is not lowercase");
    }

    return fails;
}
int test_is_upper(void) {
    int fails = 0;

    for (char c = '!'; c <= '@'; c++) {
        fails += test_char(is_upper(c), 1, "Special char is uppercase");
    }
    for (char c = '['; c <= '`'; c++) {
        fails += test_char(is_upper(c), 1, "Special char is uppercase");
    }
    for (char c = '{'; c <= '~'; c++) {
        fails += test_char(is_upper(c), 1, "braces are uppercase");
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        fails += test_char(is_upper(c), 1, "Uppercase is uppercase");
    }
    for (char c = 'a'; c <= 'z'; c++) {
        fails += test_char(is_upper(c), 0, "lowercase is not uppercase");
    }
    for (char c = 0; c < '!'; c++) {
        fails += test_char(is_upper(c), 0, "controll code is not uppercase");
    }

    return fails;
}
int test_string_operations(void) {
    int fails = 0;
    fails += test_is_upper();
    fails += test_is_lower();

    return fails;
}

int test_list_append(void) {
    int fails = 0;

    charLl ll0 = new_charLl();
    fails += test_size_t(ll0.count, 0, "new ll are empty");
    charLlRes res0 = append_charLl(ll0, 42);
    fails += test_ResultType(res0.type, SUCCESS, "appending ll into empty succeeds");
    fails += test_size_t(res0.result.count, 1, "appending ll increases count");
    charRes get0 = get_charLl(res0.result, 0);
    fails += test_ResultType(get0.type, SUCCESS, "ll getting just inserted element works");
    fails += test_char(get0.result, 42, "appending into ll insertes element");
    // free_charLl(ll0);

    charLl ll1 = res0.result;
    charLlRes res1 = append_charLl(ll1, 24);
    fails += test_ResultType(res1.type, SUCCESS, "appending ll into filled succeeds");
    fails += test_size_t(res1.result.count, 2, "appending ll increases count");
    fails += test_char(get_charLl(res1.result, 0).result, 42, "appending into ll doesn't alter other lements");
    fails += test_char(get_charLl(res1.result, 1).result, 24, "appending into ll insertes element in the back");
    // free_charLl(ll1);

    return fails;
}
int test_list_prepend(void) {
    int fails = 0;

    charLl ll0 = new_charLl();
    charLlRes res0 = prepend_charLl(ll0, 42);
    fails += test_ResultType(res0.type, SUCCESS, "prepending ll into empty succeeds");
    fails += test_size_t(res0.result.count, 1, "prepending ll increases count");
    charRes get0 = get_charLl(res0.result, 0);
    fails += test_ResultType(get0.type, SUCCESS, "ll getting just inserted element works");
    fails += test_char(get0.result, 42, "prepending into ll insertes element");
    // free_charLl(ll0);

    charLl ll1 = res0.result;
    charLlRes res1 = prepend_charLl(ll1, 24);
    fails += test_ResultType(res1.type, SUCCESS, "prepending ll into filled succeeds");
    fails += test_size_t(res1.result.count, 2, "prepending ll increases count");
    fails += test_char(get_charLl(res1.result, -1).result, 42, "prepending into ll doesn't alter other lements");
    fails += test_char(get_charLl(res1.result, 0).result, 24, "prepending into ll insertes element in the front");
    // free_charLl(ll1);

    return fails;
}
int test_list_get(void) {
    int fails = 0;

    charLl ll0 = new_charLl();
    for (size_t i = 0; i < 10; i++) {
        ll0 = append_charLl(ll0, (char) i).result;
    }

    charRes get0 = get_charLl(ll0, 0);
    fails += test_ResultType(get0.type, SUCCESS, "get 0 in 10 length ll works");
    fails += test_char(get0.result, 0, "get 0 in 10 length returns correct value");
    charRes get1 = get_charLl(ll0, 1);
    fails += test_ResultType(get1.type, SUCCESS, "get 1 in 10 length ll works");
    fails += test_char(get1.result, 1, "get 1 in 10 length returns correct value");
    charRes get2 = get_charLl(ll0, 9);
    fails += test_ResultType(get2.type, SUCCESS, "get 9 in 10 length ll works");
    fails += test_char(get2.result, 9, "get 9 in 10 length returns correct value");
    
    charRes get9 = get_charLl(ll0, -1);
    fails += test_ResultType(get9.type, SUCCESS, "get -1 in 10 length ll works");
    fails += test_char(get9.result, 9, "get -1 in 10 length returns correct value");
    charRes get8 = get_charLl(ll0, -2);
    fails += test_ResultType(get8.type, SUCCESS, "get -2 in 10 length ll works");
    fails += test_char(get8.result, 8, "get -2 in 10 length returns correct value");
    charRes get7 = get_charLl(ll0, -10);
    fails += test_ResultType(get7.type, SUCCESS, "get -10 in 10 length ll works");
    fails += test_char(get7.result, 0, "get -10 in 10 length returns correct value");
    
    charRes get10 = get_charLl(ll0, 10);
    fails += test_ResultType(get10.type, FAILURE, "get 10 in 10 length ll fails");
    charRes get_11 = get_charLl(ll0, -11);
    fails += test_ResultType(get_11.type, FAILURE, "get -11 in 10 length ll fails");
    
    // free_charLl(ll0);

    charLl ll1 = new_charLl();
    charRes get_not0 = get_charLl(ll1, 0);
    fails += test_ResultType(get_not0.type, FAILURE, "get 0 in 0 length ll fails");
    charRes get_not1 = get_charLl(ll1, -1);
    fails += test_ResultType(get_not1.type, FAILURE, "get -1 in 0 length ll fails");

    return fails;
}
int test_list_remove(void) {
    int fails = 0;

    charLl ll0 = new_charLl();

    fails += test_size_t(ll0.count, 0, "empy ll are empty");

    // "removing ll from empty list fails"
    charLlRes res0 = rem_charLl(ll0, 0);
    fails += test_ResultType(res0.type, FAILURE, "removing ll from empty list fails");
    charLlRes res1 = rem_charLl(ll0, -1);
    fails += test_ResultType(res1.type, FAILURE, "removing ll from empty list fails");
    // "removing ll from position outside of range fails"
    charLl ll1 = new_charLl();
    for (size_t i = 0; i < 10; i++) {
        ll1 = append_charLl(ll0, (char) i).result;
    }
    charLlRes res2 = rem_charLl(ll1, 99);
    fails += test_ResultType(res2.type, FAILURE, "removing ll from position outside of range fails");
    charLlRes res3 = rem_charLl(ll1, -99);
    fails += test_ResultType(res3.type, FAILURE, "removing ll from position outside of range fails");
    // free_charLl(ll1);

    charLl ll2 = new_charLl();
    for (size_t i = 0; i < 10; i++) {
        ll2 = append_charLl(ll2, (char) i).result;
    }
    fails += test_size_t(ll2.count, 10, "correct amount fo items in ll");
    charLlRes res4 = rem_charLl(ll2, 5);
    fails += test_ResultType(res4.type, SUCCESS, "removing ll from existing forward index works");
    fails += test_size_t(res4.result.count, 9, "removing ll from existing forward index works");

    // "removing ll first element"
    // "removing ll last element"
    // "removing ll from existing backward index works"
    // "emptying list through remove works"

    return fails;
}
int test_list_delete(void) {
    int fails = 0;

    // "ll deletes the element"
    // "ll deletes only the first element"
    // "del ll fails if element was not found"
    // "del ll fails on empty list"

    return fails;
}
int test_lists(void) {
    int fails = 0;
    fails += test_list_remove();
    fails += test_list_delete();
    fails += test_list_get();
    fails += test_list_append();
    fails += test_list_prepend();
    return fails;
}

int main(void) {
    int fails = 0;
    fails += test_array_macros();
    fails += test_cmp();
    fails += test_dynamic_arrays();
    fails += test_math();
    fails += test_string_operations();
    fails += test_lists();

    if (fails > 0) {redln("%d\tFAILED TESTS", fails)}
    else {greenln("\tTESTS PASSES!")};
    return -fails;
}

