#include "../../lib/quantum_simulator.h"

#define bits 5

int main() {

  srand(time(NULL));
  //printf("%u\n", qop_shor(38));
  for (int i=0; i<100; ++i) {
    qop_shor(15);
    //printf("%u\n", qop_shor(15));
  }
}
