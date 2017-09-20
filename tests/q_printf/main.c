#include "../../lib/quantum_emulator.h"

int main() {

  for (unsigned int i=0; i<N_RANGE; ++i) {
    printf("%u : ", i);
    q_printf(i);
  }

}
