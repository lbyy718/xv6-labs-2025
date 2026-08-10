#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

#define PGSIZE 4096
#define NPAGES 32

static char marker[] = "This may help.";

static int
isalnumchar(char c)
{
  return ('0' <= c && c <= '9') ||
         ('a' <= c && c <= 'z') ||
         ('A' <= c && c <= 'Z');
}

int
main(int argc, char *argv[])
{
  char *base;
  uint size;

  base = sbrk(NPAGES * PGSIZE);
  if(base == SBRK_ERROR)
    exit(1);

  size = NPAGES * PGSIZE;
  for(uint i = 0; i + 16 < size; i++){
    if(memcmp(base + i, marker, sizeof(marker) - 1) != 0)
      continue;

    char *secret = base + i + 16;
    uint n = 0;
    while(i + 16 + n < size && isalnumchar(secret[n]))
      n++;

    if(n > 0){
      write(1, secret, n);
      write(1, "\n", 1);
      exit(0);
    }
  }

  exit(1);
}
