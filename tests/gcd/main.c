#include "../../lib/utils.h"

int main() {

  int a, b;

  a = 0;
  b = 0;
  printf("%d %d %d\n", a, b, gcd(a,b) );

  a = 5;
  b = 0;
  printf("%d %d %d\n", a, b, gcd(a,b) );

  a = 0;
  b = 5;
  printf("%d %d %d\n", a, b, gcd(a,b) );

  a = 270;
  b = 192;
  printf("%d %d %d\n", a, b, gcd(a,b) );

  a = 270;
  b = 192;
  printf("%d %d %d\n", a, b, gcd(b,a) );




}
