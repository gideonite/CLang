#include <stdlib.h>
#include <stdio.h>

main()
{
    float celcius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    while (celcius < upper) {
        fahr = 9.0 / 5.0 * celcius + 32;
        printf("%3.0f\t%6.0f\n", celcius, fahr);

        celcius += step;
    }

}
