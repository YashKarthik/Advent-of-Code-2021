#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000
#define SIMULATION_DURATION_IN_DAYS 256
#define NUM_FISH_BUCKETS 9

void ineffecientMethod(char *tempLine) {
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

    //printf("After %i days: ", day);
    //for (int i = 0; i < numOfFish; i++) {
    //  printf("%i, ", fishesWithCounter[i]);
    //}
    //printf("\n");

    int fishesToday = numOfFish;
    printf("Today fish: %i \n", fishesToday);
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

}

void betterMethod(char *tempLine) {
  long numOfFish = 0;
  long fishInEachBucket[NUM_FISH_BUCKETS] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  char *counterOfFish = strtok(tempLine, ",");
  while (counterOfFish != NULL) {
    fishInEachBucket[atoi(counterOfFish)]++;
    numOfFish++;

    counterOfFish = strtok(NULL, ",");
  }

  for (int day = 0; day < SIMULATION_DURATION_IN_DAYS; day++) {

    long tempZeroes = fishInEachBucket[0];
    for (int idx = 1; idx < NUM_FISH_BUCKETS; idx++) {
      fishInEachBucket[idx - 1] = fishInEachBucket[idx];
    }

    numOfFish += tempZeroes;
    fishInEachBucket[NUM_FISH_BUCKETS - 1] = tempZeroes; // all the zeroes give birth to younglings
    fishInEachBucket[6] += tempZeroes; // all the moms become 6;
  }

  printf("%lul\n", numOfFish);

}

int main() {
  FILE *f = fopen("./input6.txt", "r");
  char tempLine[MAX_LEN];
  fgets(tempLine, MAX_LEN, f);

  //ineffecientMethod(tempLine);
  betterMethod(tempLine);

  fclose(f);
  return 0;
}
