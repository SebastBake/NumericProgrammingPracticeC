/*
Written by Sebastian Baker as practice for Unimelb - Numerical Programming for Engineers

compile: gcc L2E2_StoreMatrix.c -o storeMatrix -Wall -Werror
test run: ./storeMatrix matrix.txt
================================================================================================
Lecture 2, Ex2
Write a program that can read n×m matrix of ints from stdin with the following format:
n = 2
m = 4
4  812 94 24
42 43  31 5
use dynamic memory allocation to store the matrix
output largest and smallest value in each column
Sample data ﬁle: matrix.txt
================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <float.h>

#define READ_ONLY_FILE "r"
#define MIN(a, b) ( (a < b) ? a : b )
#define MAX(a, b) ( (a < b) ? b : a )
#define MIN_FILENAME_LENGTH strlen("a.txt")


typedef struct matrixStruct  matrix_t;
struct matrixStruct {
	int rows;
	int cols;
	double ** data;
};

matrix_t * parseMatrix(char * filename);
double ** parseMatrixData(FILE *fp, int totalRows, int totalCols);
void printMinMaxInEachCol(matrix_t matrix);
void deleteMatrix(matrix_t * matrix);

int main(int argv, char *argc[]) {

	char *filename = argc[1];
	assert(strlen(filename) >= MIN_FILENAME_LENGTH);
	printf("File input: %s\n", filename);

	matrix_t * matrix = parseMatrix(filename);
	printMinMaxInEachCol(*matrix);
	deleteMatrix(matrix);
	matrix = NULL;


	printf("done!\n");
	return 0;
}

matrix_t * parseMatrix(char * filename) {

	// open file
	FILE * fp = fopen(filename, READ_ONLY_FILE);
	assert(fp != NULL);

	// initialise matrix
	matrix_t * matrix = (matrix_t *)(malloc(sizeof(matrix_t)));
	assert(matrix != NULL);

	// parse size info
	assert(fscanf(fp, "n = %d\n", &(matrix->rows)) == 1);
	assert(fscanf(fp, "m = %d\n", &(matrix->cols)) == 1);
	printf("rows n = %d, cols m = %d\n", matrix->rows, matrix->cols);
	
	// parse and allocate content of matrix
	matrix->data = parseMatrixData(fp, matrix->rows, matrix->cols);

	// close file
	fclose(fp);
	fp = NULL;
	return matrix;
}

double ** parseMatrixData(FILE *fp, int totalRows, int totalCols) {

	// bytes needed for mem alloc
	int bytesInArrayOfPtrsToRows = sizeof(double*)*(totalRows);
	int bytesPerRow = sizeof(double)*(totalCols);

	// alloc mem for array of ptrs to rows
	double ** arrayOfPtrsToRows = (double**)malloc(bytesInArrayOfPtrsToRows);
	assert(arrayOfPtrsToRows != NULL);

	double * newRow = NULL;
	int fileRow=0;
	for (fileRow=0; fileRow<totalRows; fileRow++) {

		// allocate mem for new row in matrix
		newRow = (double*)malloc(bytesPerRow);
		assert(newRow != NULL);

		// place data into the new row
		int fileCol=0;
		for (fileCol=0; fileCol<totalCols; fileCol++) {
			assert(fscanf(fp," %lf\n", &(newRow[fileCol])) == 1);
		}

		// add new row into array of rows
		arrayOfPtrsToRows[fileRow] = newRow;
	}
	return arrayOfPtrsToRows;
}

void printMinMaxInEachCol(matrix_t matrix) {
	
	double colMin = DBL_MAX;
	double colMax = -DBL_MAX;
	int row=0, col=0;

	for (col = 0; col < matrix.cols; col++) {

		colMin = DBL_MAX, colMax = -DBL_MAX;
		for (row=0; row<matrix.rows; row++) {
			colMax = MAX(matrix.data[row][col], colMax);
			colMin = MIN(matrix.data[row][col], colMin);
		}

		printf("Column %d: min = %.0f, max = %.0f\n", col+1, colMin, colMax);
	}
}

void deleteMatrix(matrix_t * matrix) {

	int fileRow = 0;
	for (fileRow=0; fileRow<matrix->rows; fileRow++) {
		free(matrix->data[fileRow]);
	}
	free(matrix->data);
	free(matrix);
}

