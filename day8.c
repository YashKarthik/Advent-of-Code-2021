#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LEN 2048

bool unorderedCompare(char *str1, char *str2);
int sumChars(char *str);

typedef struct Line {
  char signalIn[10][8];
  char outputVal[4][8];
} Line;

int main() {
  FILE *f = fopen("./input8.txt", "r");

  Line lines[MAX_LEN];
  int numOfLines = 0;

  char tempLine[MAX_LEN];
  while (fgets(tempLine, sizeof(tempLine), f) != NULL) {
    size_t lineLength = strlen(tempLine);
    if (lineLength > 0 && tempLine[lineLength - 1] == '\n') {
      tempLine[lineLength - 1] = '\0';
    }

    int numOfSegment = 0;
    char *segment = strtok(tempLine, " ");
    while (segment != NULL) {
      if (strcmp(segment, "|") == 0) {
        segment = strtok(NULL, " ");
        numOfSegment++;
        continue; 
      }

      if (numOfSegment < 10) {
        strcpy(lines[numOfLines].signalIn[numOfSegment], segment);
      } else if (numOfSegment > 10) {
        strcpy(lines[numOfLines].outputVal[numOfSegment - 11], segment);
      }

      segment = strtok(NULL, " ");
      numOfSegment++;
    }

    numOfLines++;
  }

  for (int i = 0; i < numOfLines; i++) {
    char *one, *four, *seven, *eight;

    for (int j = 0; j < 10; j++) {
      char *currStr = lines[i].signalIn[j];
      int len = strlen(currStr);

      if (len == 5) continue;
      else if (len == 2) one = currStr;
      else if (len == 3) seven = currStr;
      else if (len == 4) four = currStr;
      else if (len == 7) eight = currStr;
    }

    char topLeft_L_InFour;

  }

  fclose(f);
  return 0;
}

bool unorderedCompare(char *str1, char *str2) {
  if (strlen(str1) != strlen(str2)) return -1;

  int str1CharCount[26] = {0};
  int str2CharCount[26] = {0};

  for (int idx = 0; idx < strlen(str1); idx++) {
    str1CharCount[str1[idx] - 97]++;
    str2CharCount[str2[idx] - 97]++;
  }

  for (int idx = 0; idx < 26; idx++) {
    if (str1CharCount[idx] != str2CharCount[idx]) return str1CharCount[idx];
  }

  return 0;
}

int sumChars(char *str) {
  int numOfChars = strlen(str);
  int sum = 0;
  for (int i = 0; i < numOfChars; i++) {
    sum += str[i];
  }
  return sum;
}

// return true if a contains all chars of b
bool everyChar(char* b, char* a) {
  int aLen = strlen(a);
  int bLen = strlen(b);

  for (int i = 0; i < aLen; i++) {
    int includes = 0;
    for (int j = 0; j < bLen; j++) {
      if (a[i] == b[j]) {
        includes = 1;
        break;
      }
    }

    if (!includes) return false;
  }

  return true;
}
