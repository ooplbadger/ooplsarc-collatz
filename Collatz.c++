// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair, swap

//#include "CollatzLazy.h"
//#include "CollatzLazyAggressiveArray.h"
#include "CollatzLazyAggressive.h"
#include "Collatz.h"

using namespace std;


// ------------
// collatz_get_cycle_length_dumb
// - assume input is a natural integer and that no computations overflow a 32-bit integer
// ------------

/**
 * @param collatz_input input value to collatz function
 * @return cycle length corresponding to input value
 *
 * Assume input value is valid (natural number).
 */
int collatz_get_cycle_length_dumb(int collatz_input)
{
  int cycle_length = 1;

  while (collatz_input != 1) {
    if (collatz_input % 2 == 1) {
      // Odd:  n = 3n + 1
      // Optimization #1 from 10 Sep 2015 class
      collatz_input += (collatz_input >> 1) + 1;
      cycle_length += 2;
    } else {
      // Even:  n = n / 2
      collatz_input >>= 1;
      ++cycle_length;
    }
  }

  return cycle_length;
}


// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval_dumb - initial implementation
// ------------

int collatz_eval_dumb (int i, int j) {
  // Ensure i <= j
  if (i > j) {
    swap(i, j);
  }


  //-------------------------
  // Optimization #2 from 10 Sep 2015 class:
  //   Given positive integers, b and e,
  //   let m = (e/2) + 1.
  //   
  //   If b < m, then
  //   mcl(b, e) = mcl(m, e).
  int mid = j/2 + 1;
  if (i < mid) {
    i = mid;
  }
  

  //-------------------------
  int max_cycle_length = 1;
  for (auto collatz_input = i; collatz_input <= j; collatz_input++) {
    int current_cycle_length = collatz_get_cycle_length_dumb(collatz_input);
    //    cout << collatz_input << ":  " << current_cycle_length << endl;

    if (current_cycle_length > max_cycle_length) {
      max_cycle_length = current_cycle_length;
    }
  }

  return max_cycle_length;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
  //  return collatz_eval_dumb(i, j);
  //  return collatz_eval_lazy(i, j);
  //  return collatz_eval_lazy_aggressive_array(i, j);
  return collatz_eval_lazy_aggressive(i, j);
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
