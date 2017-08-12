/*
Write a program using gettimeofday which measures the runtime of the following functions accurately:
    
    sqrt(), pow(), qsort()

using an array of lengths 1M, 10M and 100M containing random integers
Some of these functions execute in nanoseconds so it might be necessary to report average runtime 
over many measurements. Run your program multiple times and compare the results.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <sys/time.h>

#define EPS 1E-8
#define ONEMILL_LEN 1000000
#define TENMILL_LEN 10000000
#define HUNMILL_LEN 100000000
#define INPUT_MAX_VALUE 1000
#define POW_START 1
#define POW_END 10

int mycmp(const void *fst, const void *snd);
double* getRandArray(int numItems);
void seconds_sqrt(double* array, int numElements);
void seconds_pow(double* array, int numElements, int exponent);
void seconds_qsort(double* array, int numElements);
void runTimeTest(int len);

int main(int argv, char *argc[]) {

    // test 1M items
    runTimeTest(ONEMILL_LEN);

    // test 10M items
    runTimeTest(TENMILL_LEN);

    // test 100M items
    runTimeTest(HUNMILL_LEN);

    return 0;
}

void runTimeTest(int len) {

    double * array = getRandArray(len);

    printf("\nTesting %d item array:\n", len);

    seconds_sqrt(array, len);

    int i=POW_START;
    for (i=POW_START; i<=POW_END; i++){
        seconds_pow(array, len, i);
    }

    seconds_qsort(array, len);
} 

double* getRandArray(int numItems) {
    
    double * array = (double*)malloc(numItems*sizeof(double));
    assert(array != NULL);

    int i=0;
    for (i=0; i<numItems; i++) {
        array[i] = rand() % (INPUT_MAX_VALUE+1);
    }

    return array;
}

void seconds_sqrt(double* array, int numElements) {
    struct timeval start;
    struct timeval stop;
    gettimeofday(&start, NULL);
    
    int i=0;
    for (i=0; i<numElements; i++) {
        sqrt(array[i]);
    }

    gettimeofday(&stop, NULL);
    double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
    elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;

    double t = elapsed_ms/1000;
    printf("sqrt time: %.4fsec tot, %.8fmsec avg\n", t, elapsed_ms/numElements);
}


void seconds_pow(double* array, int numElements, int exponent) {
    struct timeval start;
    struct timeval stop;
    gettimeofday(&start, NULL);
    
    int i=0;
    for (i=0; i<numElements; i++) {
        pow(array[i], exponent);
    }

    gettimeofday(&stop, NULL);
    double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
    elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;

    double t = elapsed_ms/1000;
    printf("pow(%d) time:  %.4fsec tot, %.8fmsec avg\n", exponent, t, elapsed_ms/numElements);

}


void seconds_qsort(double* array, int numElements) {
    struct timeval start;
    struct timeval stop;
    gettimeofday(&start, NULL);
    
    qsort(array, numElements, sizeof(double), &mycmp);

    gettimeofday(&stop, NULL);
    double elapsed_ms = (stop.tv_sec - start.tv_sec) * 1000.0;
    elapsed_ms += (stop.tv_usec - start.tv_usec) / 1000.0;
    
    double t = elapsed_ms/1000;
    printf("qsort time: %.4fsec tot\n", t, t/numElements);

}

int mycmp(const void *fst, const void *snd) {
    
    assert(fst!=NULL && snd!=NULL);
    double a = *((double*)fst);
    double b = *((double*)snd);

    if ((b-a)<EPS && (a-b)<EPS) {
        return 0;
    } else if (a<b) {
        return -1;
    }
    return 1;  
}

