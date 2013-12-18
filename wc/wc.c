#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <unistd.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0);

int fd, close_success;
char *addr;
off_t offset, pa_offset;
size_t length;
struct stat sb;

int main(int argc, char **argv)
{
    char *filename = "e.txt";

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

    int char_count = 0;
    int space_count = 0;
    int newline_count = 0;
    int i;
    char curr;
    for (i=0; i < length; i++) {

        curr = *(addr+i);

        if ( (' ' == curr) || ('\t' == curr) || ('\n' == curr) )
            space_count++;

        if ('\n' == curr)
            newline_count++;

        char_count++;
    }

    printf("%d\t%d\t%d\t%s\n", newline_count, space_count, char_count, filename);

    /* Close the input file. */
    close_success = close(fd);

    return close_success;
}
