#include"pthread.h"
#include"stdlib.h"
#include"stdio.h"

struct test
{
 int var1,var2;
 float var3;
};

typedef struct test struct1;

void* fun1(void* a)
{
 struct1 *b;
 b=(struct1*)a;
 b->var3=b->var1+b->var2;
 printf("\nOperation successful the sum is %f\n",b->var3);
}

int main()
{
 pthread_t th1,th2;
 struct1 *a;
 a=(struct1 *)malloc(sizeof(struct1));
 a->var1=10;
 a->var2=20;
 pthread_create(&th1,NULL,fun1,(void*) a);
 pthread_join(th1,NULL);
 return 0;
}
#include"pthread.h"
#include"stdlib.h"
#include"stdio.h"

