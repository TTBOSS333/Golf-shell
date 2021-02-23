#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"

int sushi_exit = 0;

int main() {
  int result;
  if (sushi_read_config("sushi.conf", 1))
    return EXIT_FAILURE;

  char *line;

  printf("%s", SUSHI_DEFAULT_PROMPT);

  if (!(line = sushi_read_line(stdin)))
    return EXIT_FAILURE;

  sushi_store(line);
  sushi_show_history();
  
  return EXIT_SUCCESS;
}
