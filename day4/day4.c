#include <stdbool.h>
#include <stdio.h>

const int S = 140;
const char word[] = "XMAS";
const char rword[] = "SAMX";

void printgrid(char grid[S][S]) {
  for (int i = 0; i < S; i++) {
    for (int j = 0; j < S; j++) {
       putchar(grid[i][j]);
    }
    putchar('\n');
  }
}

bool checkh(char grid[S][S], int r, int c) {
  if (S - c < 4) {
    return false;
  }

  bool matching = true;
  for (int dr = 0; dr < 4; dr++) {
    if (grid[r][c + dr] != word[dr]) {
      matching = false;
      break;
    }
  }

  if (matching) {
    return true;
  }

  matching = true;
  for (int dr = 0; dr < 4; dr++) {
    if (grid[r][c + dr] != rword[dr]) {
      matching = false;
      break;
    }
  }
  return matching;
}

bool checkv(char grid[S][S], int r, int c) {
  if (S - r < 4) {
    return false;
  }

  bool matching = true;
  for (int dr = 0; dr < 4; dr++) {
    if (grid[r + dr][c] != word[dr]) {
      matching = false;
      break;
    }
  }

  if (matching) {
    return true;
  }

  matching = true;
  for (int dr = 0; dr < 4; dr++) {
    if (grid[r + dr][c] != rword[dr]) {
      matching = false;
      break;
    }
  }
  return matching;
}

bool checkd1(char grid[S][S], int r, int c) {
  if (S - r < 4 || S - c < 4) {
    return false;
  }

  bool matching = true;
  for (int d = 0; d < 4; d++) {
    if (grid[r + d][c + d] != word[d]) {
      matching = false;
      break;
    }
  }

  if (matching) {
    return true;
  }

  matching = true;
  for (int d = 0; d < 4; d++) {
    if (grid[r + d][c + d] != rword[d]) {
      matching = false;
      break;
    }
  }
  return matching;
}

bool checkd2(char grid[S][S], int r, int c) {
  if (S - r < 4 || c < 3) {
    return false;
  }

  bool matching = true;
  for (int d = 0; d < 4; d++) {
    if (grid[r + d][c - d] != word[d]) {
      matching = false;
      break;
    }
  }

  if (matching) {
    return true;
  }

  matching = true;
  for (int d = 0; d < 4; d++) {
    if (grid[r + d][c - d] != rword[d]) {
      matching = false;
      break;
    }
  }
  return matching;
}

int main(void) {
  char grid[S][S];

  for (int i = 0; i < S; i++) {
    for (int j = 0; j < S; j++) {
      grid[i][j] = getchar();
    }
    getchar(); // discard newline
  }

  printgrid(grid);

  long nmatches = 0;
  for (int i = 0; i < S; i++) {
    for (int j = 0; j < S; j++) {
      if (checkh(grid, i, j)) {
        nmatches++;
      }
      if (checkv(grid, i, j)) {
        nmatches++;
      }
      if (checkd1(grid, i, j)) {
        nmatches++;
      }
      if (checkd2(grid, i, j)) {
        nmatches++;
      }
    }
  }

  printf("Matches: %ld\n", nmatches);
  return 0;
}
