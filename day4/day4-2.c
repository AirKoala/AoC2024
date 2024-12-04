#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

const int S = 140;

void printgrid(char grid[S][S]) {
  for (int i = 0; i < S; i++) {
    for (int j = 0; j < S; j++) {
       putchar(grid[i][j]);
    }
    putchar('\n');
  }
}

void print3x3(char grid[S][S], size_t r, size_t c) {
  for (int i = r; i < r + 3; i++) {
    for (int j = c; j < c + 3; j++) {
      putchar(grid[i][j]);
    }
    putchar('\n');
  }
}

bool checkd1(char grid[S][S], const char* substr, size_t r, size_t c) {
  size_t n = strlen(substr);

  if (S - r < n || S - c < n) {
    return false;
  }

  for (int d = 0; d < n; d++) {
    if (grid[r + d][c + d] != substr[d]) {
      return false;
    }
  }
  return true;
}

bool checkd2(char grid[S][S], const char* substr, size_t r, size_t c) {
  size_t n = strlen(substr);

  if (S - r < n || c < n - 1) {
    return false;
  }

  bool matching = true;
  for (int d = 0; d < n; d++) {
    if (grid[r + d][c - d] != substr[d]) {
      return false;
    }
  }

  return true;
}

bool check(char grid[S][S], size_t r, size_t c) {
  char *substr = "MAS";
  char *rsubstr = "SAM";
  size_t n = strlen(substr);

  if (r + n > S || c + n > S) {
    return false;
  }

  bool d1matches = checkd1(grid, substr, r, c) || checkd1(grid, rsubstr, r, c);
  bool d2matches = checkd2(grid, substr, r, c + n - 1) || checkd2(grid, rsubstr, r, c + n - 1);
  
  if (d1matches || d2matches) {
    printf("Match at (%zu, %zu)\n", r, c);
    printf("d1matches = %d\n", d1matches);
    printf("d2matches = %d\n", d2matches);
    print3x3(grid, r, c);
    printf("\n");
  }

  return d1matches && d2matches;
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
      if (check(grid, i, j)) {
        nmatches++;
      }
    }
  }

  printf("Matches: %ld\n", nmatches);
  return 0;
}
