#include "../../lib/quantum_simulator.h"

int main() {

  srand(time(NULL));

  struct q_state z = qstate_create(3);
  qstate_random(z);
  qstate_print(z);

  struct q_state w = qstate_clone(z);

  unsigned int p[8];
  for (int i=0; i<8; ++i) { p[i]=0; }

  int n_meas = 1000000;
  for (int i=0; i<n_meas; ++i) {
    p[qstate_measure(z)] += 1;
    qstate_destroy(z);
    z = qstate_clone(w);
  } 

  for (int i=0; i<8; ++i) {
    printf("true: %f meas: %f\n", creal(z.comp[i]*conj(z.comp[i])),  p[i]/(double)n_meas);
  }
  printf("\n");

  qstate_destroy(w);
  qstate_destroy(z);

}
