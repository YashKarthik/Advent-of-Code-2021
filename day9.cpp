#include <fstream>
#include <iostream>
#include <string>


const int N{1024};
int isLowPoint(int (*heightMap)[N], int currRow, int currCol, int numCols, int numRows);
int findBasinSize(int (*heightMap)[N], int row, int col, int numCols, int numRows);

int main() {
  int numCols{0};
  int numRows{0};
  int risk{0};

  std::string line;
  int heightMap[N][N];
  std::ifstream inputFile("./input9.txt");

  if (inputFile.is_open()) {
    int row{0};
    while (getline(inputFile, line)) {
      numRows++;
      if (numCols == 0) numCols = line.length();

      for (int col{0}; col < line.length(); col++) {
        heightMap[row][col] = line[col] - '0';
      }

      row++;
    }
  } else {
    std::cout << "Couldn't open file.";
  }

  for (int i{0}; i < numRows; i++) {
    for (int j{0}; j < numCols; j++) {
      if (isLowPoint(heightMap, i, j, numCols, numRows)) {
        std::cout << heightMap[i][j] << " " <<
        findBasinSize(heightMap, i, j, numCols, numRows) << std::endl;
      }
    }
  }

  for (int i{0}; i < numRows; i++) {
    for (int j{0}; j < numCols; j++) {
      if (isLowPoint(heightMap, i, j, numCols, numRows)) {
        std::cout << "\e[1m\033[31m"; 

        risk += 1 + heightMap[i][j];
      } else if (heightMap[i][j] != 9) {
        std::cout << "\033[38;5;216m"; 
      }
      std::cout << heightMap[i][j] << "\e[0m ";
    }
    std::cout << std::endl;
  }

  std::cout << "\nRisk level: " << risk << std::endl;
  return 0;
}

int isLowPoint(int (*heightMap)[N], int currRow, int currCol, int numCols, int numRows) {
  int fails{0};

  // test right
  if (currCol + 1 >= numCols) fails++;
  else if (heightMap[currRow][currCol] >= heightMap[currRow][currCol + 1]) return 0;
  else fails++;

  // test left
  if (currCol == 0) fails++;
  else if (heightMap[currRow][currCol] >= heightMap[currRow][currCol - 1]) return 0;
  else fails++;

  // test top
  if (currRow == 0) fails++;
  else if (heightMap[currRow][currCol] >= heightMap[currRow - 1][currCol]) return 0;
  else fails++;

  // test top
  if (currRow + 1 >= numRows) fails++;
  else if (heightMap[currRow][currCol] >= heightMap[currRow + 1][currCol]) return 0;
  else fails++;

  return fails == 4 ? 1 : 0;
}

int findBasinSize(int (*heightMap)[N], int row, int col, int numCols, int numRows) {
  int result{0};

  if (row < 0) return result;
  else if (col < 0) return result;
  else if (row == numRows) return result;
  else if (col == numCols) return result;

  if (heightMap[row][col - 1] == heightMap[row][col] + 1) {
    result++;
    result += findBasinSize(heightMap, row, col - 1, numCols, numRows);
  }

  if (heightMap[row][col + 1] == heightMap[row][col] + 1) {
    result++;
    result += findBasinSize(heightMap, row, col + 1, numCols, numRows);
  }

  if (heightMap[row - 1][col] == heightMap[row][col] + 1) {
    result++;
    result += findBasinSize(heightMap, row - 1, col, numCols, numRows);
  }

  if (heightMap[row + 1][col] == heightMap[row][col] + 1) {
    result++;
    result += findBasinSize(heightMap, row + 1, col, numCols, numRows);
  }

  return result;
}
