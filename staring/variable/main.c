#include <stdio.h>

int main(void) {
  int a = 1;
  int b = a;
  int * c = &a;
  int d[1];
  d[0] = a;
  printf("a: %d\n", a);
  printf("b: %d\n", b);
  printf("c: %d\n", *c);
  printf("d: %d\n", d[0]);
  a = 2;
  printf("a: %d\n", a);
  printf("b: %d\n", b);  
  printf("c: %d\n", *c);
  printf("d: %d\n", d[0]);
  return 0;
}
