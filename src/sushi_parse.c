#include <stdio.h>
#include <string.h> //DZ: Missing prototype for strlen
#include <stdlib.h> //DZ: Missing prototype for malloc
#include "sushi_yyparser.tab.h"

// Modify this function
// modified by Shad
char *sushi_unquote(char *s) {
  //DZ: Missing prototype for strlen
  int s_len = strlen(s);
  //DZ: Should have modified in place, not make a copy
  //DZ: Missing prototype for malloc
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
	//DZ: What about \' ?
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
