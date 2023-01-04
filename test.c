#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>


static void sigint_handler(int signum) {
  // Check if the user is trying to write something on the terminal
  int nbytes;
  if (ioctl(0, FIONREAD, &nbytes) == -1) {
    perror("ioctl");
    return;
  }

  if (nbytes > 0) {
    printf("Ignoring SIGINT, %d bytes waiting to be read\n", nbytes);
  } else {
    printf("Exiting on SIGINT\n");
    exit(0);
  }
}

int main(int argc, char* argv[]) {
  // Set up the SIGINT signal handler
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    perror("signal");
    return 1;
  }

  // Loop indefinitely
  while (1) {
    pause();
  }

  return 0;
}
