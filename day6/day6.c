#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

const size_t S = 130;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Guard {
  int32_t i;
  int32_t j;
  enum Direction direction;
};

void load_map(bool map[S][S], struct Guard *guard) {
  for (size_t i = 0; i < S; i++) {
    for (size_t j = 0; j < S; j++) {
      switch (getchar()) {
      case '^':
        guard->direction = UP;
        guard->i = i;
        guard->j = j;
        break;
      case '#':
        map[i][j] = true;
        break;
      default:
        map[i][j] = false;
      }
    }

    // Discard newline
    getchar();
  }
}

void print_map(bool map[S][S], struct Guard *guard) {
  for (size_t i = 0; i < S; i++) {
    for (size_t j = 0; j < S; j++) {
      if (i == guard->i && j == guard->j) {
        switch (guard->direction) {
        case UP:
          putchar('^');
          break;
        case DOWN:
          putchar('v');
          break;
        case LEFT:
          putchar('<');
          break;
        case RIGHT:
          putchar('>');
          break;
        }
        continue;
      }

      putchar(map[i][j] ? '#' : '.');
    }
    putchar('\n');
  }
}

struct Guard next_pos(bool map[S][S], struct Guard current) {
  struct Guard temp = current;
  switch (current.direction) {
  case UP:
    temp.i -= 1;
    break;
  case DOWN:
    temp.i += 1;
    break;
  case LEFT:
    temp.j -= 1;
    break;
  case RIGHT:
    temp.j += 1;
    break;
  }

  if (temp.i < 0 || temp.i >= S || temp.j < 0 || temp.j >= S) {
    return temp;
  }

  if (map[temp.i][temp.j]) {
    // Collision, rotate CW
    switch (current.direction) {
    case UP:
      current.direction = RIGHT;
      break;
    case DOWN:
      current.direction = LEFT;
      break;
    case LEFT:
      current.direction = UP;
      break;
    case RIGHT:
      current.direction = DOWN;
      break;
    }

    return next_pos(map, current);
  }
  return temp;
}

bool is_in_array(struct Guard guard, struct Guard *arr, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (guard.i == arr[i].i && guard.j == arr[i].j &&
        guard.direction == arr[i].direction) {
      return true;
    }
  }

  return false;
}

bool will_be_stuck(bool map[S][S], struct Guard guard) {
  bool visited[S][S];
  const size_t limit = 100000;
  struct Guard history[limit];
  size_t n_history = 0;

  while (guard.i >= 0 && guard.i < S && guard.j >= 0 && guard.j <= S) {
    if (is_in_array(guard, history, n_history)) {
      return true;
    }

    history[n_history++] = guard;
    guard = next_pos(map, guard);

    if (n_history >= limit) {
      return false;
    }
  }

  return false;
}

int main(void) {
  struct Guard guard;
  bool map[S][S];
  bool visited_no_obs[S][S];

  load_map(map, &guard);
  print_map(map, &guard);

  struct Guard original_guard = guard;

  uint32_t n_visited = 0;

  while (guard.i >= 0 && guard.i < S && guard.j >= 0 && guard.j <= S) {
    if (!visited_no_obs[guard.i][guard.j]) {
      n_visited++;
      visited_no_obs[guard.i][guard.j] = true;
    }

    guard = next_pos(map, guard);
  }

  int32_t original_route[n_visited][2];
  size_t n = 0;
  for (size_t i = 0; i < S; i++) {
    for (size_t j = 0; j < S; j++) {
      if (visited_no_obs[i][j]) {
        // printf("[%zu %zu]\n", i, j);
        original_route[n][0] = i;
        original_route[n][1] = j;
        n++;
      }
    }
  }

  int32_t n_blockable = 0;

  for (size_t i = 0; i < n_visited; i++) {
    // Add obstacle
    map[original_route[i][0]][original_route[i][1]] = true;
    if (will_be_stuck(map, original_guard)) {
      n_blockable++;
    }

    // Remove obstacle
    map[original_route[i][0]][original_route[i][1]] = false;
  }

  printf("Unique cells: %d\n", n_visited);
  printf("Blockable: %d\n", n_blockable);
  return 0;
}
