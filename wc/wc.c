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
int count_words_from_addr(int length, char* start_addr)
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

    return newline_count;
}

int count_words(char* filename)
{
    int fd, close_success;
    char *addr;
    off_t offset, pa_offset;
    size_t length;
    struct stat sb;

    /* Open the input file. */
    fd = open(filename, O_RDONLY);

    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    int page_size = sysconf(_SC_PAGE_SIZE);
    int minus_pagesize = ~(page_size - 1);
    //offset = page_size * 2;
    offset = 0;
    pa_offset = offset & minus_pagesize;   // offset % page_size == 0. TODO why?

    length = sb.st_size - offset;

    /* Memory map the file. */
    addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd,
            pa_offset);

    int newline_count = count_words_from_addr(length, addr);

    munmap(addr, length);

    /* Print the resulting counts. */
    //printf("%d %d %d %s\n", newline_count, space_count, char_count, filename);

    /* Close the input file. */
    // TODO is there a finally clause in C? How can I be absolutely sure that this file is closed?
    close_success = close(fd);      // TODO not using this right now

    return newline_count;
}

int main(int argc, char **argv)
{
    for (int i = 1; // argv[0] == name of this file
            i < argc; i++) {
        char* filename = argv[i];
        int count = count_words(filename);
        printf("%d	%d	%d	%s", count, count, count, filename);        // TODO how to return multiple values
    }

}
