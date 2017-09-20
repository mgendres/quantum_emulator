#include "quantum_emulator.h"

void q_printf(unsigned int n) {
  unsigned int mask = 1;
  for (unsigned int i=0; i<N_QBITS; ++i) {
    printf("%u", mask==(mask & n));
    mask = mask << 1;
  }
  printf("\n");
}

double rng_uniform() {
  // Generate a random number in [0,1]
  // Note that this generator should only be used for
  // testing purposes (due to its potentially poor quality)
  return rand()/ (double)RAND_MAX;
}

// Given a complex vector z, return its norm sqrt(<z|z>)
double qstate_norm(double complex *z) {
  return sqrt(creal(qstate_inner(z,z)));
}

// Given complex vectors z, and w, return the inner product <z|w>
double complex qstate_inner(double complex *z, double complex *w) {
  double complex inner = 0;
  for (unsigned int i=0; i<N_RANGE; ++i) {
    inner += conj(z[i])*w[i];
  }
  return inner;
}

void qstate_random(double complex *z) {
  // Initialize a random vector z
  for (unsigned int i=0; i<N_RANGE; ++i) {
    z[i]  = 2*rng_uniform()-1;
    z[i] += I*(2*rng_uniform()-1);  
  }
  double norm = qstate_norm(z);
  for (unsigned int i=0; i<N_RANGE; ++i) {
    z[i] /= norm;
  }
}

// Return a pure state z
void qstate_pure(unsigned int i, double complex *z) {
  for (unsigned int j=0; j<N_RANGE; ++j) {
    z[j]  = 0.0;
  }
  z[i] = 1.0;
}

void qstate_print(double complex *z) {
  // Print out the vector z for all to see.
  for (unsigned int i=0; i<N_RANGE; ++i) {
    printf("%u : (%f)+I*(%f)\n", i, creal(z[i]), cimag(z[i]));
  }
}

void qop_hadamard(unsigned int i, double complex *z) {
  // Perform hadamard operation on q-bit i
  unsigned int targ = (1<<i);
  double complex tmp;
  for (unsigned int j=0; j<N_RANGE; ++j) {
    if (j & targ) { // Avoid double operations
      tmp = z[j^targ];
      z[j^targ] += z[j];
      z[j^targ] /= sqrt(2.0);
      z[j] *= -1.0;
      z[j] += tmp;
      z[j] /= sqrt(2.0);
    }
  }
}


void qop_cxor(unsigned int i, unsigned int j, double complex *z) {
  // Perform CXOR operation, treating the i-th qubit as the control bit
  // and j-th qubit as the target bit
  unsigned int ctrl = (1<<i);
  unsigned int targ = (1<<j);
  double complex tmp;
  for (unsigned int k=0; k<N_RANGE; ++k) {
    if (k & ctrl) { // Check control
      if (k & targ) { // Avoid double swap
        tmp = z[k];
        z[k] = z[k^targ];
        z[k^targ] = tmp;
      }
    }
  }
}

void qop_swap(unsigned int i, unsigned int j, double complex *z) {
  qop_cxor(i,j,z);
  qop_cxor(j,i,z);
  qop_cxor(i,j,z);
}


void qop_rotation(unsigned int i, unsigned int j, unsigned int k, double complex *z) {
  // Perform rotation gate operation R_k
  // treating the i-th qubit as the control bit
  // and the jth bit as the target bit
  unsigned int ctrl = (1<<i);
  unsigned int targ = (1<<j);
  double complex w = cexp(-2.0*PI*I/(1<<k));
  //printf("%f %f\n",creal(w), cimag(w));
  for (unsigned int l=0; l<N_RANGE; ++l) {
    if (l & ctrl) { // Check control
      if (l & targ) {
        z[l] *= w;
      }
    }
  }
}

// An implementation of the quantum Fourier transform
void qop_qft(double complex *z) {
  unsigned int k;
  for (unsigned int i=N_QBITS; i>0; --i) {
    qop_hadamard(i-1, z);
    //printf("H: targ=%u\n", i-1);
    k=2;
    for (unsigned int j=i-1; j>0; --j) {
      qop_rotation(j-1, i-1, k, z);
      //printf("R ctrl=%u targ=%u angl=%u\n", i-1, j-1, k);
      k++;
    }
  }
  // Bit reversal using swap gates
  for (unsigned int i=0; i<N_QBITS/2; ++i) {
    qop_swap(i,N_QBITS-i-1,z);
  }
}
