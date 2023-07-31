#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10000

int main() {
  FILE *f = fopen("./input7.txt", "r");
  char tempLine[MAX_LEN];
  fgets(tempLine, MAX_LEN, f);

  int numOfElems = 0;
  int sortedArray[MAX_LEN];

  char *positionStr = strtok(tempLine, ",");
  while (positionStr != NULL) {
    int positionInt = atoi(positionStr);

    if (numOfElems == 0) sortedArray[numOfElems] = positionInt;

    /* Go through array from start
     * While checking if the new int is smaller than element at current idx.
     * When we find something larger our new int,
     * Put new int in said idx, then move the rest of the array toward right by one idx.
     * If nothing is larger than our new int, we put it in last index, which would be the current
     * num of elemnts
     */
    for (int i = 0; i <= numOfElems; i++) {
      if (i == numOfElems) {
        // New element is largest.
        sortedArray[i] = positionInt;
        break;
      }
      if (sortedArray[i] < positionInt) continue;

      for (int currIdx = numOfElems - 1; currIdx >= i; currIdx--) {
        sortedArray[currIdx + 1] = sortedArray[currIdx];
      }
      sortedArray[i] = positionInt;
      break;
    }

    numOfElems++;
    positionStr = strtok(NULL, ",");
  }

  int median;
  if (numOfElems % 2 == 0) {
    median = (sortedArray[numOfElems/2 - 1] + sortedArray[numOfElems/2]) / 2;
  } else {
    median = sortedArray[numOfElems/2];
  }

  printf("Median: %i\n", median);

  // calculate fuel consumption
  int fuel_1 = 0;
  for (int i = 0; i < numOfElems; i++) {
    fuel_1 += abs(sortedArray[i] - median);
  }
  printf("Fuel 1: %i\n", fuel_1);

  int sum = 0;
  for (int i = 0; i < numOfElems; i++) {
    sum += sortedArray[i];
  }
  int mean = sum / numOfElems;
  printf("Mean: %i\n", mean);


  fclose(f);
  return 0;
}
