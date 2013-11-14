#include <stdlib.h>
#include <stdio.h>

#define STEP 20
#define LOWER 0
#define UPPER 100

int fahr_to_celcius(int fahr)
{
    return (5.0/9.0) * (fahr - 32);
};

int main(int argc, char **argv)
{
    int i, fahr;
    for (fahr=LOWER; fahr <= UPPER; fahr+=STEP)
        printf("%3d\t%3d\n", fahr, fahr_to_celcius(fahr));
}

