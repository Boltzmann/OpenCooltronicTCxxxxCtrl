#include"tc3215rs232.h"

// This file is basically for printing some kind of
// menu help. 
// It reads a file and prints every line of it
// to standard output.

void printFile(char filename[30]){
  FILE *file;
  file=fopen(filename,"r");
  if(file!=NULL){
    // if a readable file 'filename' exists ...
    char line[128];
    // ... file is read and written line by line.
    while(fgets(line, sizeof line, file)!=NULL)
      fputs(line,stdout);
    printf("\n");
    fclose(file);
  }
  else{
    perror(filename);
    // Standard C provides this function for 
    // understandable error messages with filename
    // at the end of the message.
  }
  return;
}
