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

/* Initialize global counts */
//int char_count = 0;
//int space_count = 0;
//int newline_count = 0;
//
//size_t size;
//char* start;
//
///* Count away */
//void count_words_from_addr()
//{
//    int i;
//    char curr;
//    char prev;
//    for (i=0; i < size; i++) {
//        prev = *(start_addr);       // TODO this should probably be rethought.
//        curr = *(start_addr+i);
//
//        if ((' ' != prev && '\t' != prev && '\n' != prev)
//                && ((' ' == curr) || ('\t' == curr) || ('\n' == curr)))
//            space_count++;
//
//        if ('\n' == curr)
//            newline_count++;
//
//        char_count++;
//    }
//}

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

//int isalpha(char c)
//{
//    return c != ' ' && c != '\t' && c != '\n';
//}

int main(int argc, char **argv)
{
    int fd;
    size_t size;
    char* filename = "test-data/moby-dick.txt";
    char* addr = mapfile(filename, &fd, &size);

    int char_count = size;
    int line_count = 0;
    int word_count = 0;

    int inword = 0;
    for (int i=0; i<size; i++) {
        char curr = *(addr+i);

        if (isalpha(curr) && !inword) {
            word_count++;
            inword = 1;
        }

        inword = isalpha(curr);

        if (curr == '\n')
            line_count++;
    }

    munmap(addr, size);
    close(fd);

    printf("%d\t%d\t%d\n", line_count, word_count, char_count);

    //printf("%d	%d	%d	%s\n", newline_count, space_count, char_count, filename);
}
