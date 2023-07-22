#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#define SIZE 2048

int binaryToInt(char *binNum) {
  int result = 0;
  for (int i = strlen(binNum) - 2; i >= 0; i--) {
    result += (binNum[i] - '0')*(pow(2.0, strlen(binNum) - 2 - i));
  }
  return result;
}

int part1(char diagnosticReport[SIZE][30], int numOfLines) {

  int rowLength = strlen(diagnosticReport[0]);
  char binGammaRate[rowLength];
  char binEpsilonRate[rowLength];

  for (int position = 0; position < rowLength; position++) {
    int zeroes = 0;
    int ones = 0;

    for (int row = 0; row < numOfLines; row++) {
      if (diagnosticReport[row][position] == '0') { zeroes++; }
      else { ones++; }
    }

    if (zeroes > ones) {
      binGammaRate[position] = '0';
      binEpsilonRate[position] = '1';
    } else {
      binGammaRate[position] = '1';
      binEpsilonRate[position] = '0';
    }
  }

  return binaryToInt(binGammaRate)*binaryToInt(binEpsilonRate);
}

char* filterRows(char filterInput[][30], int numOfRows, char which) {
  char* result = malloc(numOfRows*sizeof(char[30]));

  while (numOfRows != 1) {
    for (int position = 0; position < strlen(filterInput[0]); position++) {
      for (int row = 0; row < numOfRows; row++) {

        if (filterInput[row][position] == which) {}

      }
    }
  }

  return result;
}

int part2(char diagnosticReport[SIZE][30], int numOfLines) {
  int rowLength = strlen(diagnosticReport[0]);
  char oxygenRatingOptions[SIZE][30];

  char* filteredRow = filterRows(diagnosticReport, numOfLines, 0);
  printf("%s", filteredRow);

  free(filteredRow);
  return 0;
}

int main(void) {
  FILE* f = fopen("./input3.txt", "r");
  int numOfLines = 0;
  char diagnosticReport[SIZE][30];

  char tempLine[30];
  while (fgets(tempLine, 30, f) != NULL) {
    strcpy(diagnosticReport[numOfLines], tempLine);
    numOfLines++;
  }
  fclose(f);

  // Part 1
  //printf("Power consumption: %i\n",part1(diagnosticReport, numOfLines));
  part2(diagnosticReport, numOfLines);
  return 0;
}
