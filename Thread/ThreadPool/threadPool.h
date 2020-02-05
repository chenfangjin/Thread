#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <vector>
#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;

//this class is for task excuting
class CTask
{
protected:
	string strTaskname;
	void *ptrData;

public:
	CTask() = default;
	CTask(string &taskName): strTaskname(taskName), ptrData(NULL){}
	virtual int Run() = 0;
	void setData(void* data);
		
	virtual ~CTask(){}	
};

class CThreadPool
{
private:
	static vector<CTask*> vecTasklist;
	static bool shutdown;
	int threadNum;
	pthread_t *pthread_id;
	
	static pthread_mutex_t pthreadMutex;
	static pthread_cond_t pthreadCond;

protected:
	static void *ThreadFunc(void *threadData);
	static int MoveToIdle(pthread_t tid);
	static int MoveToBusy(pthread_t tid);
	int Create();

public:
	CThreadPool(int threadNum);	
	int AddTask(CTask *task);
	int StopAll();
	int getTaskSize();
};

#endif
