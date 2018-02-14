// Zhichao Yang(.2236) and Zhuoer Wang(.5538)
// To compile this file, run "gcc -O1 -Wall -o result main.c -lpthread" in the terminal.
// To run the compiled file, run "result <number>" where <number> is from 1 to 7.

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
int matrixa[N][M];
int matrixb[M][P];
int (matrixc[7])[N][P];

// Check if the two matrix passed in is identical. If it is, return 1; Else, return 0.
int checkMatrix(int firMatrix[N][P], int SecMatrix[N][P]){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < P; j++){
			if (firMatrix[i][j] != SecMatrix[i][j]){
				printf ("An error occured when comparing row %d and column %d.\n", i, j);
				printf ("matrixc of single thread is %d.\n", firMatrix[i][j]);
				printf ("matrixc of multi thread is %d.\n", SecMatrix[i][j]);
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
	while(my_num < N){
		for(j = 0; j < P; j++){
			(matrixc[result])[my_num][j]=0;
			for(k = 0; k < M; k++){
				(matrixc[result])[my_num][j] += matrixa[my_num][k]*matrixb[k][j];
			}

		}
		my_num += result+1;
	}
	pthread_exit(NULL);
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
	int i, j;

	// matrixa, matrixb, matrixc[number_of_thread]
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
	
	// pthread
	pthread_t row_result_finder[number_of_thread];
  	pthread_attr_t attr;
  	pthread_attr_init(&attr);

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
		elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
		printf ("thread: %d took %f seconds.\n",round_number + 1, elapsed);
		// check
		if (round_number != 0){
			if(checkMatrix((matrixc[0]),(matrixc[round_number]))){
				printf ("No error.\n");
			}
		}

	// testcases
	// printf ("matrixc[1][1] is %d\n", (matrixc[round_number])[1][1]);
	// printf ("matrixc[2][2] is %d\n", (matrixc[round_number])[2][2]);
	// printf ("matrixc[3][3] is %d\n", (matrixc[round_number])[3][3]);
	// printf ("matrixc[4][4] is %d\n", (matrixc[round_number])[4][4]);
	// printf ("matrixc[5][5] is %d\n", (matrixc[round_number])[5][5]);
	// printf ("matrixc[6][6] is %d\n", (matrixc[round_number])[6][6]);
	// printf ("matrixc[7][7] is %d\n", (matrixc[round_number])[7][7]);
	// printf ("matrixc[8][8] is %d\n", (matrixc[round_number])[8][8]);
	// printf ("matrixc[9][9] is %d\n", (matrixc[round_number])[9][9]);
	// printf ("matrixc[10][10] is %d\n", (matrixc[round_number])[10][10]);
	// printf ("matrixc[11][11] is %d\n", (matrixc[round_number])[11][11]);
	// printf ("matrixc[12][12] is %d\n", (matrixc[round_number])[12][12]);
	// printf ("matrixc[13][13] is %d\n", (matrixc[round_number])[13][13]);
	// printf ("matrixc[14][14] is %d\n", (matrixc[round_number])[14][14]);
	// printf ("matrixc[15][15] is %d\n", (matrixc[round_number])[15][15]);
	// printf ("matrixc[16][16] is %d\n", (matrixc[round_number])[16][16]);
	// printf ("matrixc[17][17] is %d\n", (matrixc[round_number])[17][17]);
	// printf ("matrixc[18][18] is %d\n", (matrixc[round_number])[18][18]);

	// printf ("matrixc[0][0] is %d\n", (matrixc[round_number])[0][0]);
	// printf ("matrixc[0][124] is %d\n", (matrixc[round_number])[0][124]);
	// printf ("matrixc[0][249] is %d\n", (matrixc[round_number])[0][249]);
	// printf ("matrixc[0][374] is %d\n", (matrixc[round_number])[0][374]);
	// printf ("matrixc[0][499] is %d\n", (matrixc[round_number])[0][499]);

	// printf ("matrixc[599][0] is %d\n", (matrixc[round_number])[599][0]);
	// printf ("matrixc[599][124] is %d\n", (matrixc[round_number])[599][124]);
	// printf ("matrixc[599][249] is %d\n", (matrixc[round_number])[599][249]);
	// printf ("matrixc[599][374] is %d\n", (matrixc[round_number])[599][374]);
	// printf ("matrixc[599][499] is %d\n", (matrixc[round_number])[599][499]);

	// printf ("matrixc[1199][0] is %d\n", (matrixc[round_number])[1199][0]);
	// printf ("matrixc[1199][124] is %d\n", (matrixc[round_number])[1199][124]);
	// printf ("matrixc[1199][249] is %d\n", (matrixc[round_number])[1199][249]);
	// printf ("matrixc[1199][374] is %d\n", (matrixc[round_number])[1199][374]);
	// printf ("matrixc[1199][499] is %d\n", (matrixc[round_number])[1199][499]);

	// printf ("matrixc[1799][0] is %d\n", (matrixc[round_number])[1799][0]);
	// printf ("matrixc[1799][124] is %d\n", (matrixc[round_number])[1799][124]);
	// printf ("matrixc[1799][249] is %d\n", (matrixc[round_number])[1799][249]);
	// printf ("matrixc[1799][374] is %d\n", (matrixc[round_number])[1799][374]);
	// printf ("matrixc[1799][499] is %d\n", (matrixc[round_number])[1799][499]);

	// printf ("matrixc[2399][0] is %d\n", (matrixc[round_number])[2399][0]);
	// printf ("matrixc[2399][124] is %d\n", (matrixc[round_number])[2399][124]);
	// printf ("matrixc[2399][249] is %d\n", (matrixc[round_number])[2399][249]);
	// printf ("matrixc[2399][374] is %d\n", (matrixc[round_number])[2399][374]);
	// printf ("matrixc[2399][499] is %d\n", (matrixc[round_number])[2399][499]);
	}
	printf("Done\n");
	fflush(0);
	

	/* 4. Release resources */
	pthread_attr_destroy(&attr);

	
	/* 5. Exit */
	return 0;

}

