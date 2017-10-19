#include "../../lib/quantum_simulator.h"

int main() {

  struct q_state z;

  z = qstate_create(0);
  printf("Created an %u qubit q_state of length %u.\n", z.qubits, z.length);
  qstate_destroy(z);

  z = qstate_create(1);
  printf("Created an %u qubit q_state of length %u.\n", z.qubits, z.length);
  qstate_destroy(z);

  z = qstate_create( 8*sizeof(q_reg) -1);
  printf("Created an %u qubit q_state of length %u.\n", z.qubits, z.length);
  qstate_destroy(z);

  z = qstate_create( 8*sizeof(q_reg) );
  printf("Created an %u qubit q_state of length %u.\n", z.qubits, z.length);
  qstate_destroy(z);



}
