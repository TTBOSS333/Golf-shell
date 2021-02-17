#include "sushi.h"
static char *history[SUSHI_HISTORY_LENGTH] = {NULL};
void sushi_store(char *line) {
  int arr_size = (sizeof(history) / sizeof(history[0]));
  int rear = 0;
  int front = 0;
  
 /* verify is the array is full.
    if full all elements will be shifted to the right,
    with the last one being discarded. the new line will 
    also be place in the front */

  if(rear == ( arr_size - 1)){
    for(int i = arr_size -1; i > 0; i--){
      history[i] = history[i-1];
    }
    history[front] = *line;
  }

  /* verify if the line is not null, in
    which case it will be added to the array.*/
    
  if(*line != NULL){
    for(int i = rear; i < rear; i++){
      history[rear] = history[rear-1];
    }
  }
  
  history[front] = *line;
  rear++;
}

void sushi_show_history(FILE *out) {
  char mouse;
  // open the file
  out = fopen("history", "r");
  if (out == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    }

  // read the content of the file
 
    mouse = fgetc(out); 
    int position = 0;
    while (mouse != EOF) 
    { 
        printf("%d", position);
        fflush(stdout);
        printf ("%c", mouse); 
        mouse = fgetc(out);
        position++; 
    } 
  
    fclose(out); 
    return 0;
}
