// Zhichao Yang (.2236)

#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi, rand_r */
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#define N 2400
#define M 2000
#define P 500

typedef struct {
    int threadNum;
	int roundNum;   
} passin;

/* Global variables */
int row_number;
long** matrixa;
long** matrixb;
long** matrixc[7];

// Declare matrix
long** createMatrix (long row, long col){
	int r;
	long** matrix = malloc(row * sizeof(long*));    // allocate the rows
	for (r = 0; r < row; ++r){
		matrix[r] = malloc(col * sizeof(long));    // allocate the columns
	}
	return matrix;
}

// Check if the two matrix passed in is identical. If it is, return 1; Else, return 0.
int checkMatrix(long** firMatrix, long** SecMatrix){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < P; j++){
			if (firMatrix[i][j] != SecMatrix[i][j]){
				printf ("An error occured when comparing row %d and column %d.\n", i, j);
				printf ("matrixc of single thread is %ld.\n", firMatrix[i][j]);
				printf ("matrixc of multi thread is %ld.\n", SecMatrix[i][j]);
				return 0;
			}
		}
	}
	return 1;
}

// Assign jobs to each thread to find the result of row by row.
void *findRowResult(void *param) {
 	passin *b;
 	b=(passin*)param;

	int my_num = b->threadNum;
	int result = b->roundNum;
	int j, k;
	while(my_num < M){
		for(j = 0; j < P; j++){
			(matrixc[result])[my_num][j]=0;
			for(k = 0; k < M; k++){
				(matrixc[result])[my_num][j] += matrixa[my_num][k]*matrixb[k][j];
			}

		}
		my_num += result+1;
	}
}

/* The main */
int main(int argc, char*argv[]) {
	/* 1. Get command line arguments argv[1] */
	int number_of_thread = atoi(argv[1]);
	printf("Max number of thread to be created is %d\n", number_of_thread);

	/* 2. Declare and initialize matrix A, matrix B, and other vars */
	struct timeval start, end;
	double elapsed;
	int round_number = 0;
	int r, i, j;

	// matrixa, matrixb, matrixc[number_of_thread]
	matrixa = createMatrix(N, M);
	matrixb = createMatrix(M, P);
	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			matrixa[i][j] = j-i+2;
		}
	}
	for(i = 0; i < M; i++){
		for(j = 0; j < P; j++){
			matrixb[i][j] = i-j+1;
		}
	}
	for(i = 0; i < number_of_thread; i++){
		matrixc[i] = createMatrix(N, P);
	}
	
	// pthread
	pthread_t row_result_finder[number_of_thread];
  	pthread_attr_t attr;
  	pthread_attr_init(&attr);
	
printf("checkpoint 01\n");
fflush(0);

	/* 3. Calculation and Check*/
	for (round_number = 0; round_number < number_of_thread; round_number++){
		// set the variable to pass into pthread_create
		passin setPassIn[round_number];
		for (i = 0; i <= round_number; i++){
			setPassIn[i].threadNum = i;
			setPassIn[i].roundNum = round_number;
		}
		gettimeofday(&start, NULL);
		for (i = 0; i <= round_number; i++){
			pthread_create(&(row_result_finder[i]), &attr, &findRowResult,(void*)&(setPassIn[i]));
		}
		for (i = 0; i <= round_number; i++){
			pthread_join(row_result_finder[i], NULL);
		}
 		gettimeofday(&end, NULL);
		elapsed = ((((end.tv_sec - start.tv_sec)*1000000) + end.tv_usec) - (start.tv_usec)) / 1000000.0;
		printf ("thread: %d tooks %f seconds.\n",round_number + 1, elapsed);
		// check
		if (round_number != 0){
			if(checkMatrix((matrixc[0]),(matrixc[round_number]))){
				printf ("No error.\n");
			}
		}
// printf ("matrixc[0][0] is %d\n", (matrixc[round_number])[0][0]);
// printf ("matrixc[249][210] is %d\n", (matrixc[round_number])[833][166]);
// printf ("matrixc[249][210] is %d\n", (matrixc[round_number])[833][333]);
// printf ("matrixc[1249][249] is %d\n", (matrixc[round_number])[1249][249]);
// printf ("matrixc[249][210] is %d\n", (matrixc[round_number])[1666][166]);
// printf ("matrixc[249][210] is %d\n", (matrixc[round_number])[1666][333]);
// printf ("matrixc[2399][499] is %d\n", (matrixc[round_number])[2399][499]);

	}

printf("checkpoint 02\n");
fflush(0);
	

	/* 4. Release resources */
	pthread_attr_destroy(&attr);

	for (r = 0; r < N; ++r){
		free(matrixa[r]);    // free the columns
	}
	free(matrixa);    // free the rows
	for (r = 0; r < M; ++r){
		free(matrixb[r]);    // free the columns
	}
	free(matrixb);    // free the rows
	for (i = 0; i < number_of_thread; i++){
		for (r = 0; r < N; ++r){
			free((matrixc[i])[r]);    // free the columns
		}
		free(matrixc[i]);    // free the rows
	}
	

	/* 5. Exit */
	return 0;

}

