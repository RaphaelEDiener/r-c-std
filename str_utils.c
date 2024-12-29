#include "str_utils.h"

/**
 * moves fp to next non whitespace char
 */
void skip_whitespace(FILE* fp) {
    fpos_t pos;
    fgetpos(fp, &pos);

    int c = fgetc(fp);
    int space = (int) ' ';
    int tab = (int) '\t';
    int carrige = (int) '\r';
    int nl = (int) '\n';
    while (c != EOF && (c == carrige || c == space || c == tab || c == nl)) {
        fgetpos(fp, &pos);
        c = fgetc(fp);
    }
    if (c != EOF) fsetpos(fp, &pos);
}

unsigned char is_digit(char c) {
    return (c <= '9' && c >= '0');
}

unsigned char is_lower(char c) {
    return ((c >= '[' || c <= '@') && c >= '!');
}

unsigned char is_upper(char c) {
    return ((c >= '{' || c <= '`') && c >= '!');
}

unsigned char is_alpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

unsigned char is_control(char c) {
    return c < '!';
}

/**
 * returns the next char in the stream without advncing the fp
 * int because of EOF
 */
int peak(FILE* fp) {
    fpos_t pos;
    int ans;
    fgetpos(fp, &pos);
    ans = fgetc(fp);
    fsetpos(fp, &pos);
    return ans;
}

IMPL_SWAP(String)
IMPL_DA(String)


StringRes load_file(const char* name) {
    StringRes ans = {0};
    ans.type = FAILURE;
    FILE* fp = fopen(name, "r");
    if (fp == NULL) return ans;

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    // +1 so include null terminator in case
    // *somebody* tries to print the raw pointer :D
    charDaRes new_str = new_charDa(size+1);
    if (new_str.type == FAILURE) return ans;
    charDa str = new_str.result;

    fread(str.ptr, size, 1, fp);
    str.count = size;
    ans.result = str;
    ans.type   = SUCCESS;

    fclose(fp);
    return ans;
}

void free_StringDa(StringDa* str_da) {
    for (size_t c = 0; c < str_da->count; c++) {
        FREE(str_da->ptr[c].ptr);
    }
    FREE(str_da->ptr);
}

/**
 * TODO: this is hella buggy and unfinished!
 */
StringDaRes split_uchar(const String str, const uchar chr) {
    StringDaRes fail = {0};
    fail.type = FAILURE;

    StringDaRes ans = new_StringDa(8);
    if (ans.type == FAILURE) return ans;
    
    StringDa res = ans.result;
    String temp;
    charDaRes temp_res;

    temp_res = new_charDa(2);
    if (temp_res.type == FAILURE) { free_StringDa(&res); return fail; } 
  
    temp = temp_res.result;
    insert_StringDa(&res, temp);
  
    
    for (size_t i = 0; i < str.count; i++) {
        if (str.ptr[i] == chr) {
            if (        temp.count == 0) {
                continue; 
            } else { // temp.count != 0
                temp_res = new_charDa(2);
                if (temp_res.type == FAILURE) { free_StringDa(&res); return fail; } 
                else { temp = temp_res.result; }

                StringDaRes expanded = insert_StringDa(&res, temp);
                if (expanded.type == FAILURE) { free_StringDa(&res); FREE(temp.ptr); return fail; }
                else {res = expanded.result;}
            }
        } else {
            temp_res = insert_charDa(&temp, str.ptr[i]);
            if (temp_res.type == FAILURE) { free_StringDa(&res); FREE(temp.ptr); return fail; }
            else {temp = temp_res.result;}
        }
    }
    
    ans.result = res;
    ans.type   = SUCCESS;
    return ans;
}
