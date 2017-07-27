/*
Written by Sebastian Baker as practice for Unimelb - Numerical Programming for Engineers
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

typedef struct matrixStruct  matrix_t;
struct matrixStruct {
	int rows;
	int cols;
	double ** data;
};

void processMatrixFile(char * filename);
void parseMatrixFile(char * filename, matrix_t *matrix);
double * parseRow(FILE *fp, int fileRow, int matrixCols);
void printMinMaxInEachCol(matrix_t matrix);
void deleteMatrix(matrix_t * matrix);

int main(int argv, char *argc[]) {

	// get input
	char *filename = argc[1];
	if (strlen(argc[1]) <= 4) {
		fprintf(stderr, "Filename too short! Exiting...\n");
		exit(EXIT_FAILURE);
	}
	printf("File input: %s\n", filename);

	processMatrixFile(filename);

	printf("done!\n");
	return 0;
}

void processMatrixFile(char * filename) {

	// initialise matrix
	matrix_t * matrix = (matrix_t *)(malloc(sizeof(matrix_t)));
	assert(matrix != NULL);
	
	// do stuff with the matrix
	parseMatrixFile(filename, matrix);
	printMinMaxInEachCol(*matrix);
	deleteMatrix(matrix);
	matrix = NULL;
}

void parseMatrixFile(char * filename, matrix_t *matrix) {

	// open file
	FILE * fp = fopen(filename, READ_ONLY_FILE);
	assert(fp != NULL);

	// parse size
	assert(fscanf(fp, "n = %d\n", &(matrix->rows)) == 1);
	assert(fscanf(fp, "m = %d\n", &(matrix->cols)) == 1);
	printf("rows n = %d, cols m = %d\n", matrix->rows, matrix->cols);
	
	// allocate memory space for all the rows
	int bytesInArrayOfRowPtrs = sizeof(double*)*(matrix->rows);
	matrix->data = (double**)malloc(bytesInArrayOfRowPtrs);
	assert(matrix->data != NULL);

	// parse file content by row
	int fileRow=0;
	for (fileRow=0; fileRow<matrix->rows; fileRow++) {
		matrix->data[fileRow] = parseRow(fp, fileRow, matrix->cols);
	}

	// close file
	fclose(fp);
	fp = NULL;
}

double * parseRow(FILE *fp, int fileRow, int matrixCols) {

	// allocate mem for new row in matrix
	int bytesInRow = sizeof(double)*(matrixCols);
	double * newRow = (double*)malloc(bytesInRow);
	assert(newRow != NULL);

	// Read data into the new array
	int fileCol=0;
	for (fileCol=0; fileCol<matrixCols; fileCol++) {
		assert(fscanf(fp," %lf\n", &(newRow[fileCol])) == 1);
		//printf("Recorded col=%d, row=%d, data=%.0f\n",fileCol, fileRow, newRow[fileCol]);
	}
	return newRow;
}

void printMinMaxInEachCol(matrix_t matrix) {
	
	double colMin, colMax, matrixEntry;

	int row = 0, col=0;
	for (col=0; col<matrix.cols; col++) {
		
		colMin = DBL_MAX, colMax = -DBL_MAX;

		for (row=0; row<matrix.rows; row++) {
			matrixEntry = matrix.data[row][col];
			colMax = matrixEntry > colMax ? matrixEntry : colMax;
			colMin = matrixEntry < colMin ?  matrixEntry : colMin;
		}

		printf("Column %d: min = %.0f, max = %.0f\n", col+1, colMin, colMax);
	}
}

void deleteMatrix(matrix_t * matrix) {

	int fileRow=0;
	for (fileRow=0; fileRow<matrix->rows; fileRow++) {
		free(matrix->data[fileRow]);
	}
	free(matrix->data);
	free(matrix);
}

