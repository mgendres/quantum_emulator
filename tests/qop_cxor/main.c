#include "../../lib/quantum_emulator.h"

int main() {

  srand(time(NULL));

  unsigned int qubits = 3;
  struct q_state z = qstate_create(qubits);
  struct q_state w = qstate_create(qubits);

  double complex inner;
  
  for (unsigned int c=0; c<qubits; ++c) {
    for (unsigned int t=0; t<qubits; ++t) {
      if (c!=t) {
        printf("cxor (ctrl=%u, targ=%u):\n", c, t);
        for (unsigned int i=0; i<z.length; ++i) {
          qstate_pure(i,z);
          for (unsigned int j=0; j<w.length; ++j) {
            qstate_pure(j,w);
            qop_cxor(c, t, w);
            inner = qstate_inner(z,w);
            printf("%f ", creal(inner));
          }
          printf("\n");
        }
        printf("\n");
      }
    }
  }

  qstate_destroy(z);
  qstate_destroy(w);

}
