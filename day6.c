#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000
#define SIMULATION_DURATION_IN_DAYS 80

int main() {
  FILE *f = fopen("./input6.txt", "r");
  char tempLine[MAX_LEN];
  fgets(tempLine, MAX_LEN, f);

  int numOfFish = 0;
  int arrayCapacity = 10;

  int *fishesWithCounter = calloc(arrayCapacity, sizeof(int));

  char *fishInitialCounter = strtok(tempLine, ",");
  while (fishInitialCounter != NULL) {

    if (numOfFish >= arrayCapacity) {
      arrayCapacity *= 2;
      fishesWithCounter = realloc(fishesWithCounter, arrayCapacity*sizeof(int));
    }

    fishesWithCounter[numOfFish] = atoi(fishInitialCounter);

    numOfFish++;
    fishInitialCounter = strtok(NULL, ",");
  }

  for (int day = 0; day < SIMULATION_DURATION_IN_DAYS; day++) {

    printf("After %i days: ", day);
    for (int i = 0; i < numOfFish; i++) {
      printf("%i, ", fishesWithCounter[i]);
    }
    printf("\n");

    int fishesToday = numOfFish;
    for (int fishNum = 0; fishNum < fishesToday; fishNum++) {

      if (fishesWithCounter[fishNum] != 0) {
        fishesWithCounter[fishNum]--;
        continue;
      }

      fishesWithCounter[fishNum] = 6;

      if (numOfFish >= arrayCapacity) {
        arrayCapacity *= 2;
        fishesWithCounter = realloc(fishesWithCounter, arrayCapacity*sizeof(int));
      }
      numOfFish++;
      fishesWithCounter[numOfFish-1] = 8;
    }
  }

  printf("%i \n", numOfFish);

  free(fishesWithCounter);
  fclose(f);
  return 0;
}
