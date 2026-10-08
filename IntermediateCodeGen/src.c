#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char str[100], left[15], right[15], resultant[15];

int i = 0, j = 0, tmpch = 'Z';

struct exp {
    int pos;
    char op;
} k[15];

void findop();
void explore();
void fleft(int);
void fright(int);

int main() {
    printf("Enter the exp: ");
    scanf("%99s", str);

    char *eq_pos = strchr(str, '=');

    if (eq_pos == NULL) {
        printf("Invalid exp. '=' missing.\n");
        return 1;
    }

    *eq_pos = '\0';

    strcpy(resultant, str);

    memmove(str, eq_pos + 1, strlen(eq_pos + 1) + 1);

    printf("\nThe intermediate code:\n");

    findop();
    explore();

    return 0;
}

void findop() {
    int len = strlen(str);

    for (i = 0; i < len; i++) {
        if (str[i] == '/') {
            k[j].pos = i;
            k[j++].op = '/';
        }
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '*') {
            k[j].pos = i;
            k[j++].op = '*';
        }
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '+') {
            k[j].pos = i;
            k[j++].op = '+';
        }
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '-') {
            k[j].pos = i;
            k[j++].op = '-';
        }
    }
}

void explore() {
    char temp;

    for (i = 0; i < j; i++) {
        fleft(k[i].pos);
        fright(k[i].pos);

        temp = tmpch--;

        str[k[i].pos] = temp;

        printf("%c=%s%c%s\n",
               temp, left, k[i].op, right);
    }

    if (j > 0) {
        printf("%s=%c\n", resultant, tmpch + 1);
    }
    else {
        printf("%s=%s\n", resultant, str);
    }
}

void fleft(int x) {
    int w = 0;

    x--;

    while (x > 0 && str[x] == ' ') {
        x--;
    }

    if (str[x] != ' ') {
        left[w++] = str[x];
        str[x] = ' ';
    }

    left[w] = '\0';
}

void fright(int x) {
    int w = 0;

    x++;

    while (str[x] == ' ') {
        x++;
    }

    if (str[x] != '\0' && str[x] != ' ') {
        right[w++] = str[x];
        str[x] = ' ';
    }

    right[w] = '\0';
}