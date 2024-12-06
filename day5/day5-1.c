#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t parse_rules(uint8_t rules[][2]) {
  size_t n = 0;
  uint8_t i, j;
  char buffer[10];

  while (fgets(buffer, 10, stdin) != NULL &&
         sscanf(buffer, "%hhd|%hhd", &i, &j) == 2) {
    rules[n][0] = i;
    rules[n][1] = j;
    n++;
  }

  return n;
}

size_t parse_line(char *line, uint8_t *pages) {
  size_t n_pages = 0;

  char *next = line - 1;

  do {
    line = next + 1;
    pages[n_pages++] = strtol(line, &next, 10);
  } while (next > line);

  // -1 because we're reading 1 extra always
  return n_pages - 1;
}

void print_rules(uint8_t rules[][2], size_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("%hhd|%hhd\n", rules[i][0], rules[i][1]);
  }
  printf("%zu rules.\n", n);
}

bool is_line_valid(uint8_t *pages, size_t n_pages, uint8_t rules[][2],
                   size_t n_rules) {
  for (size_t i = 0; i < n_pages; i++) {
    for (size_t r = 0; r < n_rules; r++) {
      if (pages[i] == rules[r][0]) {
        for (size_t j = 0; j < i; j++) {
          if (pages[j] == rules[r][1]) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

int main(void) {
  uint8_t rules[1200][2];
  size_t n_rules = parse_rules(rules);
  print_rules(rules, n_rules);

  char line[200];

  long sum = 0;

  while (fgets(line, 200, stdin) != NULL) {
    uint8_t pages[20];
    size_t n_pages = parse_line(line, pages);

    // Print the pages
    for (size_t i = 0; i < n_pages; i++) {
      printf("%hhd,", pages[i]);
    }

    if (is_line_valid(pages, n_pages, rules, n_rules)) {
      size_t mid = n_pages / 2;
      sum += pages[mid];

      printf("valid\n");
    } else {
      printf("invalid\n");
    }

    printf("\n");
  }

  printf("Sum: %ld\n", sum);

  return 0;
}
