#include "../../lib/quantum_emulator.h"

int main() {

  printf("%lu : char\n", sizeof(char));
  printf("%lu : int\n", sizeof(int));
  printf("%lu : unsigned int\n", sizeof(unsigned int));
  printf("%lu : long int\n", sizeof(long int));
  printf("%lu : unsigned long int\n", sizeof(unsigned long int));
  printf("%lu : float\n", sizeof(float));
  printf("%lu : double\n", sizeof(double));

  printf("%u : unsigned int (max)\n", ~(unsigned int)0);
  printf("%lu : unsigned long int (max)\n", ~(unsigned long int)0);
}
