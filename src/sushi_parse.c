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
void free_memory(prog_t *exe) {
  for (int i = 0; i < exe->args.size; i++)
    if (exe->args.args[i]) free(exe->args.args[i]);
  if (exe->redirection.in) free(exe->redirection.in);
  if (exe->redirection.out1) free(exe->redirection.out1);
  if (exe->redirection.out2) free(exe->redirection.out2);
  free(exe);
}

void sushi_assign(char *name, char *value) {
  setenv(name, value, 1);
  free(name);
  free(value);
}

char *sushi_safe_getenv(char *name) {
  char *var = getenv(name);
  return var ? var : "";
}

/*------------------------------------------------------------------
 * You can use these "convenience" functions as building blocks for
 * HW5 instead of your code, if you want. You may change them, too.
 *------------------------------------------------------------------*/

// Find the number of programs on the command line
static size_t cmd_length(prog_t *exe) {
  int count = 0;
  while(exe->prev) {
    exe = exe->prev;
    count++;
  }
  return count;
}

// Wait for the process pid to terminate; once it does, set the
// environmental variable "_" to the exit code of the process.
static int wait_and_setenv(pid_t pid) {
  int status;
  if (-1 == waitpid(pid, &status, 0)) {
    perror("waitpid");
    status = 1; // Something bad happened
  }
  char retval[16]; // Just to be safe
  sprintf(retval, "%d", status);
  if(-1 == setenv("_", retval, 1)) {
    perror("_");
    return 1;
  } else
    return 0;
}

// Execute the program defined in "exe"
static void start(prog_t *exe) {
  arglist_t args = exe->args;
  args.args = super_realloc(args.args, sizeof(char*) * (args.size + 1));
  args.args[args.size] = (char*)NULL;
  execvp(args.args[0], args.args);
  perror(args.args[0]);
}

// "Rename" file descriptor "old" to "new," if necessary. After the
// execution of this function a program that "believes" that it uses
// the "old" descriptor (e.g., stdout #1 for output) will be actually
// using the "new" descriprot (e.g., an outgoinf pipe).  This
// functions terminates the process of error and should not be used in
// the parent, only in a child.
static void dup_me (int new, int old) {
  if (new != old && -1 == dup2(new, old)) {
    perror("dup2");
    exit(1);
  }
}

// Former spawn().
int sushi_spawn(prog_t *exe, int bgmode) {
  int retval = 0;

  int child = fork();
  switch (child) {
  case -1: // We failed
    perror(exe->args.args[0]);
    return 1;
    
  case 0: // We are the child
    start(exe);
    // If we are here, we failed
    exit(EXIT_FAILURE);
    
  default: // We are the parent, do nothing so far
    if (bgmode == 0) {
      if(wait_and_setenv(child))
	retval = 1;
      break;
    }
  }
  
  free_memory(exe);
  return retval;
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

