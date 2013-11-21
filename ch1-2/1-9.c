#include <stdlib.h>
#include <stdio.h>

main()
{
    int c;
    while ((c = getchar()) != EOF) {
        int next = getchar();
        if ( (c == ' ') &&  (next == ' '))
            ;
        else {
            putchar(c);
            putchar(next);
        }
    }
}

