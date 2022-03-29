#include "../measure/measure.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <immintrin.h>

#define S 2000
#define n 100000
#define N 4096*n

using namespace std;

unsigned char array1[N];


int main() {
    unsigned char junk;
    volatile uint8_t* addr;

    init();
    
    for (int i = 0; i < N; i++) array1[i] = 1;


    for (int s = 0; s < S; s++) {
        // for (int i = 0; i < n; i++) _mm_clflush(&array1[i*4096]);
        
        addr = &array1[0];

        Measurement start = measure();
        for (volatile int i = 0; i < n; i++) {
            _mm_clflush(&array1[i*4096]);
            // _mm_mfence();
            junk = array1[i*4096];
            // _mm_mfence();
        }
        Measurement stop = measure();
        Sample sample = convert(start, stop);

        printf("%f\n", sample.time);
        // start = measure();
        // for (volatile int i = 0; i < n; i++) {
        //     _mm_clflush(&array1[i*4096]);
        //     _mm_mfence();
        // }
        // for (volatile int i = 0; i < n; i++) {
        //     junk = array1[i*4096];
        //     _mm_mfence();
        // }
        // stop = measure();
        // sample = convert(start, stop);

        // printf("%f\n", sample.energy);
        // int x = addr[0];

        start = measure();
        for (volatile int i = 0; i < n; i++) {
            _mm_clflush(&array1[0]);
            // _mm_mfence();
            junk = array1[0];
            // _mm_mfence();
        }
        stop = measure();
        sample = convert(start, stop);

        printf("%f\n", sample.time);
        
    }
}

