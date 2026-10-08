#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int iskeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "else", "enum", "extern", "float",
        "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned",
        "void", "volatile", "while"
    };

    int i, flag = 0;

    for (i = 0; i < 32; i++) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

int main() {
    char ch, buffer[15], operators[] = "+-*%=";
    FILE *fp;
    int i, j = 0;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("error while opening the file \n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        for (i = 0; i < 5; i++) {
            if (ch == operators[i]) {
                printf("%c is operators \n", ch);
            }
        }

        if (isalnum(ch)) {
            if (j < 14) {
                buffer[j++] = ch;
            }
        }
        else if ((ch == ' ' || ch == '\n' || ch == '\t') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;

            if (iskeyword(buffer) == 1) {
                printf("%s is keyword \n", buffer);
            }
            else {
                printf("%s is identifier\n", buffer);
            }
        }
    }

    if (j != 0) {
        buffer[j] = '\0';

        if (iskeyword(buffer) == 1) {
            printf("%s is keyword \n", buffer);
        }
        else {
            printf("%s is identifier\n", buffer);
        }
    }

    fclose(fp);
    return 0;
}