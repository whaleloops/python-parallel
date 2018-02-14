// Zhichao Yang (.2236)

#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi, rand_r */
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

 
int** createMatrix (int row, int col){
	int r;
	int** matrix = malloc(row * sizeof(int*));    // allocate the rows
	for (r = 0; r < row; ++r){
		matrix[r] = malloc(col * sizeof(int));    // allocate the columns
	}
	return matrix;
}

int** matrixc[3];

int main(int argc, char*argv[]) {
// declare
	int i,j,r;
	int a = 2, b = 3;
// craete matrix
	for (i=0;i<2;i++){
		matrixc[i] = createMatrix(a, b);
	}

// test
	for(i = 0; i < a; i++){
		for(j = 0; j < b; j++){
			(matrixc[0])[i][j] = i;
		}
	}
	for(i = 0; i < a; i++){
		for(j = 0; j < b; j++){
			(matrixc[1])[i][j] = i-j+1;
		}
	}

	for(i = 0; i < a; i++){
		for(j = 0; j < b; j++){
			printf ("matrixc[0][%d][%d] is %d\n", i,j,(matrixc[0])[i][j]);
		}
	}
	for(i = 0; i < a; i++){
		for(j = 0; j < b; j++){
			printf ("matrixc[1][%d][%d] is %d\n", i,j,(matrixc[1])[i][j]);
		}
	}

// free
	for (i = 0; i < 2; i++){
		for (r = 0; r < a; ++r){
			free((matrixc[i])[r]);    // free the columns
		}
	free(matrixc[i]);    // free the rows
	}

}
