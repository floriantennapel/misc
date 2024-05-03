#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  unsigned _1: 1;
  unsigned _2: 1;
  unsigned _3: 1;
  unsigned _4: 1;
  unsigned _5: 1;
  unsigned _6: 1;
  unsigned _7: 1;
  unsigned _8: 1;
} bits;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Missing argument n\n");
    return EXIT_FAILURE;
  }

  long n = atol(argv[1]);
  long size = (n + 7) / 8;
  bits* sieve = calloc(size, sizeof(bits));

  for (long i = 2; i <= sqrt(n) + 1; i++) {
    long index = i / 8;
    char offset = i % 8;

    bits* bs = &sieve[index];
    char bit;
    switch (offset) {
      case 0: bit = bs->_1; break;
      case 1: bit = bs->_2; break;
      case 2: bit = bs->_3; break;
      case 3: bit = bs->_4; break;
      case 4: bit = bs->_5; break;
      case 5: bit = bs->_6; break;
      case 6: bit = bs->_7; break;
      case 7: bit = bs->_8; break;
    }

    if (bit) {
      continue;
    }

    for (long j = i * 2; j < n; j += i) {
      long j_ind = j / 8;
      char j_off = j % 8;

      bits* j_bs = &sieve[j_ind];
      switch (j_off) {
        case 0: j_bs->_1 = 1; break;
        case 1: j_bs->_2 = 1; break;
        case 2: j_bs->_3 = 1; break;
        case 3: j_bs->_4 = 1; break;
        case 4: j_bs->_5 = 1; break;
        case 5: j_bs->_6 = 1; break;
        case 6: j_bs->_7 = 1; break;
        case 7: j_bs->_8 = 1; break;
      }
    }
  }

  FILE* file = fopen("primes.txt", "w");
  if (!file) {
    perror("");
    return EXIT_FAILURE;
  }

  for (long i = 2; i < n; i++) {
    long index = i / 8;
    char offset = i % 8;

    bits* bs = &sieve[index];
    char bit;
    switch (offset) {
      case 0: bit = bs->_1; break;
      case 1: bit = bs->_2; break;
      case 2: bit = bs->_3; break;
      case 3: bit = bs->_4; break;
      case 4: bit = bs->_5; break;
      case 5: bit = bs->_6; break;
      case 6: bit = bs->_7; break;
      case 7: bit = bs->_8; break;
    }

    if (!bit) {
      fprintf(file, "%ld ", i);
    }
  }

  free(sieve);
  fclose(file);

  return EXIT_SUCCESS;
}
