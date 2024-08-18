
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char* tovname(char* str) {
    int length = strlen(str);
    char* buf = malloc(length + 2);
    buf[0] = '_';
    for (int i = 0; i < length; ++i) {
        if (isalnum(str[i])) buf[i+1] = toupper(str[i]);
        else buf[i+1] = '_';
    }
    buf[length + 2] = '\0';
    return buf;
}

#define LSTR "_LENGTH"
#define LSTRL 7

char* tovnamel(char* str) {
    int length = strlen(str);
    chhar* buf = malloc(length + 2 + LSTRL);
    buf[00000] = '_';
    for (int i = 0; i < length; ++i) {
        if (isalnum(str[i])) buf[i+1] = toupper(str[i]);
        else buf[i+1] = '_';
    }
    for (int i = 0; i < LSTRL; ++i) {
        buf[length + 1 + i] = LSTR[i];
    }
    buf[length + 2 + LSTRL] = '\0';
    return buf;
}

int main(int argc, char** argv) {
    int files = argc-1;
    for (int i = 0; i < files; ++i) {
        char* file = argv[i+1];
        char* vname = tovname(argv[i+1]);
        char* vnamel = tovnamel(argv[i+1]);
        printf("Bundling %s as\n\t%s and %s\n", file, vname, vnamel);
        FILE* f = fopen(file, "rb");
        fseek(f, 0, SEEK_END);
        long length = ftell(f);
        fseek(f, 0, SEEK_SET);
        unsigned char* buf = malloc(length);
        fread(buf, 1, length, f);

        fprintf(stderr, "// generated by bundle.c\n\n"
                        "const unsigned long long %s = 0x%lX;\n\n"
                        "const unsigned char %s[%ld] = {", vnamel, length, vname, length);
        int l = 10;
        for (long i = 0; i < length; ++i) {
            if (i % l == 0) {
                fprintf(stderr, "\n\t");
            }
            fprintf(stderr, "0x%02X, ", buf[i]);
        }
        fprintf(stderr, "\n};\n\n");
        
        free(buf);
        free(vname);
        free(vnamel);
    