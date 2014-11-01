#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <unistd.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0);

/* Count away */
int* count_words_from_addr(int length, char* start_addr)
{
    int char_count = 0;
    int space_count = 0;
    int newline_count = 0;
    int i;
    char curr;
    char prev;
    for (i=0; i < length; i++) {
        prev = *(start_addr);       // TODO this should probably be rethought.
        curr = *(start_addr+i);

        if ((' ' != prev && '\t' != prev && '\n' != prev)
                && ((' ' == curr) || ('\t' == curr) || ('\n' == curr)))
            space_count++;

        if ('\n' == curr)
            newline_count++;

        char_count++;
    }

    return (int[3]) {char_count, space_count, newline_count};
}

int* count_words(char* filename)
{
    int fd, close_success;
    char *addr;
    size_t length;
    struct stat sb;

    /* Open the input file. */
    fd = open(filename, O_RDONLY);

    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    /* Memory map the file. */
    addr = mmap(NULL,
            length,
            PROT_READ,
            MAP_PRIVATE,
            fd,
            0);

    int* counts = count_words_from_addr(length, addr);

    /* Free the memory */
    munmap(addr, length);

    /* Close the input file */
    close_success = close(fd);

    // TODO do something with close_success.

    return counts;
}

int main(int argc, char **argv)
{
    for (int i = 1; // argv[0] == name of this file
            i < argc; i++) {
        char* filename = argv[i];
        int* counts = count_words(filename);
        printf("%d	%d	%d	%s\n", counts[0], counts[1], counts[2], filename);
    }
}
