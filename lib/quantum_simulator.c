#include "quantum_simulator.h"
#include "utils.h"

/*
  Note to self: be better about naming conventions.
  Want to make sure classical and quantum functions are indicated
  as such...
*/

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

/* Return a cloned known q_state */
struct q_state qstate_clone(struct q_state z) {
  struct q_state w;
  w.qubits = z.qubits;
  w.length = z.length;
  w.comp = (complex double *) malloc(w.length * sizeof(complex double));
  for (q_reg i=0; i<w.length; ++i) {
    w.comp[i] = z.comp[i];
  }
  return w; 
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

double qstate_min(struct q_state z) {
  double min = cabs(z.comp[0]);
  double prop;
  for (q_reg n=1; n<z.length; ++n) {
    prop = cabs(z.comp[n]);
    if (min > prop) min=prop;
  }
  return min;
}

double qstate_max(struct q_state z) {
  double max = cabs(z.comp[0]);
  double prop;
  for (q_reg n=1; n<z.length; ++n) {
    prop = cabs(z.comp[n]);
    if (max < prop) max=prop;
  }
  return max;
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

/*
This function performs a measurements on a given q_state
It returns a pure q_state (represented by a q_reg) with
appropriate probability. This can probably be implemented in 
a more efficient way, but this gets the job done.
*/
q_reg qstate_measure(struct q_state z) {
  double p;
  for (q_reg i=0; i<z.length-1; ++i) {
    p = z.comp[i]*conj(z.comp[i]);
    if (p>rng_uniform()) { return i; }
    p = sqrt(1.0-p);
    /* Renormalize */
    for (q_reg j=i+1; j<z.length; ++j) {
      z.comp[j] /= p;
    }
  }
  return z.length-1;
}

// Perform hadamard operation on q-bit i
void qop_hadamard(q_reg i, struct q_state z) {
  q_reg targ = (1<<i);
  double complex tmp;
  for (q_reg j=0; j<z.length; ++j) {
    if (j & targ) {
      tmp = z.comp[j^targ];
      z.comp[j^targ] += z.comp[j];
      z.comp[j^targ] /= sqrt(2.0);
      z.comp[j] *= -1.0;
      z.comp[j] += tmp;
      z.comp[j] /= sqrt(2.0);
    }
  }
}

void qop_x(q_reg i, struct q_state z) {
  q_reg targ = (1<<i);
  double complex tmp;
  for (q_reg j=0; j<z.length; ++j) {
    if (j & targ) {
       tmp = z.comp[j];
       z.comp[j] = z.comp[j^targ];
       z.comp[j^targ] = tmp;
    }
  }
}

void qop_y(q_reg i, struct q_state z) {
  q_reg targ = (1<<i);
  double complex tmp;
  for (q_reg j=0; j<z.length; ++j) {
    if (j & targ) {
       tmp = z.comp[j];
       z.comp[j] = I*z.comp[j^targ];
       z.comp[j^targ] = (-1)*I*tmp;
    }
  }
}

void qop_z(q_reg i, struct q_state z) {
  q_reg targ = (1<<i);
  for (q_reg j=0; j<z.length; ++j) {
    if (j & targ) {
       z.comp[j] = (-1)*z.comp[j];
    }
  }
}

void qop_s(q_reg i, struct q_state z) {
  q_reg targ = (1<<i);
  for (q_reg j=0; j<z.length; ++j) {
    if (j & targ) {
       z.comp[j] = I*z.comp[j];
    }
  }
}

// Perform CNOT operation, treating the i-th qubit as the control bit
// and j-th qubit as the target bit
void qop_cnot(q_reg i, q_reg j, struct q_state z) {
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
  qop_cnot(i,j,z);
  qop_cnot(j,i,z);
  qop_cnot(i,j,z);
}

// Controlled rotation gate operation R_\theta
// treating the i-th qubit as the control bit
// and the jth bit as the target bit
void qop_rotation(q_reg i, q_reg j, double theta, struct q_state z) {
  q_reg ctrl = (1<<i);
  q_reg targ = (1<<j);
  double complex w = cexp(theta*I);
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
  double phase;
  for (q_reg i=z.qubits; i>0; --i) {
    qop_hadamard(i-1, z);
    k=2;
    for (q_reg j=i-1; j>0; --j) {
      phase = -sgn*2.0*PI;
      phase /= (1<<k);
      qop_rotation(j-1, i-1, phase, z);
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
// where f(x) \in {0,1}
// Note (-1)^f(x) = 1-2*f(x)
void qop_oracle(int (* func)(q_reg), struct q_state z) {
  for (q_reg i=0; i<z.length; ++i) {
    z.comp[i] *= (1.0-2.0*func(i));
  }
}

// Grover's diffusion operator;
// should reimpement in terms of quantum gates if we
// are to claim this is quantum emulation?
void qop_diffusion(struct q_state z) {
  complex double mu=0.0;
  for (q_reg i=0; i<z.length; ++i) {
    mu += z.comp[i];
  }
  mu /= z.length;
  mu *= 2.0;
  for (q_reg i=0; i<z.length; ++i) {
    z.comp[i] *= -1;
    z.comp[i] += mu;
  }
}

// Grover's algorithm
// Note, this implementation appears to be slightly unstable
// if n_iter > \sqrt(z.length)... fortunately one need not
// perform more than around that many iterations
void qop_grover(int (* func)(q_reg), struct q_state z, q_reg n_iter) {
  qstate_pure(0,z);
  for (q_reg i=0; i< z.qubits; ++i) {
    qop_hadamard(i,z);
  }
  printf("i = -1 min = %f max = %f\n", qstate_min(z), qstate_max(z));
  for (q_reg i=0; i<n_iter; ++i) {
    qop_oracle(func,z);
    qop_diffusion(z);
    printf("i = %u min = %f max = %f\n", i, qstate_min(z), qstate_max(z));
  }
}

unsigned int qop_shor(q_reg n) {
  if (n%2==0) return 2;
  q_reg a = n*rng_uniform();
  do{
    a = n*rng_uniform();
  } while (a==0);
  q_reg b = gcd(a, n);
  if(b!=1) return b;
  // Perid findin, etc...
  return 0;
}

