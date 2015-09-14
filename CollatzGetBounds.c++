// CollatzGetBounds.c++


// --------
// includes
// --------

#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair, swap

#include "CollatzGetBounds.h"

using namespace std;


// --------
// globals
// --------

static const int BAD_CYCLE_LENGTH = 999999999;


// ------------
// collatz_get_cycle_length_getbounds
// - assume input is a natural integer and that no computations overflow a 32-bit integer
// ------------

/**
 * @param collatz_input input value to collatz function
 * @param[out] bounds minimum and maximum integers reached during computation
 * @return cycle length corresponding to input value
 *
 * Assume input value is valid (natural number).
 */
int collatz_get_cycle_length_getbounds(int collatz_input, pair<int, int> &bounds)
{
  int cycle_length = 1;

  while (collatz_input != 1) {
    ++cycle_length;

    if (collatz_input % 2 == 1) {
      // Odd:  n = 3n + 1
      collatz_input = collatz_input * 3 + 1;
    } else {
      // Even:  n = n / 2
      collatz_input >>= 1;
    }

    if (collatz_input > bounds.second) {
      bounds.second = collatz_input;
    } else if (collatz_input < bounds.first) {
      bounds.first = collatz_input;
      return BAD_CYCLE_LENGTH;
    }
  }

  return cycle_length;
}

// ------------
// collatz_eval_getbounds - report min/max
// ------------

int collatz_eval_getbounds (int i, int j) {
  // Ensure i <= j
  if (i > j) {
    swap(i, j);
  }

  pair<int, int> bounds = make_pair(1, 1);

  int max_cycle_length = 1;
  for (auto collatz_input = i; collatz_input <= j; collatz_input++) {
    pair<int, int> current_bounds = make_pair(1, collatz_input);
    int current_cycle_length = collatz_get_cycle_length_getbounds(collatz_input, current_bounds);

    if (current_cycle_length > max_cycle_length) {
      max_cycle_length = current_cycle_length;
    }

    if (current_bounds.first < bounds.first) {
      bounds.first = current_bounds.first;
    }

    if (current_bounds.second > bounds.second) {
      bounds.second = current_bounds.second;
    }
  }

  cout << "Min = " << bounds.first  << endl;
  cout << "Max = " << bounds.second << endl;

  return max_cycle_length;
}

