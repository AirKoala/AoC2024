#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int parseLine(char *str, int *arr) {
  int i = 0;

  char *current = str;
  char *next;
  int num = strtol(current, &next, 10);

  while (next > current) {
    current = next;
    arr[i++] = num;
    num = strtol(current, &next, 10);
  }

  return i;
}

bool checkReport(int *nums, int count, int skipIndex) {
  // printNums(nums, count, skipIndex);
  int i = 0;
  if (skipIndex == 0)
    i++; // discard first

  int prevNum = nums[i++];

  if (skipIndex == 1)
    i++; // discard second

  int num = nums[i++];

  bool increasing = num > prevNum;

  int diff = increasing ? num - prevNum : prevNum - num;

  if (diff < 1 || diff > 3) {
    return false;
  }

  while (i < count) {
    if (i == skipIndex) {
      i++;
      continue;
    }
    int nextNum = nums[i++];

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
  }

  return true;
}

int main(void) {
  char buffer[100];
  int nCorrect = 0;

  while (fgets(buffer, 100, stdin)) {
    for (int skip = -1; skip < 10; skip++) {
      int nums[50];
      int nNums = parseLine(buffer, nums);
      // printNums(nums, nNums, -1);

      if (checkReport(nums, nNums, skip)) {
        nCorrect++;
        break;
      }
    }
  }

  printf("nCorrect: %d\n", nCorrect);
  return 0;
}
