#include <stdio.h>
#include "sushi_yyparser.tab.h"

// Modify this function
// modified by Shad
char *sushi_unquote(char *s) {
  int s_len = strlen(s); 
  char *temp = malloc(s_len + 1);
  if (!temp)
    return NULL;

  int j = 0;
  for (int i = 1; i < s_len - 1; i++, j++) { 
    if (s[i] == '\\') { 
      i++;
      switch(s[i]) {
      case '\\': 
	temp[j] = '\\';
	break;
      case 'n':
	temp[j] = '\n';
	break;
      case 't':
	temp[j] = '\t';
	break;
      case 'r':
	temp[j] = '\r';
	break;
      case '"':
	temp[j] = '"';
	break;
      default:
	temp[j] = s[i];
	break;
      }
    } else
      temp[j] = s[i];
  }
  temp[j] = '\0'; 
  temp = realloc(temp, j + 1); 
  return temp;
}

// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}
