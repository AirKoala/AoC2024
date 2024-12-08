#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Operation {
  uint64_t result;
  uint16_t operands[50];
  size_t n_operands;
};

struct Operation parse_line(char *line) {
  struct Operation op;

  char *next;
  op.result = strtoull(line, &next, 10);
  op.n_operands = 0;
  next++; // skip ':'

  do {
    line = next;
    op.operands[op.n_operands++] = strtol(line, &next, 10);
  } while (next > line && op.n_operands < 50);
  op.n_operands--;

  return op;
}

uint64_t get_result(uint16_t *operands, char *operators, size_t n) {
  uint64_t res = operands[0];
  for (size_t i = 1; i < n; i++) {
    switch (operators[i - 1]) {
    case '+':
      res += operands[i];
      break;
    case '*':
      res *= operands[i];
      break;
    default:
      printf("Error: Unknown operator %c.\n", operators[i - 1]);
      for (size_t i = 0; i < n - 1; i++) {
          printf("%c ", operators[i]);
      }
      exit(EXIT_FAILURE);
    }
  }

  return res;
}

void advance_operators(char *operators, size_t n_operators) {
  if (n_operators <= 0) {
    return;
  }

  operators[0]++;

  if (operators[0] > 3) {
    operators[0] = 0;
    advance_operators(operators + 1, n_operators - 1);
  }
}

void print_operators(char *operators, size_t n_operators) {
  for (size_t i = 0; i < n_operators; i++) {  
    printf("%c ", operators[i]);
  }
}

void get_operators(char *operators, size_t n, size_t i) {
  size_t mask = i;
  printf("%zu / %d ", mask, (1 << n) - 1);
  while (n-- > 0) {
    operators[n] = (mask & 1) ? '*' : '+';
    printf("%c", operators[n]);
    mask >>= 1;
  }
  puts("");
}

bool is_valid(struct Operation *operation) {
  size_t n_operators = operation->n_operands - 1;
  char operators[n_operators];

  size_t nmax = 1 << n_operators;

  for (size_t i = 0; i < nmax; i++) {
    get_operators(operators, n_operators, i);
    uint64_t res =
        get_result(operation->operands, operators, operation->n_operands);

    if (operation->result == res) {
      return true;
    }
  }
  return false;
}

void print_op(struct Operation *op) {
  printf("%zu operands.\n", op->n_operands);
  printf("%lu:", op->result);
  for (size_t i = 0; i < op->n_operands; i++) {
    printf(" %d", op->operands[i]);
  }
  printf("\n");
}

int main(void) {
  struct Operation ops[850];

  char buf[50];
  size_t i = 0;
  while (fgets(buf, 50, stdin) && i < 850) {
    ops[i++] = parse_line(buf);
  }

  uint64_t sum = 0;
  for (size_t i = 0; i < 850; i++) {
    print_op(&ops[i]);
    if (is_valid(&ops[i])) {
      puts("Valid.");
      sum += ops[i].result;
    }
    puts("");
  }

  printf("\nSum: %lu", sum);
  return 0;
}
