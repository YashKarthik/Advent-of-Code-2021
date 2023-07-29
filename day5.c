#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_NUM_OF_LINES 2048

typedef struct point {
  int x;
  int y;
} point;

typedef struct line {
  point start;
  point end;
} line;

int isOrthogonal(line testLine) {
  if (testLine.start.x == testLine.end.x) return -1; // xs are same => vertical line
  else if (testLine.start.y == testLine.end.y) return 1; // ys are same => horizontal line
  else return 0;
}

int main() {
  FILE *f = fopen("./input5.txt", "r");

  line lines[MAX_NUM_OF_LINES];
  int numOfLines = 0;
  int max_x = 0;
  int max_y = 0;

  while (fscanf(
        f,
        "%d,%d -> %d,%d",
        &lines[numOfLines].start.x,
        &lines[numOfLines].start.y,
        &lines[numOfLines].end.x,
        &lines[numOfLines].end.y
        ) == 4) {

    if (lines[numOfLines].start.x > max_x) max_x = lines[numOfLines].start.x;
    if (lines[numOfLines].end.x > max_x) max_x = lines[numOfLines].end.x;
    if (lines[numOfLines].start.y > max_y) max_y = lines[numOfLines].start.y;
    if (lines[numOfLines].end.y > max_y) max_y = lines[numOfLines].end.y;

    numOfLines++;
  }

  /* Our map will be a 2-D array;
   * row -> y val; index within row -> x val;
   * Each cell within the inside-array will hold the number of lines that cross that point
   * Access like so: linesMap[y][x];
   */
  int **linesMap = malloc((max_y + 1) * sizeof(int*)); // len is one more than last index
  for (int i = 0; i < max_y + 1; i++) {
    linesMap[i] = calloc(max_x + 1, sizeof(int));
  }
  
  for (int currLineIdx = 0; currLineIdx < numOfLines; currLineIdx++) {

    line currLine = lines[currLineIdx];
    int orthogonality = isOrthogonal(currLine);

    if (orthogonality == 1) { // horizontal line

      if (currLine.start.x < currLine.end.x) {
        for (int x = currLine.start.x; x <= currLine.end.x; x++) {
          linesMap[currLine.start.y][x] += 1;
        }
      } else {
        for (int x = currLine.start.x; x >= currLine.end.x; x--) {
          linesMap[currLine.start.y][x] += 1;
        }
      }

    } else if (orthogonality == -1) { // vert line

      if (currLine.start.y < currLine.end.y) {
        for (int y = currLine.start.y; y <= currLine.end.y; y++) {
          linesMap[y][currLine.start.x] += 1;
        }
      } else {
        for (int y = currLine.start.y; y >= currLine.end.y; y--) {
          linesMap[y][currLine.start.x] += 1;
        }
      }
    } else { // diagonals

      if (currLine.start.x < currLine.end.x) {

        if (currLine.start.y < currLine.end.y) {
          int y = currLine.start.y;
          for (int x = currLine.start.x; x <= currLine.end.x; x++) {
            if (y > currLine.end.y) break;
            linesMap[y][x] += 1;
            y++;
          }
        } else {

          int y = currLine.start.y;
          for (int x = currLine.start.x; x <= currLine.end.x; x++) {
            if (y < currLine.end.y) break;
            linesMap[y][x] += 1;
            y--;
          }

        }

      } else {

        if (currLine.start.y < currLine.end.y) {
          int y = currLine.start.y;
          for (int x = currLine.start.x; x >= currLine.end.x; x--) {
            if (y > currLine.end.y) break;
            linesMap[y][x] += 1;
            y++;
          }
        } else {

          int y = currLine.start.y;
          for (int x = currLine.start.x; x >= currLine.end.x; x--) {
            if (y < currLine.end.y) break;
            linesMap[y][x] += 1;
            y--;
          }

        }

      }
    }
  }

  int overlaps = 0;
  for (int y = 0; y < max_y + 1; y++) {
    for (int x = 0; x < max_x + 1; x++) {
      if (linesMap[y][x] >= 2) overlaps++;
    }

    free(linesMap[y]);
  }
  free(linesMap);
  fclose(f);

  printf("Overlaps: %i\n", overlaps);
  return 0;
}
