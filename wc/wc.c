#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <unistd.h>

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

int main(int argc, char **argv)
{
    int fd;
    size_t size;
    char* addr = mapfile("test-data/moby-dick.txt", &fd, &size);

    for (int i=0; i<size; i++) {
        char c = *(addr+i);
        printf("%c", c);
    }

    //munmap(addr, size);
    //close(fd);

    //for (int i = 1; // argv[0] == name of this file
    //        i < argc; i++) {
    //    char* filename = argv[i];
    //    count_words(filename);
    //    printf("%d	%d	%d	%s\n", newline_count, space_count, char_count, filename);
    //}
}
