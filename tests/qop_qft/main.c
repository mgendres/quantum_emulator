#include "../../lib/quantum_emulator.h"

int main() {

  //srand(time(NULL));

  double complex z[N_RANGE];
 
  qstate_random(z);
  printf("norm = %f\n", qstate_norm(z) );
  qstate_print(z);

  qop_qft(z);
  qstate_print(z);
  printf("norm = %f\n", qstate_norm(z) );

}
