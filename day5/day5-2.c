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
                   size_t n_rules, size_t *pos1, size_t *pos2) {
  for (size_t i = 0; i < n_pages; i++) {
    for (size_t r = 0; r < n_rules; r++) {
      if (pages[i] == rules[r][0]) {
        for (size_t j = 0; j < i; j++) {
          if (pages[j] == rules[r][1]) {
            if (pos1 != NULL && pos2 != NULL) {
              *pos1 = i;
              *pos2 = j;
            }
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

  long sum_valid = 0;
  long sum_invalid = 0;

  while (fgets(line, 200, stdin) != NULL) {
    uint8_t pages[20];
    size_t n_pages = parse_line(line, pages);

    // Print the pages
    for (size_t i = 0; i < n_pages; i++) {
      printf("%hhd,", pages[i]);
    }

    if (is_line_valid(pages, n_pages, rules, n_rules, NULL, NULL)) {
      size_t mid = n_pages / 2;
      sum_valid += pages[mid];
      printf("valid\n");
    } else {
      printf("invalid\n");

      size_t pos1, pos2;
      while (!is_line_valid(pages, n_pages, rules, n_rules, &pos1, &pos2)) {
        printf("pos1: %zu, pos2: %zu\n", pos1, pos2);
        uint8_t tmp = pages[pos1];
        pages[pos1] = pages[pos2];
        pages[pos2] = tmp;
      }

      size_t mid = n_pages / 2;
      sum_invalid += pages[mid];
    }

    printf("\n");
  }

  printf("Valids: %ld\n", sum_valid);
  printf("Invalids: %ld\n", sum_invalid);
  return 0;
}
