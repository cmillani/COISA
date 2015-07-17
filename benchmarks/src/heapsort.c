/* -*- mode: c -*-
 * $Id: heapsort.gcc,v 1.10 2001/05/08 02:46:59 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */


#define IM 139968
#define IA   3877
#define IC  29573

unsigned int gen_random();
void heapsort(int n, unsigned int *ra);

//#define X86

#ifdef X86
#include <stdio.h>
void print(const char *str) {
  printf("%s", str);
}

void printnum(int n) {
  printf("%d", n);
}
#else
#include "stdthing.h"
#endif

int
main(int argc, char *argv[]) {
  int N = 20;
  unsigned int ary[21];
  int i;
    
  for (i=1; i<=N; i++) {
    ary[i] = gen_random();
  }

  heapsort(N, ary);

  printnum(ary[N]);
  print("\n");

  return(0);
}

unsigned int
gen_random() {
  static unsigned int last = 42;
  return( last = (last * IA + IC) % IM  );
}

void
heapsort(int n, unsigned int *ra) {
  int i, j;
  int ir = n;
  int l = (n >> 1) + 1;
  unsigned int rra;

  for (;;) {
    if (l > 1) {
      rra = ra[--l];
    } else {
      rra = ra[ir];
      ra[ir] = ra[1];
      if (--ir == 1) {
        ra[1] = rra;
        return;
      }
    }
    i = l;
    j = l << 1;
    while (j <= ir) {
      if (j < ir && ra[j] < ra[j+1]) { ++j; }
      if (rra < ra[j]) {
        ra[i] = ra[j];
        j += (i = j);
      } else {
        j = ir + 1;
      }
    }
    ra[i] = rra;
  }
}

