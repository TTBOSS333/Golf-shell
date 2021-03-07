#include <string.h>
#include <ctype.h>
#include "sushi.h"

// modified by pw
char *sushi_read_line(FILE *in) {
  char buffer[SUSHI_MAX_INPUT + 1];
  char *result;
  char *tok;

  if (!fgets(buffer, SUSHI_MAX_INPUT + 1, in))
    return NULL;

  strtok(buffer, "\n"); // Remove the newline, if any

  int is_blank = 1;
  for (size_t i = 0; i < strlen(buffer); i++)
    if (!isspace(buffer[i])) {
      is_blank = 0;
      break;
    }

  if (is_blank) // Blank line
    return NULL;

  result = malloc(strlen(buffer) + 1); // Needs a check!
  strcpy(result, buffer);

  // Line too long?
  if (strlen(buffer) == SUSHI_MAX_INPUT) {
    fprintf(stderr, "%s\n", "Line too long, truncated");
    int c;
    do
      c = fgetc(in);
    while (c != '\n' && c != EOF);
  }

  return result;
}

int sushi_read_config(char *fname, int ok_if_missing) {

  FILE *infile;

  if (!(infile = fopen(fname, "r"))) {
    if (!ok_if_missing) {
      perror(fname);
      return 1;		
    }
    return 0;
  }

  char *line;

  while (!feof(infile))
    if((line = sushi_read_line(infile))) 
      sushi_store(line);

  fclose(infile);
  return 0;
}
