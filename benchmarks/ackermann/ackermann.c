/* -*- mode: c -*-
 * $Id: ackermann.gcc,v 1.5 2001/05/04 01:21:38 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */


// #include <stdio.h>
// #include <stdlib.h>

#include "stdthing.h"

int Ack(int M, int N);

// #define X86

#ifdef X86
void print(const char *str) {
  printf("%s", str);
}

void printnum(int n) {
  printf("%d", n);
}
#endif

int
main(int argc, char *argv[]) {
  int n = 2;
  int res = Ack(3, n);
  print("Ack(3,");
  printnum(n);
  print("): ");
  printnum(res);
  print("\n");
  return(0);
}

int
Ack(int M, int N) {
  if (M == 0) return( N + 1 );
  if (N == 0) return( Ack(M - 1, 1) );
  return( Ack(M - 1, Ack(M, (N - 1))) );
}

