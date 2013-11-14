#include <stdlib.h>
#include <stdio.h>

#define IN  1
#define OUT 0

/* a program that prints its input, one word per line */

main()
{
    int c;
    int state = IN;
    while ( (c = getchar()) != EOF) {

        if (c == '\n' || c == '\t' || c == ' ') {
            state = OUT;
        }
        else if (state == OUT) {
            putchar('\n');
            state = IN;
        }
        if (state == IN) {
            putchar(c);
        }
    }

    putchar('\n');
}

