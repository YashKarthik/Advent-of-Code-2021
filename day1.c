#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX 10

int main() {
  FILE* inputFile = fopen("./input1.txt", "r");

  int inc = 0;
  char line1[MAX];
  char line2[MAX] = "";

  while (
    fgets(line1, MAX, inputFile) != NULL
  ) {

    if (strcmp(line2, "") == 0) {
      strcpy(line2, line1);
      continue;
    };

    int depth1 = atoi(line1);
    int depth2 = atoi(line2);

    if (depth2 < depth1) inc++;
    strcpy(line2, line1);
  }

  printf("%i\n", inc);

  return 0;
}
