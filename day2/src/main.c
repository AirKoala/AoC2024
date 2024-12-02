#include <stdbool.h>
#include <stdio.h>

int parseNum(char **str) {
  int num = 0;

  while (**str >= '0' && **str <= '9') {
    num = num * 10 + **str - '0';
    (*str)++;
  }

  return num;
}

bool checkReport(char *str) {
  int prevNum = parseNum(&str);
  // ++ so that the pointer ends up on next number starting position
  str++;
  int num = parseNum(&str);
  str++;

  bool increasing = num > prevNum;

  int diff = 0;
  if (increasing) {
    diff = num - prevNum;
  } else {
    diff = prevNum - num;
  }

  if (diff < 1 || diff > 3) {
    return false;
  }

  while (*str) {
    int nextNum = parseNum(&str);

    int diff = 0;
    if (increasing) {
      diff = nextNum - num;
    } else {
      diff = num - nextNum;
    }

    if (diff < 1 || diff > 3) {
      return false;
    }

    num = nextNum;
    str++;
  }

  return true;
}

int main(void) {
  char buffer[100];
  int nCorrect = 0;

  while (fgets(buffer, 100, stdin)) {
    if (checkReport(buffer)) {
      nCorrect++;
    }
  }

  printf("%d", nCorrect);
  return 0;
}
