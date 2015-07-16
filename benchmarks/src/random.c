/* -*- mode: c -*-
 * $Id: random.gcc,v 1.14 2001/05/08 01:36:50 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */


#define IM 139968
#define IA 3877
#define IC 29573

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

unsigned int gen_random();

int main(int argc, char *argv[]) {
  int N = 1;
  long long result = 0;
    
  while (N--) {
    result = gen_random();
  }
  printnum(result);
  print("\n");
  return(0);
}

unsigned int gen_random() {
  static unsigned int last = 42;
  printnum(last);
  print("\n");
  last = last * IA;
  printnum(last);
  print("\n");
  last = last + IC;
  printnum(last);
  print("\n");
  last = last % IM;
  printnum(last);
  print("\n");
  return last;
}
