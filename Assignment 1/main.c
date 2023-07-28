// main.c
#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("USAGE: %s <source-file>\n", argv[0]);
    } else {
        lexer_main(argv[1]);
    }
    return 0;
}
