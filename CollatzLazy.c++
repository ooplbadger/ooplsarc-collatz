// CollatzLazy.c++


// --------
// includes
// --------

#include <utility>  // swap
#include <map>      // map

#include "CollatzLazy.h"

using namespace std;


// ------------
// collatz_get_cycle_length_lazy
// - assume input is a natural integer and that no computations overflow a 32-bit integer
// ------------

/**
 * @param initial_collatz_input input value to collatz function
 * @return cycle length corresponding to input value
 *
 * Assume input value is valid (natural number).
 */
int collatz_get_cycle_length_lazy(int initial_collatz_input)
{
  static map<int, int> cycle_length_map;

  if (cycle_length_map[initial_collatz_input]) {
    return cycle_length_map[initial_collatz_input];
  }

  int cycle_length = 1;
  int collatz_input = initial_collatz_input;

  while (collatz_input != 1) {
    if (collatz_input % 2 == 1) {
      // Odd:  n = 3n + 1
      collatz_input = collatz_input * 3 + 1;
    } else {
      // Even:  n = n / 2
      collatz_input >>= 1;
    }

    if (cycle_length_map[collatz_input]) {
      cycle_length += cycle_length_map[collatz_input];
      break;
    }

    ++cycle_length;
  }

  cycle_length_map[initial_collatz_input] = cycle_length;

  return cycle_length;
}

// ------------
// collatz_eval_lazy
// ------------

int collatz_eval_lazy (int i, int j) {
  // Ensure i <= j
  if (i > j) {
    swap(i, j);
  }

  int max_cycle_length = 1;
  for (auto collatz_input = i; collatz_input <= j; collatz_input++) {
    int current_cycle_length = collatz_get_cycle_length_lazy(collatz_input);
    //    cout << collatz_input << ":  " << current_cycle_length << endl;

    if (current_cycle_length > max_cycle_length) {
      max_cycle_length = current_cycle_length;
    }
  }

  return max_cycle_length;
}
