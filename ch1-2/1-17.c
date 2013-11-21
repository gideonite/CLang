#include <stdlib.h>
#include <stdio.h>

#define THRESHOLD   80
#define MAXLINE     1000    /* max line input size */

/* print all lines that are longer than 80 chars */

/* getline: Maximally read a line into s. Returns the length of the line
 * regardless of whether or not it is longer than maxline.*/
int _getline(char s[], int lim);

/* printline: Prints a string to stdout. */
int printstr(char s[]);

int main(int argc, char **argv)
{
    int len;
    char line[MAXLINE];
    while ( (len = _getline(line, MAXLINE)) != 0) {
        if (len > 80) {
            printstr(line);
        }
    }
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
