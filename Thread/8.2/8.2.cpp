#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *thfunc(void *arg)
{
	cout << "sub thread is running";
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thread_id;
	pthread_attr_t thread_attr;
	int res;
	
	res = pthread_attr_init(&thread_attr);
	res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	res = pthread_create(&thread_id, &thread_attr, thfunc, NULL);
	cout << "main thread will exit"<< endl;

	sleep(1);
}
