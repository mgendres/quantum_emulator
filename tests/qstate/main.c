#include "../../lib/quantum_emulator.h"

int main() {

  srand(time(NULL));

  double complex z[N_RANGE];
  qstate_random(z);
  qstate_print(z);
  printf("%f\n", qstate_norm(z));

  qstate_pure(0,z);
  qstate_print(z);
  printf("%f\n", qstate_norm(z));



}
