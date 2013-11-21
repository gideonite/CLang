#include <stdlib.h>
#include <stdio.h>

/* a program that counts blanks, tabs, and newlines*/

main()
{
    int c;
    int blanks = 0;
    int tabs = 0;
    int newlines = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        }
        else if (c == '\t')
            ++tabs;
        else if (c == '\n')
            ++newlines;
    }

    printf("blanks: %d tabs: %d newlines: %d\n", blanks, tabs, newlines);
}
