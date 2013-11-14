#include <stdlib.h>
#include <stdio.h>

/* Program to remove trailing blanks and tabs from each line of input */

#define MAXLINE 1000    /* max line input size */

int _getline(char s[], int lim);
int printstr(char s[]);

/* Removes trailing whitespace from a string */
int trailing_trim(char s[]);

int is_space(char c);

int main(int argc, char **argv)
{
    char s[] = "abc          ";
    trailing_trim(s);
    printf("%s.", s);

    char blank[] = " ";
    trailing_trim(blank);
    printf("%s.", blank);
}

int _getline(char s[], int lim)
{
    int c;
    int i = 0;
    while ( ((c = getchar()) != EOF) && (i <= (lim - 1)) && (c != '\n')) {
        s[i] = c;
        i++;
    }
    s[i+1] = '\0';

    return i;
}

int printstr(char s[])
{
    int i = 0;
    char c;

    while ( (c = s[i]) != '\0') {
        putchar(c);
        i++;
    }

    return i;
}

int is_space(char c)
{
    return (c == '\t' || c == ' ');
}

int trailing_trim(char s[])
{
    // find the length of s
    int len = 0;
    while (s[len] != '\0') len++;

    while ( len > 0 &&
            (s[len-1] == ' ' || s[len-1] == '\t' || s[len-1] == '\n')) {
        s[len-1] = '\0';
        len--;
    }

    return len;
}
