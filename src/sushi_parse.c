#include <stdio.h>
#include <string.h>
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
  printf("this function was called");
}

int spawn(prog_t *exe, prog_t *pipe, int bgmode) {
  // DZ: Undeclared variable
       pid_t newProcess = fork();

       if (newProcess == 0)
       {
	 // DZ: Undeclared AND uninitalized variable! Cannot fix this for you
            temp = super_realloc(temp, (args + 1) * sizeof(int));

             if(execvp(exe->args.args[0], args) == -1)
             {
                   exit(0);
             }
       }

       if (newProcess != 0)
       {
	 //DZ: This function is void but takes two parameters.
             if(free_memory() == NULL)
             {
                  return 0; 
             }
             else
                  perror("Error in function free_memory()");

       }
       
       // DZ: What if fork() failed?
      
  return 1;
}

char *super_strdup(const char *s) {
  // DZ: strdup called twice.
  if(!(strdup(s))){
        abort();
  }
  // DZ: How do you know this call did not fail?
  return strdup(s);
}

void *super_malloc(size_t size) {  
  // DZ: malloc called twice.
  if(!(malloc(size))){
        abort();
    }
  // DZ: How do you know this call did not fail?
  return malloc(size);
}

void *super_realloc(void *ptr, size_t size) {
  // DZ: realloc called twice.
  if(!(realloc(ptr,size))){
        abort();
    }
  // DZ: How do you know this call did not fail?
  return realloc(ptr, size);
}

// Do not modify this function
void yyerror(const char* s) {
  fprintf(stderr, "Parse error: %s\n", s);
}

void __not_implemented__() {  
  fputs("This operation is not implemented yet\n", stderr);
}

