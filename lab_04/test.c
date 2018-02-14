#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


int main()
{
	const int n=2400, m=2000, p=500;
printf("checkpoint 00\n");
fflush(0);
	clock_t t;
	t = clock();
	int** array = malloc(n * sizeof(int*));    // allocate the rows
	int r;
	for (r = 0; r < n; ++r)
	{
		array[r] = malloc(m * sizeof(int));    // allocate the columns
	}
	array[10][50] = 10;    // insert data at row 10, column 50

	for (r = 0; r < n; ++r)
	{
		free(array[r]);    // this frees the columns
	}
	free(array);    // this frees the rows
	t = clock() - t;
	printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);
printf("checkpoint 01\n");
fflush(0);

return 0;
}
