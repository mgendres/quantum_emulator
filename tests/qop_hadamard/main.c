#include "../../lib/quantum_simulator.h"

int main() {

  srand(time(NULL));

  unsigned int qubits = 3;
  struct q_state z = qstate_create(qubits);
  struct q_state w = qstate_create(qubits);

  for (unsigned int k=0; k<qubits; ++k) {
    printf("hadamard %u\n",k);
    double complex inner;
    for (unsigned int i=0; i<z.length; ++i) {
      qstate_pure(i,z);
      for (unsigned int j=0; j<w.length; ++j) {
        qstate_pure(j,w);
        qop_hadamard(k, w);
        inner = qstate_inner(z,w);
        printf("%f ", creal(inner));
      }
      printf("\n");
    }
    printf("\n");
  }

  qstate_destroy(z);
  qstate_destroy(w);

}
