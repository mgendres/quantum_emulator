#include "../../lib/quantum_emulator.h"

int main() {
  q_reg max = ~0;
  printf("q_reg max is : %u\n", max);

  for (q_reg i=0; i<10; ++i) {
    printf("%u : ", i);
    q_printf(i);
  }

  for (q_reg i=max-10; i<max; ++i) {
    printf("%u : ", i);
    q_printf(i);
  }

  printf("Interestingly the for loop can only up to but not including max.\n");
  printf("Replacing condition < with <= renders the loop infinite.\n");
  printf("My guess is that \"<= max\" is converted to \"< max+1 (=0)\" at compile time.\n");

}
