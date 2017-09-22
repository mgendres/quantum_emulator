#ifndef QUANTUM_EMULATOR_H 
#define QUANTUM_EMULATOR_H

#include <stdio.h>
#include <complex.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned int q_reg;

//#define N_QBITS 3
//#define N_RANGE (1<<N_QBITS)

#define PI 3.14159265359

struct q_state {
  double complex *comp;
  q_reg qubits; // The number of qubits used to represent the state
  q_reg length; // The number of comples numbers needed to represent the state = 2^qubits
};

struct q_state qstate_create(q_reg);

void qstate_destroy(struct q_state);

void q_printf(q_reg);

double rng_uniform();

double qstate_norm(struct q_state);

void qstate_normalize(struct q_state);

double complex qstate_inner(struct q_state, struct q_state);

void qstate_random(struct q_state);

void qstate_print(struct q_state);

void qstate_pure(q_reg, struct q_state);

void qop_hadamard(q_reg, struct q_state);

void qop_cxor(q_reg, q_reg, struct q_state);

void qop_swap(q_reg, q_reg, struct q_state);

void qop_rotation(q_reg, q_reg, q_reg, struct q_state);

void qop_qft(struct q_state);
 

#endif /* QUANTUM_EMULATOR_H */
