#include <stdlib.h>
#include <stdio.h>

/*
 * Exercise 1-23
 *
 * Remove comments from a C program
 *
 * Basic Idea: Use mutual recursion to implement a finite state machine.
 * Hopefully, whoever uses this program isn't writing tons and tons of
 * comments =). To accomodate these terrrrible programmers, use trampolines,
 * but that is beyond the current of this exercise.
 *
 * */

void double_slash();
void code();
void slash(char prev);
void star(char _star);
void star_comment();

int main(int argc, char **argv)
{
    code();
}

void code()
{
    char c = getchar();

    if (c !=EOF) {
        if ('/' == c)
            slash(c);
        else {
            putchar(c);
            code();
        }
    }
}

void slash(char prev)
{
    char curr = getchar();

    if ('/' == curr)
        double_slash();

    else if ('*' == curr)
        star_comment();

    else {
        putchar(prev);
        putchar(curr);
        code();
    }
}

void double_slash()
{
    char c = getchar();

    if (c == '\n') {
        putchar(c);
        code();
    }
    else
        double_slash();
}

void star_comment()
{
    char curr = getchar();

    if ('*' == curr)
        star(curr);
    else
        star_comment();
}

void star(char _star)
{
    char curr = getchar();

    if ('/' == curr)
        code();
    else
        star_comment();
}
