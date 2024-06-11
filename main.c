#include "rstd.h"

void add1p(int* x) {
    (*x)++;
}
int add2(int x) {
    return x+2;
}
int add2p(int* x) {
    return (*x)+2;
}
char eq1(int x) {
    return x == 1;
}
char false(int x) {
    return 0 && (char) x;
}
char eq1p(int* x) {
    return *x == 1;
}
char falsep(int* x) {
    return 0 && (char) *x;
}
char positive(int x) {
    return x >= 0;
}
char positivep(int* x) {
    return *x >= 0;
}
char negative(int x) {
    return x <= 0;
}
char negativep(int* x) {
    return *x <= 0;
}
uchar int_to_uchar(int x) {
    return (char) (x % 256);
}
uchar intp_to_uchar(int* x) {
    return (char) ((*x) % 256);
}
int add(int x, int y) {
    return x + y;
}
int addp(int x, int* y) {
    return x + (*y);
}
int addpp(int* x, int* y) {
    return (*x) + (*y);
}
static int counter_ = 0;
void inc_counter(int* _ignore) {
    (void)_ignore;
    counter_++;
}
char to_zero(char* ignore) {
    (void)ignore;
    return 0;
}
char is_zero(char* x) {
    return 0 == *x;
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
    fails += test_char(all_charDa(da0, is_zero), 1, "all finds all cases");

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

int test_dynamic_arrays(void) {
    int fails = 0;
    fails += test_da_creation();
    fails += test_da_insertion();
    fails += test_da_for_each();
    fails += test_da_all();
    return fails;
}

/**
 * Leaks in tests are fiiiiine ~
 */
int main(void) {
    int fails = 0;
    fails += test_array_macros();
    fails += test_cmp();
    fails += test_dynamic_arrays();

    if (fails > 0) {redln("%d\tFAILED TESTS", fails)}
    else {greenln("\tTESTS PASSES!")};
    return -fails;
}

