#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>  /* isalpha(char c) */

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0);

char* mapfile(char* filename, int* fd_p, size_t* size_p)
{
    int fd;
    char *addr;
    size_t size = *size_p;
    struct stat sb;

    /* Open the input file. */
    fd = open(filename, O_RDONLY);

    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    size = sb.st_size;

    /* Memory map the file. */
    addr = mmap(NULL,
            size,
            PROT_READ,
            MAP_PRIVATE,
            fd,
            0);

    /* Make these avaiable to the caller */
    *fd_p = fd;
    *size_p = size;

    return addr;
}

/**
 * Loops over every character in the file and counts the numbers of lines,
 * word, and chars. Populates the given variables with the corresponding
 * values.
 */
int wc(char* filename, int* line_count_p, int* word_count_p, int* char_count_p)
{
    int fd;
    size_t size;
    char* addr = mapfile(filename, &fd, &size);

    int char_count = size;      /* well that was easy, thanks `size_t`*/
    int line_count = 0;
    int word_count = 0;

    /**
     * For every character in the mapped file, if the current character is a
     * space and the previous character is not a space, then we have
     * effectively exited a word and we should incremement our word count. The
     * rest is trivial.
     */
    int inword = 0;
    char prev = *addr;
    for (int i=0; i<size; i++) {
        char curr = *(addr+i);

        if (isspace(curr) && !isspace(prev)) {
            word_count++;
            inword = 0;
        }

        if (curr == '\n')
            line_count++;

        prev = curr;
    }

    munmap(addr, size);

    /* Make these avaiable to the caller */
    *line_count_p = line_count;
    *word_count_p = word_count;
    *char_count_p = char_count;

    return close(fd);
}

int main(int argc, char **argv)
{
    for (int i=1; i<argc; i++)
    {
        char* filename = argv[i];
        int line_count, word_count, char_count;
        wc(filename, &line_count, &word_count, &char_count);
        printf("\t%d\t%d\t%d\t%s\n", line_count, word_count, char_count, filename);
    }
}
