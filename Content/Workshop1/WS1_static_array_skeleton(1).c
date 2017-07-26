/* Reading in an array of fixed length and computing the mean and variance of its elements */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	
	/* Allocate memory statically for the array */
	
	/* Read in the provided array here */
	FILE *f;
	f = fopen("W1Ex2_data.txt","r");
    for (i=0;i<5;i++) fscanf(f,"%d",&a[i]);
    fclose(f);
	
	/* Compute the mean here */
	
    /* Output the values here */
    printf("The mean is: %f \n", mean);
    printf("The variance is: %f \n", var);
    
	return 0;
}
