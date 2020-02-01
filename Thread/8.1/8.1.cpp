#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void *thfunc(void *arg)
{
	char *parameter =(char*) arg;
	cout << "hello comedy"<< endl;
	return (void *)0;
}
int main(int argc, char *argv [])
{
	pthread_t tidp;
	int ret;
	const char *str = "hello comedy";
	ret = pthread_create(&tidp, NULL, thfunc, (void*)str);
	if(ret)
	{
		 printf("pthread_create failed:%d\n", ret);
		 return -1;
	}
	
	pthread_join(tidp, NULL);
	printf("in main: thread is created\n");
	return 0;
}
