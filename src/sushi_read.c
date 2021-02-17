  /*
    pengchao_wang working on it 02/16/2021
   */


#include "sushi.h"

static char *history[SUSHI_HISTORY_LENGTH] = {NULL};

char *sushi_read_line(FILE *in) {
  /*
    You code goes here.
   */
  char * ptr;
  char ch;
  int num;
  int nspace;

  ptr = (char*) malloc(SUSHI_MAX_INPUT+1);
  /*
   * If any I/O or memory operation fails,
   * the function shall print an error message
   * with perror() and return NULL.
   */
  if (in==NULL || ptr==NULL){
      perror("I/O or memory operation fails");
      return NULL;
  }

  /*
   * If the input is longer than SUSHI_MAX_INPUT,
   * the function shall discard the rest of it
   * (to the next newline, including the newline
   * itself) and display the following error message
   * to stderr: Line too long, truncated.
   */
    num=0;
    nspace=0;
    while( (ch=fgetc(in)) != EOF ){
        if(ch==' '){
            nspace++;
        }

        if(num<SUSHI_MAX_INPUT){
            if(ch=='\n'){
                ptr[num]='\0';
                break;
            } else{
                ptr[num]=ch;
            }
        } else {
            ptr[SUSHI_MAX_INPUT]='\0';
            if(ch=='\n'){
                fprintf(stderr, "Line too long, truncated.");
                break;
            }
        }

        num++;
    }

  /*
   * If the line is blank (empty or consists only of
   * white spaces, as defined by isspace()), it shall
   * be discarded and the function shall return NULL.
   */

  if(num==0 || (nspace>0 &&nspace+1==num)){
      return NULL;
  }
  return ptr;
}

int sushi_read_config(char *fname, int ok_if_missing) {
  /*
    You code goes here.
   */
  FILE *in;
  int num;
  in = fopen(fname,"r");

  if (in==NULL){
//      perror("File not exist");
      return EXIT_FAILURE;
  }

  num=0;
  while (!feof(in)){
      char *line = sushi_read_line(in);
      history[num]=line;
      num++;
  }

//  for(int i=0;i<num;i++){
//      printf("%s\n", history[i]);
//  }


  fclose(in);
  return EXIT_SUCCESS;
}