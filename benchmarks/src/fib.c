int fib(int n);

// #define X86

#ifdef X86
#include <stdio.h>
#include <stdlib.h>
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
main() {
  int d= fib(12);
  print("fib(12) = ");
  printnum(d);
  print("\n");
}

int
fib(int n) {
  if (n == 1 || n == 2)
    return 1;
  return fib(n-1) + fib(n-2);
}


