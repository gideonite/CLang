#include <stdlib.h>
#include <stdio.h>

/* write a program that prints out a histogram of the lengths of words in the
 * its input */

#define IN  1
#define OUT 0
#define MAX_WORD_LENGTH 100

main()
{
    int c, i;
    int state = IN;
    int histogram[MAX_WORD_LENGTH]; // no words are larger than 100
    int curr_length = 0;

    // initialize histogram
    for (i = 0; i < MAX_WORD_LENGTH; i++) {
        histogram[i] = 0;
    }

    while ( (c = getchar()) != EOF) {
        if (c == '\n' || c == '\t' || c == ' ') {
            state = OUT;
        }
        else if (state == OUT) {
            histogram[curr_length] += 1;

            curr_length = 0;
            state = IN;
        }
        if (state == IN) {
            ++curr_length;
        }
    }
    ++histogram[curr_length];       // EOF counts as a word delimiter

    for (i = 0; i < MAX_WORD_LENGTH; i++) {
        int j;
        if (histogram[i] != 0) {
            printf("%d : ", i);
            for (j = 0; j < histogram[i]; j++)
                printf("#");
            printf("\n");
        }
    }
}

