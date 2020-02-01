#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

typedef struct
{
	int n;
	const char *str;
}MyStruct;
void *thfunc(void *arg)
{
	MyStruct *parameter =(MyStruct*) arg;
	cout << parameter->n << endl;
	return (void *)0;
}
int main(int argc, char *argv [])
{
	pthread_t tidp;
	int ret;
	MyStruct mystruct;
	mystruct.n = 100;
	mystruct.str = "hello comedy";
	ret = pthread_create(&tidp, NULL, thfunc, (void *)&mystruct);
	if(ret)
	{
		 printf("pthread_create failed:%d\n", ret);
		 return -1;
	}
	
	pthread_join(tidp, NULL);
	printf("in main: thread is created\n");
	return 0;
}
