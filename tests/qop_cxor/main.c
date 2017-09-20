#include "../../lib/quantum_emulator.h"

int main() {

  srand(time(NULL));

  double complex z[N_RANGE];
  double complex w[N_RANGE];

  double complex inner;
  
  for (unsigned int c=0; c<N_QBITS; ++c) {
    for (unsigned int t=0; t<N_QBITS; ++t) {
      if (c!=t) {
        printf("cxor (ctrl=%u, targ=%u):\n", c, t);
        for (unsigned int i=0; i<N_RANGE; ++i) {
          qstate_pure(i,z);
          for (unsigned int j=0; j<N_RANGE; ++j) {
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


}
