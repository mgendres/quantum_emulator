#ifndef QUANTUM_EMULATOR_H 
#define QUANTUM_EMULATOR_H


#include <stdio.h>
#include <complex.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define N_QBITS 3
#define N_RANGE (1<<N_QBITS)

#define PI 3.14159265359

void q_printf(unsigned int);

double rng_uniform();


double qstate_norm(double complex *);

double complex qstate_inner(double complex *, double complex *);

void qstate_random(double complex *);

void qstate_print(double complex *);

void qstate_pure(unsigned int, double complex *);

void qop_hadamard(unsigned int, double complex *);

void qop_cxor(unsigned int, unsigned int, double complex *);

void qop_swap(unsigned int, unsigned int, double complex *);

void qop_rotation(unsigned int, unsigned int, unsigned int, double complex *);

void qop_reverse(double complex *);

void qop_qft(double complex *);


#endif /* QUANTUM_EMULATOR_H */
