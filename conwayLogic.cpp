#include <cheerp/client.h> //Misc client side stuff
#include <cheerp/clientlib.h>
#include <iostream>

[[cheerp::genericjs]] int conwayKernel(int **board, int iloc, int jloc,
                                       int rows, int cols) {
  int iMinLoc = iloc > 0 ? iloc - 1 : 0;

  int iMaxLoc = iloc + 1 < rows ? iloc + 2 : rows;

  int jMinLoc = jloc > 0 ? jloc - 1 : 0;

  int jMaxLoc = jloc + 1 < cols ? jloc + 2 : cols;

  int neighborCount = 0;

  // std::cout  << " | kernel at: " << iloc << ", " << jloc;
  // std::cout  << " range: " << iMinLoc << ", " << iMaxLoc << ", " << jMinLoc
  // << ", " << jMaxLoc;
  for (int i = iMinLoc; i < iMaxLoc; i++) {
    for (int j = jMinLoc; j < jMaxLoc; j++) {
      // std::cout  << " ckeck " << i << ", " << j << ": ";
      neighborCount += board[i][j];
      // std::cout  << neighborCount << "; ";
    }
  }
  int isAlive = board[iloc][jloc] == 1;
  if (isAlive) {
    return (2 < neighborCount && neighborCount < 5);
  }
  return neighborCount == 3;
}
[[cheerp::genericjs]] int **getNextBoard(int **board, int rows, int cols) {
  int **next = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    next[i] = (int *)malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      next[i][j] = conwayKernel(board, i, j, rows, cols);
      // std::cout  << next[i][j];
    }
  }

  // std::cout  << " end\n";
  return next;
}

[[cheerp::genericjs]] int **getBoardDiff(int **prev, int **next, int rows,
                                         int cols) {
  int **diff = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    diff[i] = (int *)malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      diff[i][j] = prev[i][j] ^ next[i][j];
    }
  }
  return diff;
}

[[cheerp::genericjs]] int **tick(int ***boardPtr, int rows, int cols) {
  int **board = *boardPtr;
  // std::cout  << "tick \n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // std::cout  << board[i][j] << ", ";
    }
    // std::cout  << "\n";
  }

  int **nextBoard, **diff;
  nextBoard = getNextBoard(board, rows, cols);
  diff = getBoardDiff(board, nextBoard, rows, cols);
  *boardPtr = nextBoard;
  return diff;
}
