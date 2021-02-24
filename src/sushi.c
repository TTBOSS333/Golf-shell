
#include "sushi.h"

int main(/*int argc, char *argv[]*/)
{
  /*
    pengchao_wang working on it 02/16/2021
   */
  char *fname = "sushi.conf";
  int ok_if_missing = 0;

  //DZ Must check the return value
  sushi_read_config(fname, ok_if_missing);
  /*
    pengchao_wang working on it 02/16/2021
   */
  
  /*
    Shad working on it 02/17/2021
   */
  //DZ Uninitialized! 
  FILE *output=stdout;
  sushi_show_history(output);
  /*
    shad working on it 02/17/2021
   */

  //DZ Ontrehr things missing.
  return EXIT_SUCCESS;
}
