#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  DIR *dir;
  struct dirent *entry;

  // Open the directory specified by argv[1]
  dir = opendir(argv[1]);
  if (dir == NULL) {
    perror(argv[1]);
    return 1;
  }

  // Read each entry in the directory
  while ((entry = readdir(dir)) != NULL) {
    printf("%s\n", entry->d_name);
  }

  // Close the directory stream
  closedir(dir);

  return 0;
}
