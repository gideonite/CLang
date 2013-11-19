#include <stdlib.h>
#include <stdio.h>

#define MAXLINE 2000    /* max line input size */

int getline(char s[]);

void double_slash();
void code();
void slash(char prev);
void star(char _star);
void star_comment();

int main(int argc, char **argv)
{
    code();
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

void code()
{
    char c = getchar();

    if (c !=EOF) {
        if ('/' == c)
            slash(c);
        else {
            putchar(c);
            code();
        }
    }
}

void slash(char prev)
{
    char curr = getchar();

    if ('/' == curr)
        double_slash();

    else if ('*' == curr)
        star_comment();

    else {
        putchar(prev);
        putchar(curr);
        code();
    }
}

void double_slash()
{
    char c = getchar();

    if (c == '\n') {
        putchar(c);
        code();
    }
    else
        double_slash();
}

void star_comment()
{
    char curr = getchar();

    if ('*' == curr)
        star(curr);
    else
        star_comment();
}

void star(char _star)
{
    char curr = getchar();

    if ('/' == curr)
        code();
    else
        star_comment();
}