#include <stdio.h>
#include <string.h>
#define MAX_LEN 2048

int main() {
  FILE *f = fopen("./input8.txt", "r");

  char numToPtrnMap[10][8];
  char tempLine[MAX_LEN];
  int count = 0;
  while (fgets(tempLine, sizeof(tempLine), f) != NULL) {
    //strlcpy(lines[numOfLines], tempLine, sizeof(lines[0]));
    size_t lineLength = strlen(tempLine);
    if (lineLength > 0 && tempLine[lineLength - 1] == '\n') {
      tempLine[lineLength - 1] = '\0';
    }

    // While loop reads the signal patterns
    char *signalPtrn = strtok(tempLine, " ");
    while (signalPtrn != NULL) {
      if (strcmp(signalPtrn, "|") == 0) break;

      if (strlen(signalPtrn) == 2) {
        // 2 segments activated => pattern represents 1
        strlcpy(numToPtrnMap[0], signalPtrn, 3);
      } else if (strlen(signalPtrn) == 4) {
        // 4 segments activated => pattern represents 4
        strlcpy(numToPtrnMap[3], signalPtrn, 5);
      } else if (strlen(signalPtrn) == 3) {
        // 3 segments activated => pattern represents 7
        strlcpy(numToPtrnMap[6], signalPtrn, 4);
      } else if (strlen(signalPtrn) == 7) {
        // 7 segments activated => pattern represents 8
        strlcpy(numToPtrnMap[7], signalPtrn, 8);
      }

      signalPtrn = strtok(NULL, " ");
    }

    // This loop reads output values
    signalPtrn = strtok(NULL, " ");
    while (signalPtrn != NULL) {
      //for (int i = 0; i < 10; i++) {
        //if (strcmp(numToPtrnMap[i], signalPtrn) != 0) continue;
        if (
            strlen(signalPtrn) == 2 ||
            strlen(signalPtrn) == 4 ||
            strlen(signalPtrn) == 3 ||
            strlen(signalPtrn) == 7
           ) {
          printf("YES %s \n", signalPtrn);
          count++;
        } else printf("NO  %s \n", signalPtrn);

      //}

      signalPtrn = strtok(NULL, " ");
    }
  }
  printf("Counter: %i\n", count);

  fclose(f);
  return 0;
}
