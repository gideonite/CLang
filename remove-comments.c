#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 2000    /* max line input size */

int getline(char s[]);

int main(int argc, char **argv)
{
    int state;
    int DOUBLE_SLASH = 1;
    int SLASH_STAR = 2;
    char b[MAXLINE];

    while (0 != (getline(b))) {
        state = 0;

        if ('/' == b[0] && '/' == b[1])
            state = DOUBLE_SLASH;

        if (state != DOUBLE_SLASH) {
            printf("%s", b);
        }
    }
}

int getline(char s[])
{
    int c;
    int i = 0;
    while ( ((c = getchar()) != EOF) && (i <= (MAXLINE - 1))) {
        s[i] = c;
        i++;

        if ('\n' == c)
            break;
    }
    s[i] = '\0';

    return i;
}
