#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct expr
{
    char op[5];
    char op1[10];
    char op2[10];
    char res[10];
};

struct expr arr[20];
int n;

char name[20][10], val[20][10];   /* table of known constants */
int cnt = 0;

int isnum(char *s)
{
    return isdigit((unsigned char)s[0]) ||
           (s[0] == '-' && isdigit((unsigned char)s[1]));
}

/* remember var = value (overwrites old entry if present) */
void setconst(char *v, char *value)
{
    int j;
    for(j = 0; j < cnt; j++)
        if(strcmp(name[j], v) == 0) { strcpy(val[j], value); return; }
    strcpy(name[cnt], v);
    strcpy(val[cnt], value);
    cnt++;
}

/* var no longer holds a known constant */
void killconst(char *v)
{
    int j;
    for(j = 0; j < cnt; j++)
        if(strcmp(name[j], v) == 0) name[j][0] = '\0';
}

void input()
{
    int i;

    printf("Enter number of expressions: ");
    scanf("%d", &n);
    if(n > 20) n = 20;

    printf("Enter each expression as: op operand1 operand2 result\n");
    printf("(for assignment use: = value - var)\n");

    for(i = 0; i < n; i++)
    {
        scanf("%4s %9s %9s %9s",
              arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    }
}

void constant()
{
    int i, j, a, b, r;
    char temp[10];

    for(i = 0; i < n; i++)
    {
        /* propagate known constants into operands */
        for(j = 0; j < cnt; j++)
        {
            if(name[j][0] == '\0') continue;
            if(strcmp(arr[i].op1, name[j]) == 0) strcpy(arr[i].op1, val[j]);
            if(arr[i].op[0] != '=' && strcmp(arr[i].op2, name[j]) == 0)
                strcpy(arr[i].op2, val[j]);
        }

        /* assignment: x = value */
        if(arr[i].op[0] == '=')
        {
            if(isnum(arr[i].op1)) setconst(arr[i].res, arr[i].op1);
            else                  killconst(arr[i].res);
            continue;
        }

        /* both operands constant: fold */
        if(isnum(arr[i].op1) && isnum(arr[i].op2))
        {
            a = atoi(arr[i].op1);
            b = atoi(arr[i].op2);

            switch(arr[i].op[0])
            {
                case '+': r = a + b; break;
                case '-': r = a - b; break;
                case '*': r = a * b; break;
                case '/':
                    if(b == 0) { killconst(arr[i].res); continue; }
                    r = a / b;
                    break;
                default: killconst(arr[i].res); continue;
            }

            sprintf(temp, "%d", r);
            printf("%s = %s\n", arr[i].res, temp);

            setconst(arr[i].res, temp);

            strcpy(arr[i].op, "=");
            strcpy(arr[i].op1, temp);
            strcpy(arr[i].op2, "-");
        }
        else
        {
            killconst(arr[i].res);   /* result is not a known constant */
        }
    }
}

void output()
{
    int i;

    printf("\nOptimized code is:\n");
    for(i = 0; i < n; i++)
        printf("%s %s %s %s\n",
               arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
}

int main()
{
    input();
    constant();
    output();
    return 0;
}