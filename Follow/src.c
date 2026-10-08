#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0, fm = 0;
char prod[10][10], res[20], fres[20];
int visited[26];

void FIRST(char c);
void FOLLOW(char c);
void add(char c);
void addf(char c);

int main()
{
    int i, choice;
    char c;

    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("\nEnter productions like E=TR (use # for epsilon):\n");
    for(i = 0; i < n; i++)
    {
        printf("Production %d: ", i + 1);
        scanf("%9s", prod[i]);
    }

    do
    {
        m = 0;
        memset(visited, 0, sizeof(visited));   /* reset guard */

        printf("\nFind FOLLOW of: ");
        scanf(" %c", &c);
        FOLLOW(c);

        printf("FOLLOW(%c) = { ", c);
        for(i = 0; i < m; i++) printf("%c ", res[i]);
        printf("}\n");

        printf("\nContinue? (1/0): ");
        scanf("%d", &choice);
    } while(choice == 1);

    return 0;
}

void FOLLOW(char c)
{
    int i, j, k, len, hasEps;
    char next;

    if(visited[c - 'A']) return;               /* recursion guard */
    visited[c - 'A'] = 1;

    if(prod[0][0] == c) add('$');

    for(i = 0; i < n; i++)
    {
        len = strlen(prod[i]);
        for(j = 2; j < len; j++)
        {
            if(prod[i][j] != c) continue;

            if(j + 1 < len)
            {
                next = prod[i][j + 1];
                if(!isupper(next))
                    add(next);
                else
                {
                    fm = 0;                    /* FIRST uses its own array */
                    FIRST(next);
                    hasEps = 0;
                    for(k = 0; k < fm; k++)
                    {
                        if(fres[k] == '#') hasEps = 1;
                        else add(fres[k]);
                    }
                    if(hasEps) FOLLOW(prod[i][0]);
                }
            }
            else
                FOLLOW(prod[i][0]);
        }
    }
}

void FIRST(char c)
{
    int i;

    if(!isupper(c)) { addf(c); return; }

    for(i = 0; i < n; i++)
    {
        if(prod[i][0] == c)
        {
            if(prod[i][2] == '#') addf('#');
            else if(!isupper(prod[i][2])) addf(prod[i][2]);
            else FIRST(prod[i][2]);
        }
    }
}

void add(char c)
{
    int i;
    for(i = 0; i < m; i++) if(res[i] == c) return;
    res[m++] = c;
}

void addf(char c)
{
    int i;
    for(i = 0; i < fm; i++) if(fres[i] == c) return;
    fres[fm++] = c;
}