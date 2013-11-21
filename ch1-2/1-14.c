#include <stdlib.h>
#include <stdio.h>

/* write a program that prints the frequencies of characters in its input */

#define MAX_NO_CHARS 255

main()
{
    int c, i;
    int chars[MAX_NO_CHARS];
    int total_chars;

    // initialize chars
    for (i = 0; i < MAX_NO_CHARS; i++) {
        chars[i] = 0;
    }

    while ( (c = getchar()) != EOF) {
        ++total_chars;
        ++chars[(char) c];
    }

    for (i=0; i < MAX_NO_CHARS; i++) {
        if (chars[i] != 0) {
            printf("%c : %.3f\n", i, (float) chars[i] / total_chars);
        }
    }
}

