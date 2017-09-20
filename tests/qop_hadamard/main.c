#include "../../lib/quantum_emulator.h"

int main() {

  srand(time(NULL));

  double complex z[N_RANGE];
  double complex w[N_RANGE];

  for (unsigned int k=0; k<N_QBITS; ++k) {
    printf("hadamard %u\n",k);
    double complex inner;
    for (unsigned int i=0; i<N_RANGE; ++i) {
      qstate_pure(i,z);
      for (unsigned int j=0; j<N_RANGE; ++j) {
        qstate_pure(j,w);
        qop_hadamard(k, w);
        inner = qstate_inner(z,w);
        printf("%f ", creal(inner));
      }
      printf("\n");
    }
    printf("\n");
  }
}
