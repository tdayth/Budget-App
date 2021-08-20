#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ops.h"

#define MAXLINE 32
#define MAX_CMD 10
#define MAX_NUM_ARGS 3


int tokenize(char **args, char *command) {
  int argc = 0;
  char *token = strtok(command, " ");
  while (token != NULL) {
    if (argc >= MAX_NUM_ARGS) {
        printf("Too many arguments\n");
        argc = 0;
        break;
    }
    args[argc] = malloc(sizeof(char) * MAX_CMD);
    strcpy(args[argc], token);
    argc++;
    token = strtok(NULL, " ");
  }

  return argc;
}

void display_help_message() {
    printf("\nList of commands:\n");
    printf("add [place] [amount]\n");
    printf("remove [place] [amount]\n");
    printf("total [time]\n");
    printf("budget [time] [amount]\n");
    printf("find [store] [time]\n");
    printf("overview [time]\n");
    printf("quit\n\n");
    fflush(stdout);
}

int isString(char *string) {
    for (int i = 0; i < strlen(string); i++) {
       if (!isalpha(string[i])) {
         return 1;
       }
    }
    return 0;
}

int isDigits(char *string) {
    for (int i = 0; i < strlen(string); i++) {
       if (!isdigit(string[i])) {
         return 1;
       }
    }
    return 0;
}


void process_args(char *fileName, char *command) {
    //command can have multiple args. Need function to extract all cargs
    char **args = malloc(sizeof(char*) * MAX_NUM_ARGS);
    int argc = tokenize(args, command);


    if ((strcmp(command, "help") == 0) && argc == 1) {
      display_help_message();
      return;


    } else if ((strcmp(args[0], "add") == 0) && isString(args[1]) == 0
                                             && isDigits(args[2]) == 0
                                             && argc == 3) {
        add_expense(fileName, args[1], args[2]);
        printf("Expense added.\n");

    } else if ((strcmp(args[0], "remove") == 0) && isString(args[1]) == 0
                                                && isDigits(args[2]) == 0
                                                && argc == 3) {
        printf("Expense removed.\n");

    } else if ((strcmp(args[0], "total") == 0) && isString(args[1]) == 0
                                               && argc == 2) {
        printf("Your total is:\n");

    } else if ((strcmp(args[0], "budget") == 0) && isString(args[1]) == 0
                                                && isDigits(args[2]) == 0
                                                && argc == 3) {
        printf("Your budget for the [time]:\n");

    } else if ((strcmp(args[0], "find") == 0) && isString(args[1]) == 0
                                              && isString(args[2]) == 0
                                              && argc == 3) {
        printf("Finding...\n");

    } else if ((strcmp(args[0], "overview") == 0) && isString(args[1]) == 0
                                                  && argc == 2) {
        printf("Overview:\n");

    } else if (strcmp(command, "quit") == 0) {
        printf("Closing program...\n");
        exit(0);

    } else {
      printf("Invalid command. Try again.\n");
    }

    for (int j = 0; j < MAX_NUM_ARGS; j++) {
        free(args[j]);
    }
    free(args);
}

int main(int argc, char **argv) {
  char command[MAXLINE] = "";

  //printf("%s %s\n", argv[0], argv[1]); //argv 1 is fileName
  printf("Enter command (\"help\" to list commands): ");
  fflush(stdout);

while (fgets(command, MAXLINE, stdin) != NULL) {
  if ((command[strlen(command) - 1]) == '\n') {
      command[strlen(command) - 1] = '\0';
  }
  process_args(argv[1], command);
  printf("Enter command: ");
}


}
