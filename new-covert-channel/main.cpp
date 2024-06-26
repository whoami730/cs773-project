#include "../measure/measure.h"

#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <time.h>
#include <signal.h>
#include <immintrin.h>

#define MAX 10000
#define S 2000
#define n 100000
#define N1 4096*n

unsigned char array1[N1];


timer_t gTimerid;
uint64_t writer = 0;

Measurement buffer[MAX];

void measurement_callback(int sig) {
  buffer[writer++] = measure();
}

void start_timer(void) {
  struct itimerspec value;

  uint64_t ns = 20*1000*1000llu;

  value.it_value.tv_sec = 0;
  value.it_value.tv_nsec = ns;

  value.it_interval.tv_sec = 0;
  value.it_interval.tv_nsec = ns;

  timer_settime(gTimerid, 0, &value, NULL);
}

void stop_timer(void) {
  struct itimerspec value;

  value.it_value.tv_sec = 0;
  value.it_value.tv_nsec = 0;

  value.it_interval.tv_sec = 0;
  value.it_interval.tv_nsec = 0;

  timer_settime(gTimerid, 0, &value, NULL);
}

// char key[] = {0,1,1,0,1};
char key[] = {0,1,1,0,1};

void balloon(double _n, unsigned char junk, uint64_t N){
  uint64_t until = get_timestamp() + seconds_2_timeticks(_n); 
  // while (get_timestamp() < until) {                           
  //   _x;                                                       
  // }

  for (volatile int i = 0; get_timestamp() < until; i++) {
      for (volatile int j = 0; j < N; ++j) {
      
        if(j >= n) j = 0;
        _mm_clflush(&array1[j*4096]);
        // _mm_mfence();
        junk = array1[j*4096];
        // _mm_mfence();
      }
  }
}

void idle(double _n,unsigned char junk, uint64_t N){
  uint64_t until = get_timestamp() + seconds_2_timeticks(_n);
  
  for (volatile int i = 0; get_timestamp() < until; i++) {
    
    for (volatile int j = 0; j < N; ++j) {
      // _mm_clflush(&array1[0]);
      // // _mm_mfence();
      // junk = array1[0];
      // // _mm_mfence();
      ;
    }
  }
}

#define N 20000

uint64_t XY[N];

void init_victim() {
 for (int i = 0; i < N1; i++) array1[i] = 1;
 for (int i = 0; i < N; ++i) {
    XY[i] = 1;
  }
}

void victim() {
  uint64_t factor = 0xdeadc0de;
  
  volatile uint8_t* addr;
  unsigned char junk;
  // this is a just a toy example!
  for (int j = 0; j < sizeof(key); ++j) {
    if (key[j]) {
      // DO_FOR_N_SECONDS(0.1, square_and_multiply(XY, factor, N));
      balloon(0.1,junk,N);
    } else {
      // try switching these lines to go from the covert channel to an RSA like sampling attack.
      //DO_FOR_N_SECONDS(0.1, square(XY, N));
      idle(0.1,junk,N);
  }
}
}

int main() {
  init();
  (void) signal(SIGALRM, measurement_callback);
  timer_create(CLOCK_REALTIME, NULL, &gTimerid);

  Sample sum[MAX];
  memset(sum, 0, sizeof(Sample)*MAX);
  
  for (int avg = 0; avg < 200; ++avg) {
    writer = 0;
    init_victim();
    start_timer();
    victim();
    stop_timer();
    for (uint64_t i = 0; i < writer-1; ++i) {
      add(sum[i], convert(buffer[i], buffer[i+1]));
    }
    printf("%d -> %lu\n", avg, writer-1);
  }

  printf("recorded %lu samples\n", writer);
  for (uint64_t i = 0; sum[i].count; ++i) {
    fprintf(stderr, "%f\n", sum[i].energy / sum[i].count / sum[i].time);
  }
}