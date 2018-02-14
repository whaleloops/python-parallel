#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi, rand_r */
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

typedef struct {
int x;
int y;
} point;

int main(int argc, char*argv[]) {
// creates a variable p
// of point type
point setP[3];

setP[0].x = 1;
setP[0].y = 2;

setP[1].x = 4;
setP[1].y = 5;

setP[2].x = 8;
setP[2].y = 9;

printf ("p.x is %d, and p.y is %d\n", setP[0].x, setP[0].y);
printf ("p.x is %d, and p.y is %d\n", setP[1].x, setP[1].y);
printf ("p.x is %d, and p.y is %d\n", setP[2].x, setP[2].y);

}
