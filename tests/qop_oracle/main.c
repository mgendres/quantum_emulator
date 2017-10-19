#include "../../lib/quantum_simulator.h"

/* This function is unknown, except throught the
action fof the quantum oracle */
int f(q_reg x) {
  if (x==5) return 1;
  return 0;
}

int main() {

  struct q_state z;

  z = qstate_create(3);
  qstate_pure(0,z);
  for (q_reg i=0; i< z.qubits; ++i) {
    qop_hadamard(i,z);
  }
  qstate_print(z);
  qop_oracle(f,z);
  qstate_print(z);
  qstate_destroy(z);

}
