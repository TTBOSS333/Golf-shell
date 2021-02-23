#include <stdio.h>
#include "sushi_yyparser.tab.h"

// Modify this function
char *sushi_unquote(char *s) {
  return s;
}

// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}
