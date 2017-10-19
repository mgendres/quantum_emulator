#include "../../lib/quantum_simulator.h"

int main() {

  srand(time(NULL));

  struct q_state z = qstate_create(3);

  qstate_random(z);
  qstate_print(z);

  struct q_state w = qstate_clone(z);
  qstate_print(w);

  qstate_destroy(w);
  qstate_destroy(z);

}
