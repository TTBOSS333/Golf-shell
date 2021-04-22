#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "sushi.h"

int sushi_exit = 0;

static void refuse_to_die(int sig)
{
  fputs("Type exit to exit the shell\n", stderr);
}

static void prevent_interruption() {
  struct sigaction sa = {.sa_handler = refuse_to_die, .sa_flags = 0};
  if (sigaction(SIGINT, &sa, NULL)) {
    // Cannot be fixed, anyway.
    perror("sigaction");
  }
}

int main(int argc, char * argv[0]) {
  prevent_interruption();
  lookup_table_setup();
  if (sushi_read_config("sushi.conf", 1))
    return EXIT_FAILURE;

  char *line;

  while (!sushi_exit) {
    printf("%s", SUSHI_DEFAULT_PROMPT);

    if ((line = sushi_read_line(stdin)) && !sushi_parse_command(line))
      sushi_store(line);
  }
  
  return EXIT_SUCCESS;
}