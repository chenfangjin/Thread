#include "threadPool.h"
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

class CMyTask : public CTask 
{
public:
	CMyTask() = default;
	int Run()
		{
			printf("%s\n", (char *)ptrData);
			int x = rand() % 4 + 1;
			sleep(x);
			return 0;
		}
	~CMyTask(){}
};

int main()
{
	CMyTask taskObj;
	char szTmp[] = "hello comedy";
	taskObj.setData((void*)szTmp);
	CThreadPool threadpool(5);
	
	for (int i = 0; i < 10; i++)
		threadpool.AddTask(&taskObj);
	
	while(1)
	{
		printf("There are still %d tasks need to handle\n",threadpool.getTaskSize());
		if(threadpool.getTaskSize()==0)
		{
			if(threadpool.StopAll() == -1)
			{
				printf("Thread pool clear, exit.\n");
				exit(0);
			}
		}	
		sleep(2);
		cout << "2 seconds later..." << endl;
	}
	return 0;
}
