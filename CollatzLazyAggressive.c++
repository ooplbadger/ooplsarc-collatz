// CollatzLazyAggressive.c++


// --------
// includes
// --------

#include <utility>  // swap
#include <unordered_map>      // unordered_map

#include "CollatzLazyAggressive.h"

using namespace std;


// --------
// constants
// --------
static const int MAX_SEQUENCE_LENGTH = 1000;


// ------------
// collatz_get_cycle_length_lazy_aggressive
// - assume input is a natural integer and that no computations overflow a 32-bit integer
// ------------

/**
 * @param initial_collatz_input input value to collatz function
 * @return cycle length corresponding to input value
 *
 * Assume input value is valid (natural number).
 *
 * Note:  map is much slower than unordered_map.  In a test if 1-100,000,
 * "map" is slower than the "dumb" approach.
 */
int collatz_get_cycle_length_lazy_aggressive(int collatz_input)
{
  //------------------------- persistent

  // Initialize the base case:  1 has cycle length 1
  static unordered_map<int, int> cycle_length_map ( {{1, 1}} );

  //------------------------- this is persistent to reduce memory alloc/dealloc
  static int sequence_scratch_space[MAX_SEQUENCE_LENGTH];


  // Not needed by the algorithm, but this saves a little time if the value is already
  // cached
  if (cycle_length_map[collatz_input]) {
    return cycle_length_map[collatz_input];
  }


  int cycle_length = 0;
  sequence_scratch_space[0] = collatz_input;

  while (!cycle_length_map[collatz_input]) {
    if (collatz_input % 2 == 1) {
      // Odd:  n = 3n + 1
      collatz_input = collatz_input * 3 + 1;
    } else {
      // Even:  n = n / 2
      collatz_input >>= 1;
    }

    ++cycle_length;

    sequence_scratch_space[cycle_length] = collatz_input;
  }

  int true_cycle_length = cycle_length_map[collatz_input];

  while (cycle_length > 0) {
    cycle_length_map[sequence_scratch_space[--cycle_length]] = ++true_cycle_length;
  }

  return true_cycle_length;

//  cycle_length += cycle_length_map[collatz_input];
//
//  cycle_length_map[sequence_scratch_space[0]] = cycle_length;
//
//  return cycle_length;
}

// ------------
// collatz_eval_lazy_aggressive
// ------------

int collatz_eval_lazy_aggressive (int i, int j) {
  // Ensure i <= j
  if (i > j) {
    swap(i, j);
  }

  int max_cycle_length = 1;
  for (auto collatz_input = i; collatz_input <= j; collatz_input++) {
    int current_cycle_length = collatz_get_cycle_length_lazy_aggressive(collatz_input);
    //    cout << collatz_input << ":  " << current_cycle_length << endl;

    if (current_cycle_length > max_cycle_length) {
      max_cycle_length = current_cycle_length;
    }
  }

  return max_cycle_length;
}
