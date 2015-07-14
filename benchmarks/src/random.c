/* -*- mode: c -*-
 * $Id: random.gcc,v 1.14 2001/05/08 01:36:50 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <math.h>

// #include "stdthing.h"

#define IM 139968
#define IA 3877
#define IC 29573

double gen_random(double max);

int
main(int argc, char *argv[]) {
  int N = 100000000;
  double result = 0;
    
  while (N--) {
    result = gen_random(100.0);
  }
  printf("%d %.9f\n", 0, result);
  return(0);
}

double
gen_random(double max) {
  static long last = 42;
    
  last = (last * IA + IC) % IM;
  return( max * last / IM );
}
