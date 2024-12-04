#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void putsn(char *s, int n) {
  while (n-- > 0 && *s) {
    putchar(*(s++));
  }
  putchar('\n');
}

void printn(char *str, int n) {
  printf("%d chars: ", n);
  while (n-- > 0 && *str) {
    putchar(*(str++));
  }
  putchar('\n');
}

long strtoi(char *str, char **endptr) {
  long n = 0;

  while (*str >= '0' && *str <= '9') {
    n *= 10;
    n += *str - '0';
    str++;
  }

  *endptr = str;
  return n;
}

bool parsedo(char *str, char **endptr) {
  if (*str == '\0') {
    *endptr = str;
    return false;
  }

  if (strncmp(str, "do()", 4) != 0) {
    *endptr = str + 1;
    return false;
  }

  putsn(str, 4);

  *endptr = str + 4;
  return true;
}

bool parsedont(char *str, char **endptr) {
  if (*str == '\0') {
    *endptr = str;
    return false;
  }

  if (strncmp(str, "don't()", 7) != 0) {
    *endptr = str + 1;
    return false;
  }

  putsn(str, 7);

  *endptr = str + 7;
  return true;
}

bool parsemul(char *str, long *x, long *y, char **endptr) {
  if (*str == '\0') {
    *endptr = str;
    return false;
  }
  // printn(str, 5);
  if (strncmp(str, "mul(", 4) != 0) {
    *endptr = str + 1;
    return false;
  }

  putsn(str, 4);

  str += 4;

  char *next;

  *x = strtoi(str, &next);
  if (next == str) {
    // no int found
    *endptr = str;
    return false;
  }
  putsn(str, next - str);
  str = next;

  if (*str != ',') {
    *endptr = str;
    return false;
  }
  putsn(str, 1);
  str++;

  *y = strtoi(str, &next);
  if (next == str) {
    // no int found
    *endptr = str;
    return false;
  }

  putsn(str, next - str);
  str = next;

  if (*str != ')') {
    *endptr = str;
    return false;
  }
  putsn(str, 1);
  str++;

  *endptr = str;
  return true;
}

int main(void) {
  char input[20000];
  char c;
  int i = 0;
  while ((c = getchar()) != EOF) {
    input[i++] = c;
  }

  char *current;
  char *next;
  next = input;

  long long sum = 0;
  bool mulenabled = true;

  do {
    current = next;

    char *nextdo = NULL;
    char *nextdont = NULL;
    char *nextmul = NULL;

    if (parsedo(current, &nextdo)) {
      mulenabled = true;
    } else if (parsedont(current, &nextdont)) {
      mulenabled = false;
    } else if (mulenabled) {
      long x, y;
      if (parsemul(current, &x, &y, &nextmul)) {
        sum += x * y;
      }
    }

    next = nextdo;
    if (nextdont && nextdont < next) {
      next = nextdont;
    }
    if (nextmul && nextmul < next) {
      next = nextmul;
    }
  } while (next > current);

  printf("sum: %lld\n", sum);

  return 0;
}
