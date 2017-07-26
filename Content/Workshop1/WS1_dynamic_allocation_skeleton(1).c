/* Reading in an array of fixed length and computing the mean and variance of its elements */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Enter the filename
#define FILENAME "./data_wksp1ex5_2.txt"

int main(int argc, char *argv[]) {
	
	int i;
	int size;
	float mean, var;
	
	/* Read in the size of the array from file */
	FILE *f;
	f = fopen(FILENAME,"r");
	fscanf(f,"%d",&size);
	
	/* Allocate memory dynamically for the array */
	
	/* Read in the provided array here */
    
	/* Compute the mean and variance here */
	
	
    /* Output the values here */
    printf("The mean is: %f \n", mean);
    printf("The variance is: %f \n", var);
    
    /* Free the memory here */
    
	return 0;
}
