#include "sushi.h"
static char *history[SUSHI_HISTORY_LENGTH] = {NULL};
void sushi_store(char *line) {

  //DZ Array size is SUSHI_HISTORY_LENGTH, no need to calculate it
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
    //DZ Must free the discarded line
    //DZ Wrong. history[front] = line;
    history[front] = *line;
  }

  /* verify if the line is not null, in
    which case it will be added to the array.*/
  //DZ Wrong. line != NULL;
  if(*line != NULL){
    for(int i = rear; i < rear; i++){
      history[rear] = history[rear-1];
    }
  }
  //DZ Wrong. history[front] = line;
  //DZ: Also, you already did this above^
  history[front] = *line;

  //DZ does rear grow infinitely?
  rear++;
}

void sushi_show_history(FILE *out) {
  char mouse;
  //DZ: The history is not in the file but in the buffer
  // open the file
  out = fopen("history", "r");
  if (out == NULL) 
    {
      //DZ perror()
        printf("Cannot open file \n");
	//DZ Only main() may exit()
        exit(0); 
    }

  // read the content of the file

  //DZ Wrong, see above^
    mouse = fgetc(out); 
    int position = 0;
    while (mouse != EOF) 
    { 
        printf("%d", position);
        printf("  ");
        
        printf ("%c", mouse); 
        printf("\n");
        mouse = fgetc(out);
        position++; 
    } 
  
    fclose(out);

    //DZ: Cannot return 0 in a void function
    return 0;
}
