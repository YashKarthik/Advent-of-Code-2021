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

int main(void) {
  FILE* f = fopen("./input3.txt", "r");
  int numOfLines = 0;
  char diagnosticReport[SIZE][30];

  char tempLine[30];
  while (fgets(tempLine, 30, f) != NULL) {
    strcpy(diagnosticReport[numOfLines], tempLine);
    numOfLines++;
  }

  int rowLength = strlen(diagnosticReport[0]);

  char binGammaRate[rowLength];;
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

  printf("Gamma: %s;\nEpsilon: %s;\n", binGammaRate, binEpsilonRate);
  printf("%i\n", binaryToInt(binGammaRate)*binaryToInt(binEpsilonRate));

  return 0;
}
