// CollatzGetBounds.h

#ifndef Collatz_Get_Bounds_h
#define Collatz_Get_Bounds_h

// ------------
// collatz_eval_getbounds - report min/max
// ------------

/**
 * @param i one end       of the range, inclusive
 * @param j the other end of the range, inclusive
 * @return the max cycle length of the range [i, j]
 *
 * All i, j will be less than 1,000,000 and greater than 0.
 * No operation overflows a 32-bit integer if i,j < 100,000.
 *
 * NOTE:  if i,j > 100,000, then we can easily overflow 32-bit integer
 * but we do not check this case.
 */
int collatz_eval_getbounds (int i, int j);


#endif	// Collatz_Get_Bounds_h
