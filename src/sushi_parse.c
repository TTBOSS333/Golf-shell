#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "sushi.h"
#include "sushi_yyparser.tab.h"

static char lookup_table[128] = {'\0'};

// The function storesd the special characters in the lookup table
void lookup_table_setup() {
  static const char special[][2] = {
    {'a', '\a'}, {'b', '\b'}, {'f', '\f'}, {'n', '\n'}, {'r', '\r'},
    {'t', '\t'}, {'v', '\v'}, {'\\', '\\'}, {'\'', '\''}, {'\"', '\"'},
    {'?', '\?'}, {'0', '\0'},
  };
  for (int i = 0; special[i][0]; i++)
    lookup_table[(size_t)special[i][0]] = special[i][1];
}

// Decode special characters
char *sushi_unquote(char *s) {
  size_t j = 0;
  for (size_t i = 0; i < strlen(s); i++, j++) {
    // Checks for escape sequences
    char next = lookup_table[(size_t)s[i + 1]];
    s[j] = (s[i] == '\\' && next) ? (i++, next) : s[i];
  }
  s[j] = '\0'; // Null-terminate the string

  return s;
}

// Function skeletons for HW3
void free_memory(prog_t *exe, prog_t *pipe) {
  // TODO - but not this time
  fputs("Temp message: freeing memory\n", stderr);
}

int spawn(prog_t *exe, prog_t *pipe, int bgmode) {
  int retval = 0;
  int child = fork();
  switch (child) {
  case -1: // We failed
    perror("fork");
    free_memory(exe, pipe);
    retval = 1;
    break;
    
  case 0: // We are the child
    exe->args.args = super_realloc(exe->args.args, exe->args.size + 1);
    exe->args.args[exe->args.size] = NULL;
    execvp(exe->args.args[0], exe->args.args);

    // If we are here, we failed
    perror(exe->args.args[0]);
    exit(EXIT_FAILURE);
    
  default: // We are the parent, do nothing so far
    break;
  }
  
  return retval;
}

void sushi_assign(char *name, char *value) {
  // TODO
}

char *sushi_safe_getenv(char *name) {
  // TODO
  return "";
}

char *super_strdup(const char *s) {
  char *result = strdup(s);
  if (!result) abort();
  return result;
}

void *super_malloc(size_t size) {
  void *result = malloc(size);  
  if (!result) abort();
  return result;
}

void *super_realloc(void *ptr, size_t size) {
  void *result = realloc(ptr, size);  
  if (!result) abort();
  return result;
}

// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}

void __not_implemented__() {  
  fputs("This operation is not implemented yet\n", stderr);
}

