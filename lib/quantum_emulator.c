#include "quantum_emulator.h"

int valid_qubit(q_reg i) {
  return (i < 8*sizeof(q_reg));
}

/* Helper function to create a q_state */
struct q_state qstate_create(q_reg n) {
  if ( !valid_qubit(n) ) {
    printf("Use fewer qubits or change the data type of q_reg to accomodate more qubits!\n");
    exit(0);
  }
  struct q_state z;
  z.qubits = n;
  z.length = (1<<n);
  z.comp = (complex double *) malloc(z.length * sizeof(complex double));
  return z;
}

/* Helper function to destroy a q_state */
void qstate_destroy(struct q_state z) {
  free(z.comp);
}

/* This just prints out some bits; not really used for anything. */
void q_printf(q_reg n) {
  q_reg mask = 1;
  for (q_reg i=0; i<8*sizeof(q_reg); ++i) {
    printf("%u", mask==(mask & n));
    mask = mask << 1;
  }
  printf("\n");
}

// Generate a random number in [0,1]
// WARNING: this generator should only be used for testing
// purposes (due to its potentially poor quality)
double rng_uniform() {
  return rand()/ (double)RAND_MAX;
}

// Given a q_state, return its norm
double qstate_norm(struct q_state z) {
  return sqrt(creal(qstate_inner(z,z)));
}

// Normalize a given q_state
void qstate_normalize(struct q_state z) {
  double norm = qstate_norm(z);
  for (q_reg n=0; n<z.length; ++n) {
    z.comp[n] /= norm;
  }
}

// Given q_states z, and w, return the inner product <z|w>
double complex qstate_inner(struct q_state z, struct q_state w) {
  if ( z.length != w.length ) {
    printf("Cannot compute inner product.\n");
    exit(0);
  }
  double complex inner = 0;
  for (q_reg n=0; n<z.length; ++n) {
    inner += conj(z.comp[n])*w.comp[n];
  }
  return inner;
}

void qstate_random(struct q_state z) {
  for (q_reg n=0; n<z.length; ++n) {
    z.comp[n]  = 2*rng_uniform()-1;
    z.comp[n] += I*(2*rng_uniform()-1);  
  }
  qstate_normalize(z);
}

// Initialize a pure q_state
void qstate_pure(q_reg n, struct q_state z) {
  if ( n >= z.length) {
    printf("Cannot initialize pure state.\n");
    exit(0);
  }
  for (q_reg i=0; i<z.length; ++i) {
    z.comp[i]  = 0.0;
  }
  z.comp[n] = 1.0;
}

void qstate_print(struct q_state z) {
  for (q_reg n=0; n<z.length; ++n) {
    //printf("%u : (%f)+I*(%f)\n", n, creal(z.comp[n]), cimag(z.comp[n]));
    printf("(%f)+I*(%f),\n", creal(z.comp[n]), cimag(z.comp[n]));
  }
  printf("qubits : %u\n", z.qubits);
  printf("length :%u\n", z.length);
  printf("norm : %f\n", qstate_norm(z));
}

// Perform hadamard operation on q-bit i
void qop_hadamard(q_reg i, struct q_state z) {
  q_reg targ = (1<<i);
  double complex tmp;
  for (q_reg j=0; j<z.length; ++j) {
    if (j & targ) { // Avoid double operations
      tmp = z.comp[j^targ];
      z.comp[j^targ] += z.comp[j];
      z.comp[j^targ] /= sqrt(2.0);
      z.comp[j] *= -1.0;
      z.comp[j] += tmp;
      z.comp[j] /= sqrt(2.0);
    }
  }
}


// Perform CXOR operation, treating the i-th qubit as the control bit
// and j-th qubit as the target bit
void qop_cxor(q_reg i, q_reg j, struct q_state z) {
  q_reg ctrl = (1<<i);
  q_reg targ = (1<<j);
  double complex tmp;
  for (q_reg k=0; k<z.length; ++k) {
    if (k & ctrl) { // Check control
      if (k & targ) { // Avoid double swap
        tmp = z.comp[k];
        z.comp[k] = z.comp[k^targ];
        z.comp[k^targ] = tmp;
      }
    }
  }
}

void qop_swap(q_reg i, q_reg j, struct q_state z) {
  qop_cxor(i,j,z);
  qop_cxor(j,i,z);
  qop_cxor(i,j,z);
}

// Controlled rotation gate operation R_k
// treating the i-th qubit as the control bit
// and the jth bit as the target bit
void qop_rotation(q_reg i, q_reg j, q_reg k, int sgn,  struct q_state z) {
  q_reg ctrl = (1<<i);
  q_reg targ = (1<<j);
  double phase = -sgn*2.0*PI;
  phase /= (1<<k);
  double complex w = cexp(phase*I);
  for (q_reg l=0; l<z.length; ++l) {
    if (l & ctrl) {
      if (l & targ) {
        z.comp[l] *= w;
      }
    }
  }
}

// An implementation of the quantum Fourier transform
void qop_qft(struct q_state z, int sgn) {
  q_reg k;
  for (q_reg i=z.qubits; i>0; --i) {
    qop_hadamard(i-1, z);
    k=2;
    for (q_reg j=i-1; j>0; --j) {
      qop_rotation(j-1, i-1, k, sgn, z);
      k++;
    }
  }
  // Bit reversal using swap gates
  // (a lookup table would be more efficient)
  for (q_reg i=0; i<z.qubits/2; ++i) {
    qop_swap(i,z.qubits-i-1,z);
  }
}

// Applies operator O == \sum_x (-1)^f(x) |x><x| to a state,
// where f(x) = +/- 1
void qop_oracle(int (* func)(q_reg), struct q_state z) {
  for (q_reg i=0; i<z.length; ++i) {
    z.comp[i] *= func(i);
  }
}

