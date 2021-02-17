
#include "sushi.h"

int main(/*int argc, char *argv[]*/)
{
  /*
   */
  char *fname = "sushi.conf";
  int ok_if_missing = 0;
  sushi_read_config(fname, ok_if_missing);
  /*
    pengchao_wang working on it 02/16/2021
   */


  return EXIT_SUCCESS;
}
