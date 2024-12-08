#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef char Operator;
#define ADD 0
#define MULT 1
#define CONC 2

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

uint32_t n_digits(uint64_t x) {
  uint32_t n_digits = 0;

  while (x > 0) {
    x /= 10;
    n_digits++;
  }

  return n_digits;
}

uint64_t concatenate(uint64_t a, uint64_t b) {
  uint32_t n_digits_b = n_digits(b);
  while (n_digits_b-- > 0) {
    a *= 10;
  }

  return a + b;
}

uint64_t get_result(uint16_t *operands, Operator *operators, size_t n) {
  uint64_t res = operands[0];
  for (size_t i = 1; i < n; i++) {
    switch (operators[i - 1]) {
    case ADD:
      res += operands[i];
      break;
    case MULT:
      res *= operands[i];
      break;
    case CONC:
      res = concatenate(res, operands[i]);
      break;
    default:
      printf("Error: Unknown operator %d.\n", operators[i - 1]);
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

  if (operators[0] > 2) {
    operators[0] = 0;
    advance_operators(operators + 1, n_operators - 1);
  }
}

void print_operators(char *operators, size_t n_operators) {
  const char ops[] = {'+', '*', '|'};

  for (size_t i = 0; i < n_operators; i++) {
    printf("%c ", ops[operators[i]]);
  }
  puts("");
}

bool is_valid(struct Operation *operation) {
  size_t n_operators = operation->n_operands - 1;
  Operator operators[n_operators];
  for (size_t i = 0; i < n_operators; i++) {
    operators[i] = ADD;
  }

  // size_t nmax = n_operators * n_operators * n_operators;
  size_t nmax = 1;
  for (size_t _ = 0; _ < n_operators; _++) {
    nmax *= 3;
  }


  for (size_t i = 0; i < nmax; i++) {
    print_operators(operators, n_operators);
    uint64_t res =
        get_result(operation->operands, operators, operation->n_operands);

    if (operation->result == res) {
      return true;
    }

    advance_operators(operators, n_operators);
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
