#include "../measure/measure.h"
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <immintrin.h>

#define S 200000
#define n 1
#define N n*n

using namespace std;

char array1[N];


int main() {

    init();

    for (int i = 0; i < N; i++) {
        array1[i] = i % 128 + (i >> 8) % 128;
    }

    char some_res = 0;

    vector<int> v;
    for (int i = 0; i < N; i++) {
        v.push_back(i);
    }

    random_shuffle(v.begin(), v.end());    

    for (int i = 0; i < S; i++) {
        for (int i = 0; i < N; i++) {
            int idx = v[i];
            int x = 0;
            _mm_clflush(&array1[idx]);

            Measurement start = measure();
            x = array1[idx];
            Measurement stop = measure();
            idx = N - idx;
            some_res ^= x;
            Sample sample = convert(start, stop);
            fprintf(stderr, "%f\n", sample.energy);

            idx = N - idx;

            start = measure();
            x = array1[idx];
            stop = measure();
            some_res += x;
            sample = convert(start, stop);
            fprintf(stderr, "%f\n", sample.energy);
        }
    }
}
