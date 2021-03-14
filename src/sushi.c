#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"

int sushi_exit = 0;

static void refuse_to_die(int sig)
{
  // TODO
}

static void prevent_interruption() {
  // TODO
}

int main() {
  prevent_interruption();
  lookup_table_setup();
  if (sushi_read_config("sushi.conf", 1))
    return EXIT_FAILURE;

  char *line;

  while (!sushi_exit) {
    printf("%s", SUSHI_DEFAULT_PROMPT);

    if (!(line = sushi_read_line(stdin)))
      return EXIT_FAILURE;
    
    if (!sushi_parse_command(line))
      sushi_store(line);
  }
  
  return EXIT_SUCCESS;
}
