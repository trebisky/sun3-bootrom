#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int
main ( int argc, char **argv )
{
  int fd, r;
  unsigned char* adr = NULL;
  struct stat st;
  size_t size, i;
  unsigned short int sum;

  if (argc < 2) {
    fprintf(stderr, "One argument needed: path to file to checksum\n");
    exit(-1);
  }
  
  fd = open(argv[1], O_RDWR );
  if (fd <= 0) {
    fprintf(stderr, "Can't open file\n");
    exit(-2);
  }
  r = fstat(fd, &st);
  if (r < 0) {
    fprintf(stderr, "Can't stat file\n");
    exit(-3);
  }
  size = st.st_size;

  fprintf(stderr, "File is %zd bytes\n", size);
  if (size != 65536) {
    fprintf(stderr, "Are you sure it's the right file? aborting\n");
    exit(-4);
  }

  adr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (adr ==  MAP_FAILED) {
    fprintf(stderr, "Can't mmap file (%d, %s)\n", errno, strerror(errno));
    exit(-5);
  }

  sum = 0;
  for (i = 0 ; i < size-2 ; i++) {
    sum += adr[i];
  }

  printf("Checksum is 0x%04x\n", sum);

  *((unsigned char *)(adr + size - 1)) = (unsigned char)( sum       & 0xFF);
  *((unsigned char *)(adr + size - 2)) = (unsigned char)((sum >> 8) & 0xFF);

  munmap(adr, size);

  close(fd);

  return 0;
}
