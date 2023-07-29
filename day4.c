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
  bool completed;
} BingoBoard;

int sumUnmarkedCells(BingoBoard winnerBoard);
int boardNumOftheFinalWinner(BingoBoard *bingoBoards, int numOfBoards);

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

  char *bingoMoveStr = strtok(bingo_moves, ",");
  int loserBoardIdx = -1;

  while (bingoMoveStr != NULL) {
    int bingoMove = atoi(bingoMoveStr);
    printf("Move: %i\n", bingoMove);

    for (int boardIdx = 0; boardIdx < numOfBoards; boardIdx++) {
      for (int cellIdx = 0; cellIdx < (ROWS * COLS); cellIdx++) {

        if (bingoBoards[boardIdx].cells[cellIdx].number != bingoMove) continue;

        bingoBoards[boardIdx].cells[cellIdx].marked = true;
        bingoBoards[boardIdx].numOfMarkedCells++;
        printf("B_num: %i, Cell: %i\n", boardIdx, bingoBoards[boardIdx].cells[cellIdx].number);

      }
    }

    int finalWinnerIdx = boardNumOftheFinalWinner(bingoBoards, numOfBoards);
    if (finalWinnerIdx == 1) {
      for (int bdx = 0; bdx < numOfBoards; bdx++) {
        if (bingoBoards[bdx].completed == false) {
          printf("found loser");
          loserBoardIdx = bdx;
        }
      }
      printf("Loser board: %i\n", loserBoardIdx);
    }
    if (loserBoardIdx != -1) {
      int unmarkedSum = sumUnmarkedCells(bingoBoards[loserBoardIdx]);
      printf("\nFinal Winner board: %i\n", loserBoardIdx+1);
      printf("Unmarked sum: %i\n", unmarkedSum);
      printf("Winning Move: %i\n", bingoMove);
      printf("Score: %i\n", bingoMove*unmarkedSum);
      break;
    }

    bingoMoveStr = strtok(NULL, ",");
  }


  printf("\n");
  free(bingoBoards);
  fclose(f);
  return 0;
}

int boardNumOftheFinalWinner(BingoBoard *bingoBoards, int numOfBoards) {

  int numOfWinners = 0;

  for (int boardIdx = 0; boardIdx < numOfBoards; boardIdx++) {

    if (bingoBoards[boardIdx].completed) continue;

    for (int rowStart = 0; rowStart < (ROWS * COLS) - 5; rowStart+=5) {

      if (
          bingoBoards[boardIdx].cells[rowStart].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+1].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+2].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+3].marked == true &&
          bingoBoards[boardIdx].cells[rowStart+4].marked == true
         ) {
        numOfWinners++;
        bingoBoards[boardIdx].completed = true;
        break;
      }
    }

    if (bingoBoards[boardIdx].completed) continue;

    for (int colIdx = 0; colIdx < COLS; colIdx++) {

      if (
          bingoBoards[boardIdx].cells[colIdx].marked == true &&
          bingoBoards[boardIdx].cells[colIdx+5].marked == true &&
          bingoBoards[boardIdx].cells[colIdx+10].marked == true &&
          bingoBoards[boardIdx].cells[colIdx+15].marked == true &&
          bingoBoards[boardIdx].cells[colIdx+20].marked == true
         ) {
        numOfWinners++;
        break;
      }
      printf("potential: %i", boardIdx);
    }
  }
  if (numOfWinners == numOfBoards - 1) return 1;

  return 0;
}

int sumUnmarkedCells(BingoBoard winnerBoard) {

  int unmarkedSum = 0;
  for (int cellIdx = 0; cellIdx < (ROWS * COLS); cellIdx++) {

    if (winnerBoard.cells[cellIdx].marked) continue;

    unmarkedSum += winnerBoard.cells[cellIdx].number;
  }

  return unmarkedSum;
}
