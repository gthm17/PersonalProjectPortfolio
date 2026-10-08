#include <stdio.h>
#include <string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

void check();

int main() {
    printf("GRAMMER IS E->E+E\nE->E*E\nE->(E)\nE->id");

    printf("\n Enter input string:");
    scanf("%15s", a);

    c = strlen(a);

    strcpy(ac, "SHIFT->");

    printf("\n$%s\tSTACK\tACTIONS", a);

    for (k = 0, j = 0; j < c; k++, j++) {
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i++] = 'i';
            stk[i++] = 'd';
            stk[i] = '\0';

            a[j] = ' ';
            a[j + 1] = ' ';

            printf("\n$%s\t%s$\t%s id", a, stk, ac);

            check();

            j++;
        }
        else {
            stk[i++] = a[j];
            stk[i] = '\0';

            a[j] = ' ';

            printf("\n$%s\t%s$\t%s symbol", a, stk, ac);

            check();
        }
    }

    check();

    if (strcmp(stk, "E") == 0) {
        printf("\n\nString Accepted\n");
    }
    else {
        printf("\n\nString Rejected\n");
    }

    return 0;
}

void check() {
    strcpy(ac, "REDUCE TO E");

    for (z = 0; z < i - 1; z++) {
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';

            for (k = z + 1; k < i - 1; k++) {
                stk[k] = stk[k + 1];
            }

            i--;
            stk[i] = '\0';

            printf("\n$%s\t%s$\t%s", a, stk, ac);

            z = -1;
        }
    }

    for (z = 0; z < i - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E';

            for (k = z + 1; k < i - 2; k++) {
                stk[k] = stk[k + 2];
            }

            i = i - 2;
            stk[i] = '\0';

            printf("\n$%s\t%s$\t%s", a, stk, ac);

            z = -1;
        }
    }

    for (z = 0; z < i - 2; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';

            for (k = z + 1; k < i - 2; k++) {
                stk[k] = stk[k + 2];
            }

            i = i - 2;
            stk[i] = '\0';

            printf("\n$%s\t%s$\t%s", a, stk, ac);

            z = -1;
        }
    }

    for (z = 0; z < i - 2; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' &&
            stk[z + 2] == ')') {
            stk[z] = 'E';

            for (k = z + 1; k < i - 2; k++) {
                stk[k] = stk[k + 2];
            }

            i = i - 2;
            stk[i] = '\0';

            printf("\n$%s\t%s$\t%s", a, stk, ac);

            z = -1;
        }
    }
}