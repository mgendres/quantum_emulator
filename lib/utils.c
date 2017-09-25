#include "utils.h"

int gcd(int a, int b) {
  if (a==0) return b;
  if (b==0) return a;
  int c;
  do {
    c = a % b;
    a = b;
    b = c;
  } while (b > 0);
  return a;
}

unsigned int is_prime(unsigned int n) {
  if (n<=1) return 0;
  if (n<=3) return 1;
  if (n%2==0) return 0;
  if (n%3==0) return 0;
  for (int i=5; i*i<=n; i+=6) {
    if (n%i==0) return 0;
    if (n%(i+2)==0) return 0;
  }
  return 1;
}

