#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "lexemes.h"
#include "utils.h"

int i;
FILE *yyin;
char *yytext;

// Utility Function To Check Reserved Keyword Token

int checkReservedKeyword(char *word) {
    if (strcmp(word, "while") == 0) return WHILE_TOK;
    if (strcmp(word, "for") == 0) return FOR_TOK;
    if (strcmp(word, "if") == 0) return IF_TOK;
    if (strcmp(word, "else") == 0) return ELSE_TOK;
    if (strcmp(word, "int") == 0) return INT_TOK;
    if (strcmp(word, "float") == 0) return FLOAT_TOK;

    return 0;
}

int checkSingleCharacterLexemes(char *word) {
    if (strcmp(word, "(") == 0) return LPAREN_TOK;
    if (strcmp(word, ")") == 0) return RPAREN_TOK;
    if (strcmp(word, ">") == 0) return GT_TOK;
    if (strcmp(word, "<") == 0) return LT_TOK;
    if (strcmp(word, "=") == 0) return EQ_TOK;
    if (strcmp(word, "-") == 0) return MINUS_TOK;
    if (strcmp(word, "+") == 0) return PLUS_TOK;
    if (strcmp(word, "*") == 0) return MULTIPLY_TOK;
    if (strcmp(word, "/") == 0) return DIVISION_TOK;
    if (strcmp(word, ";") == 0) return SEMICOLON_TOK;

    return 0;
}

int checkValidIdentifier(char *word) {
    // first letter of identifier should be letter or underscore
    if (word[0] != '_' && !isLetter(word[0])) return 0;

    // can only contain letters (uppercase and lowercase), digits and underscore
    for (i = 0; i < (int)strlen(word); i++) {
        if (word[0] != '_' && !isAlphanumeric(word[0])) return 0;
    }

    return ID_TOK;
}

int checkConstant(char *word) {
    int period_count = 0;

    // Loop through each character of the word
    for (i = 0; i < (int)strlen(word); i++) {
        // If a period (.) is found and it's the first one, it could be a floating-point constant
        if (word[i] == '.' && period_count < 1) {
            period_count++;
        } else if (!isDigit(word[i])) {
            return 0; // If any character is not a digit or a period, it's not a constant
        }
    }

    // If no period is found, consider it as an integer constant
    if (period_count == 0)
        return INTCONST;
    else if (period_count == 1)
        return FLOATCONST;
    else
        return 0;
}
int yylex() {
    char *word = malloc(256);
    int flag;
    fscanf(yyin, "%s", word);
    yytext = word;

    if ((flag = checkReservedKeyword(word))) return flag;
    if ((flag = checkSingleCharacterLexemes(word))) return flag;
    if ((flag = checkValidIdentifier(word))) return flag;
    if ((flag = checkConstant(word))) return flag;

    return 0;
}
void lexer_main(const char *filename) {
    yyin = fopen(filename, "r");

    if (yyin == NULL) {
        printf("%s: no such file\n", filename);
        return;
    }

    int token;
    while (!feof(yyin)) {
        token = yylex();
        if (token)
            printf("[TOKEN] [%s] -> [%d]\n", yytext, token);
        else
            printf("[TOKEN NOT FOUND YET]\n");
    }
    fclose(yyin);
}