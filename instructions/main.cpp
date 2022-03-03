#include "../measure/measure.h"

#include <stdio.h>
#include <string.h>

#define S 20000
#define N 50000

int main(int argc, char *argv[]) {

  // if (argc != 2) {
  //   printf("usage: %s [imul|add|nop]\n", argv[0]);
  //   return -1;
  // }

  // init the measurement library
  init();

  // measure imul
  if (strcmp(argv[1], "imul") == 0) {
    for (int s = 0; s < S; ++s) {
      volatile uint64_t prod = 3;
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("imul $0x55, %0":"=r"(prod):"r"(prod));
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  } 
  // measure add
  else if (strcmp(argv[1], "add") == 0) {
    for (int s = 0; s < S; ++s) {
      volatile uint64_t sum = 0;
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("add $0x55, %0":"=r"(sum):"r"(sum));
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure nop
  else if (strcmp(argv[1], "nop") == 0) {
    for (int s = 0; s < S; ++s) {
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("nop");
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure clflush
  else if (strcmp(argv[1], "clflush") == 0) {
    char target_array[256];
    for (int s = 0; s < S; ++s) {
      // target_array[0] = 'a'; // access some element to bring in cache
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("clflush 0(%0)"::"r"(&target_array[0]));
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure inc
  else if (strcmp(argv[1], "inc") == 0) {
    for (int s = 0; s < S; ++s) {
      volatile uint64_t sum = 0;
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("inc %0":"=r"(sum):"r"(sum));
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure xor
  else if (strcmp(argv[1], "xor") == 0) {
    for (int s = 0; s < S; ++s) {
      volatile uint64_t xorr = 0;
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("xor $0x55, %0":"=r"(xorr):"r"(xorr));
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure mov
  else if (strcmp(argv[1], "mov") == 0) {
    for (int s = 0; s < S; ++s) {
      volatile uint64_t movv = 0;
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("mov $0x55, %0":"=r"(movv):"r"(movv));
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure fscale
  else if (strcmp(argv[1], "fscale") == 0) {
    for (int s = 0; s < S; ++s) {
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("fscale");
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure rdrand
  else if (strcmp(argv[1], "rdrand") == 0) {
    for (int s = 0; s < S; ++s) {
      volatile uint64_t sum = 0;
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("rdrand %0":"=r"(sum):"r"(sum));
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  // measure rdtsc
  else if (strcmp(argv[1], "rdtsc") == 0) {
    for (int s = 0; s < S; ++s) {
      Measurement start = measure();
      for (int i = 0; i < N; ++i) {
        asm volatile("rdtsc");
      }
      Measurement stop = measure();
      Sample sample = convert(start, stop);
      fprintf(stderr, "%f\n", sample.energy);
    }
  }
  return 0;
}