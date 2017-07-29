/* For this exercise you must read in a matrix and ouput the maximum and 
   minimum values from each column. Use dynamic memory allocation to store
   the matrix in memory and fill in steps 2-5 below
   
   Chitrarth Lav, 27 July 2017 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void* safe_malloc(size_t bytes)
{
    void* ptr = malloc(bytes);
    if (ptr == NULL) {
        printf("error mallocing %lu bytes\n", bytes);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

int main(int argc, char const* argv[])
{
    uint32_t n, m;
    // (1) read dimensions
    // n == number of rows
    // m == number of cols
    if (scanf("n = %u\n", &n) != 1) {
        printf("error reading n dimension.\n");
        exit(EXIT_FAILURE);
    }
    if (scanf("m = %u\n", &m) != 1) {
        printf("error reading m dimension.\n");
        exit(EXIT_FAILURE);
    }

    // (2) allocate memory


    // (3) read the data

    // (4) compute stats

    // (5) cleanup
 

    return EXIT_SUCCESS;
}
