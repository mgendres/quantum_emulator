#include "../../lib/quantum_emulator.h"

int main() {

  //srand(time(NULL));

  struct q_state z = qstate_create(3);
 
  qstate_random(z);
  qstate_print(z);
  printf("norm = %f\n", qstate_norm(z) );

  qop_qft(z);
  qstate_print(z);
  printf("norm = %f\n", qstate_norm(z) );

  qstate_destroy(z);

}
