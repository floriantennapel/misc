#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CHECK(bit, offset) ((bit) & (1 << (offset)))
#define SET(bitPtr, offset) (*(bitPtr) |= (1 << (offset)))

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Missing argument n\n");
    return EXIT_FAILURE;
  }

  long n = atol(argv[1]);
  long size = n / 8 + 1;
  char* sieve = calloc(size, 1);

  if (!sieve) {
    perror("");
    return EXIT_FAILURE;
  }

  long final = sqrt(n) + 1;

  for (long i = 2; i <= final; i++) {
    long index = i / 8;
    char offset = i % 8;
    if (CHECK(sieve[index], offset)) {
      continue;
    }

    for (long j = i * 2; j < n; j += i) {
      long j_ind = j / 8;
      char j_off = j % 8;

      SET(&sieve[j_ind], j_off);
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

    if (!CHECK(sieve[index], offset)) {
      fprintf(file, "%ld ", i);
    }
  }

  free(sieve);
  fclose(file);

  return EXIT_SUCCESS;
}
