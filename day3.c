#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#define SIZE 1000

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

char* filterRows(char** filterInput, int numOfRows, int position, int greater) {
  if (numOfRows == 1) {
    char* rating = (char*)malloc(12 * sizeof(char));
    strcpy(rating, filterInput[0]);
    return rating;

  }
  char** ones_future_list = (char**)malloc(numOfRows * sizeof(char*));
  char** zeroes_future_list = (char**)malloc(numOfRows * sizeof(char*));
  int ones = 0;
  int zeroes = 0;

  for (int row = 0; row < numOfRows; row++) {
    if (filterInput[row][position] == '0') {
      zeroes_future_list[zeroes] = (char*)malloc(12 * sizeof(char));
      strcpy(zeroes_future_list[zeroes], filterInput[row]);
      zeroes++;
    } else {
      ones_future_list[ones] = (char*)malloc(12 * sizeof(char));
      strcpy(ones_future_list[ones], filterInput[row]);
      ones++;
    }
  }

  char* result;
  if (greater == 1) {
    if (zeroes > ones) result = filterRows(zeroes_future_list, zeroes, position+1, greater);
    else  result = filterRows(ones_future_list, ones, position+1, greater);
  } else {
    if (zeroes > ones) result = filterRows(ones_future_list, ones, position+1, greater);
    else result = filterRows(zeroes_future_list, zeroes, position+1, greater);
  }

  // Free allocated memory for future lists
  for (int i = 0; i < zeroes; i++) {
    free(zeroes_future_list[i]);
  }
  for (int i = 0; i < ones; i++) {
    free(ones_future_list[i]);
  }
  free(zeroes_future_list);
  free(ones_future_list);

  return result;
}

int part2(char** diagnosticReport, int numOfLines) {
  int rowLength = strlen(diagnosticReport[0]);
  char oxygenRatingOptions[SIZE][30];

  char* oxy = filterRows(diagnosticReport, numOfLines, 0, 0);
  char* scrubber = filterRows(diagnosticReport, numOfLines, 0, 1);
  int result = binaryToInt(oxy)*binaryToInt(scrubber);

  free(oxy);
  free(scrubber);
  return result;
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

  char **diagRepPtrs = (char **)malloc(SIZE * sizeof(char *));
  for (int i = 0; i < SIZE; i++) {
    diagRepPtrs[i] = (char *)malloc(30 * sizeof(char));
    strcpy(diagRepPtrs[i], diagnosticReport[i]);
  }

  printf("Power consumption: %i\n",part1(diagnosticReport, numOfLines));
  printf("Life support rating: %i\n", part2(diagRepPtrs, numOfLines));;
  return 0;
}
