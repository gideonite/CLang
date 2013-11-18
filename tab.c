#include <stdio.h>

#define MAXLINE 1000    /* max line input size */
#define TABWIDTH 4

int getline(char s[], int lim);
int putstr(char s[]);
int length(char s[]);
void detab(char detabbed[], char s[]);
int tab_distance(int index);
void entab(char entabbed[], char s[]);
void fold_lines(char s[]);

int main(int argc, char **argv)
{

    // read in file line by line, printing out each line reversed
    //char line[MAXLINE];
    //char detabbed[MAXLINE];
    //char entabbed[MAXLINE];
    //while (getline(line, MAXLINE) != 0) {
    //    detab(detabbed, line);

    //    //putstr(detabbed);
    //    //putchar('\n');

    //    entab(entabbed, detabbed);
    //    putstr(entabbed);
    //    putchar('\n');
    //}

    char buffer[MAXLINE];
    fold_lines(buffer);
}

/*
 * Exercise 1-20
 *
 * Replace tabs with the proper number of spaces.
 *
 * */
void detab(char detabbed[], char s[])
{
    char c;
    int s_index = 0;
    int detab_index = 0;

    // zero out detabbed
    for (int i=0; detabbed[i] != '\0'; i++) {
        detabbed[i] = 0;
    }

    for (; ((c = s[s_index]) != '\0') && s_index < MAXLINE-1; s_index++) {
        if (s[s_index] == '\t') {

            int dist = tab_distance(detab_index);

            for (int j=0; j < dist; j++)
                detabbed[detab_index + j] = ' ';
            detab_index += dist;
        }
        else {
            detabbed[detab_index] = s[s_index];
            detab_index++;
        }
    }

    detabbed[detab_index] = '\0';
}

/*
 * Exercise 1-21
 *
 * Replaces spaces with the minimum number of tabs and spaces to achieve the
 * same spacing. If if comes down to choosing between a single tab and
 * single space, choose a single space.
 *
 * If a string has only spaces, returns [\0]
 */
void entab(char entabbed[], char s[])
{
    int i;
    char c;
    int space_count = 0;
    int j = 0;      // entabbed index

    for (i=0; (c = s[i]) != '\0'; i++) {

        if (c == ' ') {
            space_count++;
        } else {
            if (space_count > 0) {
                int tabs = (i / TABWIDTH) - ((i - space_count) / TABWIDTH);
                int spaces = i % TABWIDTH;

                // write tabs
                for (int k=0; k < tabs; k++) {
                    entabbed[j] = '\t';
                    j++;
                }

                // write spaces
                for (int k=0; k < spaces; k++) {
                    entabbed[j] = ' ';
                    j++;
                }
                space_count = 0;
            }
            entabbed[j] = c;
            j++;
        }
    }
    entabbed[j] = '\0';
}

#define LINE_LENGTH 80
int is_space(char c);

/*
 * Exercise 1-22
 *
 * "Fold" long lines of input into two or more shorter lines after the last
 * non-blank character before the nth column of input.
 */
void fold_lines(char s[])
{
    // for each c in s, put c in b (the index is i % LINE_LENGTH) , when i %
    // LINE_LENGTH == 0, write out b.
    //
    // Need to handle lines terminated by spaces.
    //

    int c, i;

    for (i=1; (c = getchar()) != EOF; i++) {
        putchar(c);

        if (i >= LINE_LENGTH) {
            putchar('\n');
            i = 1;
        }

        if (c == '\n')
            i = 1;

        if (is_space(c)) {
            int space_count = 0;
            while ( is_space(c = getchar()) && c != EOF && c != '\n')
                space_count++;

            int newlines = space_count / LINE_LENGTH;
            for (int j=0; j < newlines; j++) {
                putchar('\n');
                i++;
            }
        }
    }
}

int is_space(char c)
{
    return (c == ' ' || c == '\t');
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

/* Returns distance to the nearest tab stop. */
int tab_distance(int index)
{
    return TABWIDTH - (index % TABWIDTH);
}
