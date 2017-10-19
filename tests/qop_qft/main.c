#include "../../lib/quantum_simulator.h"

int main() {

  //srand(time(NULL));

  struct q_state z = qstate_create(8);
 
  qstate_random(z);
  qstate_print(z);
  printf("norm = %f\n", qstate_norm(z) );

  qop_qft(z, 1);
  qstate_print(z);
  qop_qft(z, -1);
  qstate_print(z);
  printf("norm = %f\n", qstate_norm(z) );

  qstate_destroy(z);

}
