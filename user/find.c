#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"
#include "user/user.h"

struct action {
  char **argv;
  int argc;
};

static char*
base_name(char *path)
{
  char *p = path + strlen(path);

  while(p > path && p[-1] != '/')
    p--;
  return p;
}

static void
handle_match(char *path, struct action *action)
{
  if(action == 0){
    printf("%s\n", path);
    return;
  }

  char *argv[MAXARG];
  for(int i = 0; i < action->argc; i++)
    argv[i] = action->argv[i];
  argv[action->argc] = path;
  argv[action->argc + 1] = 0;

  int pid = fork();
  if(pid < 0){
    fprintf(2, "find: fork failed\n");
    return;
  }

  if(pid == 0){
    exec(argv[0], argv);
    fprintf(2, "find: exec %s failed\n", argv[0]);
    exit(1);
  }

  wait(0);
}

static void
find(char *path, char *name, struct action *action)
{
  char buf[512];
  char *p;
  int fd;
  struct dirent de;
  struct stat st;

  fd = open(path, O_RDONLY);
  if(fd < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if(st.type == T_FILE){
    if(strcmp(base_name(path), name) == 0)
      handle_match(path, action);
    close(fd);
    return;
  }

  if(st.type != T_DIR){
    close(fd);
    return;
  }

  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
    fprintf(2, "find: path too long %s\n", path);
    close(fd);
    return;
  }

  strcpy(buf, path);
  p = buf + strlen(buf);
  if(p == buf || p[-1] != '/')
    *p++ = '/';

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;

    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = '\0';
    if(strcmp(p, ".") == 0 || strcmp(p, "..") == 0)
      continue;

    find(buf, name, action);
  }

  close(fd);
}

int
main(int argc, char *argv[])
{
  struct action action;
  struct action *actionp = 0;

  if(argc == 3){
    // With no -exec clause, matching paths are printed.
  } else if(argc >= 5 && strcmp(argv[3], "-exec") == 0){
    action.argc = argc - 4;
    action.argv = &argv[4];
    if(action.argc + 1 >= MAXARG){
      fprintf(2, "find: too many arguments for -exec\n");
      exit(1);
    }
    actionp = &action;
  } else {
    fprintf(2, "usage: find path name [-exec command [args ...]]\n");
    exit(1);
  }

  find(argv[1], argv[2], actionp);
  exit(0);
}
