#include "../../lib/quantum_emulator.h"

int main() {

  srand(time(NULL));

  struct q_state z = qstate_create(3);

  qstate_random(z);
  qstate_print(z);

  qstate_pure(0,z);
  qstate_print(z);

  qstate_pure(7,z);
  qstate_print(z);

  qstate_pure(8,z);
  qstate_print(z);

  qstate_destroy(z);

}
