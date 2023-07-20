#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main() {
  FILE* inputFile = fopen("./input1.txt", "r");

  int depths[2048]; // each elem is a number from the file
  int lines = 0;    // will contain number of elems in depths

  char tempLine[15];
  while (fgets(tempLine, 15, inputFile) != NULL) {
    depths[lines] = atoi(tempLine);
    lines++;
  }

  // Part one
  int inc = 0;
  for (int i = 1; i < lines; i++) {
    if (depths[i] > depths[i - 1]) { inc++; }
  }

  printf("%i\n", inc);

  // Part two
  int windowInc = 0;
  for (int i = 1; i < lines - 2; i++) {
    int window_1 = depths[i - 1] + depths[i] + depths[i + 1];
    int window_2 = depths[i] + depths[i + 1] + depths[i + 2];

    if (window_2 > window_1) { windowInc++; }
  }
  printf("%i\n", windowInc);

  fclose(inputFile);
  return 0;
}
