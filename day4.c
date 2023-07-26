#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 5
#define MAX_LENGTH 2048

typedef struct GridUnit {
  int number;
  bool marked;
} GridUnit;

typedef struct BingoBoard {
  GridUnit cells[ROWS * COLS];
  int numOfMarkedCells;
} BingoBoard;

int main() {
  FILE *f = fopen("./input4.txt", "r");

  int maxBingoBoards = 1;
  int numOfBoards = 0;
  char bingo_moves[MAX_LENGTH] = ""; // will use strtok to read token from this
  BingoBoard *bingoBoards = (BingoBoard *)malloc(maxBingoBoards * sizeof(BingoBoard));

  // read only the first line, it contains comma-sep bingo moves
  if (fgets(bingo_moves, MAX_LENGTH, f) == NULL) {
    printf("No bingo moves found in file.\n");
    return 1;
  }

  int rowNumberWithinBoard = 0;
  char tempLine[MAX_LENGTH];
  while (fgets(tempLine, MAX_LENGTH, f) != NULL) {
    if (tempLine[0] == '\n') {
      numOfBoards++;
      rowNumberWithinBoard = 0;

      // allocate memory for new boards
      if (numOfBoards > maxBingoBoards) {
        maxBingoBoards *= 2;
        bingoBoards = (BingoBoard *)realloc(bingoBoards, (maxBingoBoards)*sizeof(BingoBoard));
      };

      continue;
    }
    rowNumberWithinBoard++;

    int i = 0;
    char *cellVal = strtok(tempLine, " ");
    // read cell value from line and put into row[5]
    while (cellVal) {
      if (*cellVal != ' ') {
        bingoBoards[numOfBoards - 1].cells[5 * (rowNumberWithinBoard - 1) + i].number = atoi(cellVal);
        bingoBoards[numOfBoards - 1].cells[5 * (rowNumberWithinBoard - 1) + i].marked = false;
        bingoBoards[numOfBoards - 1].numOfMarkedCells = 0;
        i++;
      }
      cellVal = strtok(NULL, " ");
    }
  }

  printf("Num of boards parsed: %i\n", numOfBoards);

  int bingoMove = atoi(strtok(bingo_moves, ","));
  while (bingoMove) {
    for (int boardIdx = 0; boardIdx < numOfBoards; boardIdx++) {
      for (int cellIdx = 0; cellIdx < (ROWS * COLS); cellIdx++) {

        if (bingoBoards[boardIdx].cells[cellIdx].number != bingoMove) continue;

        bingoBoards[boardIdx].cells[cellIdx].marked = true;
        bingoBoards[boardIdx].numOfMarkedCells++;

      }
    }
    bingoMove = atoi(strtok(NULL, ","));
  }


  printf("\n");
  free(bingoBoards);
  fclose(f);
  return 0;
}

int checkWin(BingoBoard *bingoBoards, int numOfBoards) {

  for (int boardIdx = 0; boardIdx < numOfBoards; boardIdx++) {
    for (int rowStart = 0; rowStart < (ROWS * COLS) - 5; rowStart+=5) {

      int markedInRow = 0;
      if (bingoBoards[boardIdx].numOfMarkedCells < 5) return -1;

      if (
          bingoBoards[boardIdx].cells[rowStart].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+1].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+2].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+3].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+4].marked == true
         ) return boardIdx;
    }

    //for (int colIdx = 0; colIdx < (ROWS * COLS) - 5; colIdx+=5) {

    //  int markedInRow = 0;
    //  if (bingoBoards[boardIdx].numOfMarkedCells < 5) return -1;

    //  if (
    //      bingoBoards[boardIdx].cells[colIdx].marked == true &&
    //      bingoBoards[boardIdx].cells[colIdx+1].marked == true &&
    //      bingoBoards[boardIdx].cells[colIdx+2].marked == true &&
    //      bingoBoards[boardIdx].cells[colIdx+3].marked == true &&
    //      bingoBoards[boardIdx].cells[colIdx+4].marked == true
    //     ) return boardIdx;
    //}
  }

}
