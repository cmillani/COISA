/* -*- mode: c -*-
 * $Id: ary3.gcc,v 1.1 2001/05/31 02:27:48 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 *
 * this program is modified from:
 *   http://cm.bell-labs.com/cm/cs/who/bwk/interps/pap.html
 * Timing Trials, or, the Trials of Timing: Experiments with Scripting
 * and User-Interface Languages</a> by Brian W. Kernighan and
 * Christopher J. Van Wyk.
 *
 * I added free() to deallocate memory.
 */



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
void *memset(void *s, int c, unsigned int n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}
#endif

int
main(int argc, char *argv[]) {
  int n = 250;
  int i, k, x[250], y[250];

  // emulando calloc
  for (i = 0; i < n; ++i) {
    x[i] = 0;
    y[i] = 0;
  }

  for (i = 0; i < n; i++) {
    x[i] = i + 1;
  }
  for (k=0; k<1000; k++) {
//    for (i = n-1; i >= 0; i--) {
    for (i = 0; i < n; i++) {
      y[i] += x[i];
    }
  }

  printnum(y[0]);
  print(" ");
  printnum(y[n-1]);
  print("\n");

  return(0);
}
