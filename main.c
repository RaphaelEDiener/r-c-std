#include "rstd.h"

char test(int* x){
    return (*x % 2) == 0;
}

void print_char(char* x) {
    printf("%c\n", (*x));
}

char add_3(char* x){
    return *x + 3;
}

int add(int* x, int* y){
    return *x + *y;
}

int main() {
    printf("%p\n", &test);
    truthy_int_fn fn = &test;
    int arr[5] = {0,2,4,5,8};
    intWp my_wp = {sizeof(int), 5, arr};
    printf("%d\n", all_int(my_wp, fn));
    printf("sum: %d\n", fold_int_to_int(my_wp, &add, 0));

    arr[3] = 6;
    printf("%d\n", all_int(my_wp, fn));

    new_wp(second, char, 3);
    _second[0] = 'a'; 
    _second[1] = 'b';
    _second[2] = 'c';
    for_each_char(second, &print_char);

    mapip_char(second, add_3);
    for_each_char(second, &print_char);
    
    return 0;
}

