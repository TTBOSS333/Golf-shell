#include <stdlib.h>
#include <stdio.h>
#include "sushi.h"

//DZ: I assume that this is most recent valid revision:
// https://github.com/ttboss777/Golf-shell/blob/115f97e17879f3d36bc1092291190a215e8c3c89/src/sushi.c

int sushi_exit = 0;

int main() {
  int result;
  if (sushi_read_config("sushi.conf", 1))
    return EXIT_FAILURE;


  while (sushi_exit == 0)
    {
      char *line;

      printf("%s", SUSHI_DEFAULT_PROMPT);

      if (!(line = sushi_read_line(stdin)))
	sushi_parse_command(line);

      // DZ: Why break the llop after the first command?
      return EXIT_FAILURE;

      //DZ : Must store consitionally
      sushi_store(line);
    }

  // DZ: No need
  sushi_show_history();
  
  return EXIT_SUCCESS;

}
