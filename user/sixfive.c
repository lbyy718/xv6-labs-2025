#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

static int
is_separator(char c)
{
  return c != '\0' && strchr(" -\r\t\n./,", c) != 0;
}

static void
print_if_sixfive(int valid, int have_digits, int value)
{
  if(valid && have_digits && (value % 5 == 0 || value % 6 == 0))
    printf("%d\n", value);
}

static int
process_file(char *path)
{
  int fd = open(path, O_RDONLY);
  if(fd < 0){
    fprintf(2, "sixfive: cannot open %s\n", path);
    return -1;
  }

  int valid = 1;
  int have_digits = 0;
  int value = 0;
  char c;

  while(read(fd, &c, 1) == 1){
    if(is_separator(c)){
      print_if_sixfive(valid, have_digits, value);
      valid = 1;
      have_digits = 0;
      value = 0;
    } else if(c >= '0' && c <= '9'){
      if(valid){
        have_digits = 1;
        value = value * 10 + c - '0';
      }
    } else {
      // A token such as "xv6" is not a number. Ignore the whole
      // token until one of the specified separators is encountered.
      valid = 0;
    }
  }

  // End-of-file acts as an implicit separator.
  print_if_sixfive(valid, have_digits, value);
  close(fd);
  return 0;
}

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "usage: sixfive file ...\n");
    exit(1);
  }

  int failed = 0;
  for(int i = 1; i < argc; i++){
    if(process_file(argv[i]) < 0)
      failed = 1;
  }

  exit(failed);
}
