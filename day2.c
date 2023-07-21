#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdlib.h"
#define SIZE  2048

void slice_string(char *to, char *from, int start, int end) {
  if (end >= strlen(from)) { end = strlen(from); }

  int i = 0;
  for (int offset = start; offset < end; offset++) {
    to[i] = from[offset];
    i++;
  }

  to[i] = '\0';
}

char** split_string(char *to_split, char delimiter) {
  char **result = (char**)malloc(sizeof(char *) * 2);

  for (int i = 0; i < strlen(to_split); i++) {
    if (to_split[i] != delimiter) { continue; }

    result[0] = (char*)malloc((i+1) * sizeof(char));
    result[1] = (char*)malloc((strlen(to_split) - i) * sizeof(char));
    strcpy(result[0], "");
    strcpy(result[1], "");

    slice_string(result[0], to_split, 0, i);
    slice_string(result[1], to_split, i+1, strlen(to_split));
    break;
  }

  return result;
}

int main() {
  FILE* f = fopen("./input2.txt", "r");

  int numOfLines = 0;
  char commandStrings[SIZE][10];

  char tempLine[15];
  while (fgets(tempLine, 15, f) != NULL) {
    strcpy(commandStrings[numOfLines], tempLine);
    numOfLines++;
  }

  //char commandStrings[SIZE][10] = {
  //  "forward 5",
  //  "down 5",
  //  "forward 8",
  //  "up 3",
  //  "down 8",
  //  "forward 2",
  //};

  //numOfLines = 6;

  int hori = 0;
  int vert = 0;

  for (int i = 0; i < numOfLines; i++) {
    char **split_strs = split_string(commandStrings[i], ' ');

    if (strcmp(split_strs[0], "forward") == 0) {
      hori += atoi(split_strs[1]);
    } else if (strcmp(split_strs[0], "down") == 0) {
      vert += atoi(split_strs[1]);
    } else if (strcmp(split_strs[0], "up") == 0) {
      vert -= atoi(split_strs[1]);
    }
    free(split_strs);
  }

  printf("hori(%i) * vert(%i) = %i\n", hori, vert, hori*vert);
  return 0;
}
