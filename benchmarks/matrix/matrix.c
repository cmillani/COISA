/* -*- mode: c -*-
 * $Id: matrix.gcc,v 1.6 2001/03/31 15:52:48 doug Exp $
 * http://www.bagley.org/~doug/shootout/
 */

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
#include "stdthing.h"

void *memset(void *s, int c, int n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

#define SIZE 7


//#define X86

#ifdef X86
void print(const char *str) {
  printf("%s", str);
}

void printnum(int n) {
  printf("%d", n);
}
#endif
//// my malloc implementation
#define POOLMAX 768
char mypool[768];
int curptr = 0;

void *my_malloc(int size) {
  if (curptr + size > POOLMAX) {
    print("out of memory :-)\n");
    while(1);
  }
  void *res = &mypool[curptr];
  curptr += size;
  return res;
}
///// end


int **mkmatrix(int rows, int cols);
void zeromatrix(int rows, int cols, int **m);
//void freematrix(int rows, int **m);
int **mmult(int rows, int cols, int **m1, int **m2, int **m3);
void initialize(int **m1, int **m2);
void sum(int rows, int cols, int **m1, int **m2, int **m3);

int main(int argc, char *argv[]) {
  int i;
    
  int **m1 = mkmatrix(SIZE, SIZE);
  int **m2 = mkmatrix(SIZE, SIZE);
  initialize(m1, m2);
  int **mm = mkmatrix(SIZE, SIZE);

  mm = mmult(SIZE, SIZE, m1, m2, mm);
  sum(SIZE, SIZE, m1, m2, mm);

  printnum(mm[0][0]);
  print(" ");
  printnum(mm[2][3]);
  print(" ");
  printnum(mm[3][2]);
  print(" ");
  printnum(mm[4][4]);
  print("\n");

  //  freematrix(SIZE, m1);
  //  freematrix(SIZE, m2);
  //  freematrix(SIZE, mm);
  return(0);
}

void initialize(int **m1, int **m2) {
  int  i, j, cur = 0;
  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      m1[i][j] = cur++;
      if (cur > 10)
        cur = 0;
    }
  }
  for (i = SIZE - 1; i >= 0; --i) {
    for (j = SIZE - 1; j >= 0; --j) {
      m2[i][j] = cur++;
      if (cur > 10)
        cur = 0;
    }
  }
}

int **mkmatrix(int rows, int cols) {
  int i, j, count = 0;
  int **m = (int **) my_malloc(rows * sizeof(int *));
  for (i=0; i<rows; i++) {
    m[i] = (int *) my_malloc(cols * sizeof(int));
    for (j=0; j<cols; j++) {
      m[i][j] = count++;
    }
  }
  return(m);
}

void zeromatrix(int rows, int cols, int **m) {
  int i, j;
  for (i=0; i<rows; i++)
    for (j=0; j<cols; j++)
      m[i][j] = 0;
}

//void freematrix(int rows, int **m) {
//  while (--rows > -1) { free(m[rows]); }
//  free(m);
//}

void sum(int rows, int cols, int **m1, int **m2, int **m3) {
  int i, j;
  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      m3[i][j] = m1[i][j] + m2[i][j];
    }
  }
}

int **mmult(int rows, int cols, int **m1, int **m2, int **m3) {
  int i, j, k, val;
  for (i=0; i<rows; i++) {
    for (j=0; j<cols; j++) {
      val = 0;
      for (k=0; k<cols; k++) {
        val += m1[i][k] * m2[k][j];
      }
      m3[i][j] = val;
    }
  }
  return(m3);
}

