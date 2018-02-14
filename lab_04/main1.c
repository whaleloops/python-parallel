// Zhichao Yang (.2236)

#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi, rand_r */
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N 2400
#define M 2000
#define P 500
 
struct passins {                                                            
    int threadNum;
	int roundNum;                                                          
};
typedef struct passins passin1;

int** createMatrix (int row, int col){
	int r;
	int** matrix = malloc(row * sizeof(int*));    // allocate the rows
	for (r = 0; r < row; ++r){
		matrix[r] = malloc(col * sizeof(int));    // allocate the columns
	}
	return matrix;
}

/* Global variables */
int row_number;
int** matrixa;
int** matrixb;
int** matrixc[7];

void *findRowResult(void *param) {
 	passin1 *b;
 	b=(passin1*)param;

	int my_num = b->threadNum;
	int result = b->roundNum;
printf("my_num is %d\n", my_num);
printf("result is %d\n", result);
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
	clock_t t;
	int round_number = 0;
	int r, i, j, k;

	matrixa = createMatrix(N, M);
	matrixb = createMatrix(M, P);
	for(i = 0; i < number_of_thread; i++){
		matrixc[i] = createMatrix(N, P);
	}

	pthread_t row_result_finder[number_of_thread];
  	pthread_attr_t attr;
  	pthread_attr_init(&attr);

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
	int numberOfThreadArray [number_of_thread];
	for (i = 0; i < number_of_thread; i++){
		numberOfThreadArray [i] = i;
	}
printf("checkpoint 01\n");
fflush(0);

	/* 3. Calculation */
	// non thread
	t = clock();
	for(i = 0; i < N; i++){
		for(j = 0; j < P; j++){
			(matrixc[0])[i][j]=0;
			for(k = 0; k < M; k++){
				(matrixc[0])[i][j] += matrixa[i][k]*matrixb[k][j];
			}
		}
	}
	t = clock() - t;
	printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);
printf ("matrixc1[0][0] is %d\n", (matrixc[0])[0][0]);

printf("checkpoint 02\n");
fflush(0);




	passin1 *a;
	a = (passin1 *)malloc(sizeof(passin1));
	// multi thread
	t = clock();
	for (i = 0; i < number_of_thread; i++){
		a->threadNum = numberOfThreadArray[i];
		a->roundNum =1; //1 to be changed
		pthread_create(&(row_result_finder[i]), &attr, &findRowResult,(void*)a);
	}
	for (i = 0; i < number_of_thread; i++){
		pthread_join(row_result_finder[i], NULL);
	}
	t = clock() - t;
	printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);
printf ("matrixc2[0][0] is %d\n", (matrixc[1])[0][0]);


	// check

	/* 6. Release resources */
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
	

	/* 7. Exit */
	return 0;

}

