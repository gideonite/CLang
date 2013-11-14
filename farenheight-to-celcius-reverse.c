#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

main()
{
    int fahr = 0;
    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP) {
        printf("%3d %6.1f\n", fahr, (5.0/9.0) * (fahr - 32));
    }

    while (1) {
        char in = getchar();
        putchar(in);
    }
}

