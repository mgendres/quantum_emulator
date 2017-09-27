#include "../../lib/quantum_emulator.h"

int main() {

  srand(time(NULL));

  unsigned int qubits = 1;
  struct q_state z = qstate_create(qubits);
  struct q_state w = qstate_create(qubits);

  double complex inner;
  
  printf("X:\n");
  for (unsigned int i=0; i<z.length; ++i) {
    qstate_pure(i,z);
    for (unsigned int j=0; j<w.length; ++j) {
      qstate_pure(j,w);
      qop_x(0, w);
      inner = qstate_inner(z,w);
      printf("(%f,%f)", creal(inner), cimag(inner));
    }
    printf("\n");
  }
  printf("\n");

  printf("Y:\n");
  for (unsigned int i=0; i<z.length; ++i) {
    qstate_pure(i,z);
    for (unsigned int j=0; j<w.length; ++j) {
      qstate_pure(j,w);
      qop_y(0, w);
      inner = qstate_inner(z,w);
      printf("(%f,%f)", creal(inner), cimag(inner));
    }
    printf("\n");
  }
  printf("\n");

  printf("Z:\n");
  for (unsigned int i=0; i<z.length; ++i) {
    qstate_pure(i,z);
    for (unsigned int j=0; j<w.length; ++j) {
      qstate_pure(j,w);
      qop_z(0, w);
      inner = qstate_inner(z,w);
      printf("(%f,%f)", creal(inner), cimag(inner));
    }
    printf("\n");
  }
  printf("\n");


  printf("S:\n");
  for (unsigned int i=0; i<z.length; ++i) {
    qstate_pure(i,z);
    for (unsigned int j=0; j<w.length; ++j) {
      qstate_pure(j,w);
      qop_s(0, w);
      inner = qstate_inner(z,w);
      printf("(%f,%f)", creal(inner), cimag(inner));
    }
    printf("\n");
  }
  printf("\n");

  qstate_destroy(z);
  qstate_destroy(w);

}
