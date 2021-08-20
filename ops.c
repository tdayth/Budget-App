#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ops.h"

#define MAXLINE 32
#define MAX_PLACES 10

void split(char **final, char *line, char *with) {
    char *token = NULL;
    token = strtok(line, with);
    if (strcmp(with, " ") == 0) {
        for (int j = 0; j < 4; j++) {
            token = strtok(NULL, with);
        }
    }

    int i = 0;
    while (token != NULL) {
      final[i] = malloc(sizeof(char) * MAXLINE);
      strcpy(final[i], token);
      i++;
      token = strtok(NULL, with);
    }
}


void add_expense(char *fileName, char *place, char *cost) {
  FILE *f = fopen(fileName, "r");
  if (f < 0) {
    printf("failed");
  }

  char line[1024] = "";
  char c;

  fseek(f, -1, SEEK_END);
  c = fgetc(f);
  while(c != '\n')
{
    fseek(f, -2, SEEK_CUR);
    c = fgetc(f);
}

//split line by spaces, then split each new element by = except the first element

  //fseek(f, 1, SEEK_CUR);
  fread(line, 1, 1024, f);
  printf("%s\n", line);

  char **final = malloc(sizeof(char*) * MAX_PLACES);
  split(final, line, " ");

  // If place does not already exist in the file
  // fwrite(" ", 1, 1, f);
  // fwrite(place, 1, strlen(place), f);
  // fwrite("=$", 1, 2, f);
  // fwrite(cost, 1, strlen(cost), f);

  for (int j = 0; j < MAX_PLACES; j++) {
      free(final[j]);
  }
  free(final);

  fclose(f);
}
