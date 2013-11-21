#include <stdlib.h>
#include <stdio.h>

/* Write a function `reverse` that reverses the character string. Use it to
 * write a program that reverses its input line by line. */

#define MAXLINE 1000    /* max line input size */

int length(char s[]);
int getline(char s[], int lim);
void reverse(char s[]);
void test();
int putstr(char s[]);

int main(int argc, char **argv)
{
    // read in file line by line, printing out each line reversed
    char line[MAXLINE];
    while (getline(line, MAXLINE) != 0) {
        reverse(line);
        putstr(line);
        putchar('\n');
    }

    //test();
}

void reverse(char s[])
{
    // It'd be cool to do this with points to avoid having to count the list,
    // but this works for now
    int len = length(s);

    char tmp;
    for (int i = 0; i < len / 2; i++) {
        tmp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = tmp;
    }
}

int getline(char s[], int lim)
{
    int c;
    int i = 0;
    while ( ((c = getchar()) != EOF) && (i <= (lim - 1)) && (c != '\n')) {
        s[i] = c;
        i++;
    }
    s[i] = '\0';

    return i;
}

int putstr(char s[])
{
    int i = 0;
    char c;
    for (; (c = s[i]) != '\0'; i++) {
        putchar(c);
    }

    return i;
}

/* Finds the length of the string s (this means that \0 doesn't count) */
int length(char s[])
{
    int len = 0;
    while (s[len] != '\0')
        len++;

    return len;
}

void test()
{
    // tests
    printf("\n\ntest\n\n");
    printf("%d\n", 5 == length("12345"));
    printf("===============\n");

    char s[4];
    s[0] = 'a';
    s[1] = 'b';
    s[2] = 'c';
    s[3] = '\0';

    reverse(s);
    printf("%s\n", s);
}
