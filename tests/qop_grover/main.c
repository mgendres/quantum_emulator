#include "../../lib/quantum_simulator.h"

#define bits 5

/* This function is unknown, except throught the
action fof the quantum oracle */
int f(q_reg x) {
  if (x==(1<<bits)-1) return 1;
  return 0;
}

int main() {

  srand(time(NULL));
  struct q_state z = qstate_create(bits);
  double n_iter = PI/4.0;
  n_iter *= sqrt(z.length);
  qop_grover(f,z, (int) n_iter);
  qstate_print(z);
  printf("measured state: %u\n", qstate_measure(z));
  qstate_destroy(z);

}
