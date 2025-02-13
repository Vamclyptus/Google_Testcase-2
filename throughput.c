#include <stdio.h>
#include <time.h>
//#include <sys/sysinfo.h>
//#include <stddef.h>


#define SAMPLE_RATE 48000  // Sample rate in Hz
#define BIT_DEPTH 16       // Bit depth (bits per sample)
#define CHANNELS 2         // Number of audio channels
#define DURATION 35         // Duration in seconds (test with 5 sec of audio)

void measure_throughput() {
    struct timespec start, end;
    
   
    
    // Calculate total data to be processed (uncompressed PCM)
    long total_bytes = (long) SAMPLE_RATE * BIT_DEPTH/8  * CHANNELS * DURATION;
    clock_gettime(CLOCK_MONOTONIC, &start);
    long seconds = end.tv_sec - start.tv_sec;
    for (volatile long i = 0; i < total_bytes; i++){printf("%d ",i);}
    clock_gettime(CLOCK_MONOTONIC, &end);
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    double elapsed_time = seconds - nanoseconds;
    double throughput = (total_bytes*1000000000) / elapsed_time;

    printf("Processed %ld bytes in %.6f nano seconds\n", total_bytes, elapsed_time);
    printf("Throughput: %.2f KB/sec\n", throughput / 1024 );
}

int main() {
    measure_throughput();
    return 0;
}
