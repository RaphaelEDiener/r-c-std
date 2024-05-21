#include <stdio.h>

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
    return ((c <= 'z' && c >= 'a') || c == '_');
}

unsigned char is_upper(char c) {
    return (c <= 'Z' && c >= 'A');
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
