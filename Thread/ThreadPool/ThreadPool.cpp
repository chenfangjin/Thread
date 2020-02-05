#include "threadPool.h"
#include <cstdio>
#include <iostream>

void CTask::setData(void *data)
{
	ptrData = data;
}

vector<CTask*> CThreadPool::vecTasklist;
bool CThreadPool::shutdown = false;
pthread_mutex_t CThreadPool::pthreadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t CThreadPool::pthreadCond = PTHREAD_COND_INITIALIZER;

CThreadPool::CThreadPool(int threadNums)
{
	this->threadNum = threadNums;
	cout << "I will create "<< threadNums << endl;
	Create();
}

void *CThreadPool::ThreadFunc(void *threadData)
{
	pthread_t tid = pthread_self();
	while(1)
	{
		pthread_mutex_lock(&pthreadMutex);
		while(vecTasklist.size() == 0 && !shutdown)
			pthread_cond_wait(&pthreadCond, &pthreadMutex);
		
		if(shutdown)
		{
			pthread_mutex_unlock(&pthreadMutex);
			printf("[tid: %lu]\texit\n", pthread_self());
			pthread_exit(NULL);
		}
	
		printf("[tid: %lu]\trun: ", tid);
		vector<CTask*>::iterator iter = vecTasklist.begin();
	
		CTask *task = *iter;
		if(iter != vecTasklist.end())
		{
			task = *iter;
			vecTasklist.erase(iter);
		}
		
		pthread_mutex_unlock(&pthreadMutex);
		
		task->Run();
		printf("[tid: %lu]\tidle\n", tid);
	}
	
	return (void*)0;
}

int CThreadPool::AddTask(CTask *task)
{
	pthread_mutex_lock(&pthreadMutex);
	vecTasklist.push_back(task);
	pthread_mutex_unlock(&pthreadMutex);
	
	pthread_cond_signal(&pthreadCond);
	
	return 0;
} 

int CThreadPool::Create()
{
	pthread_id = new pthread_t[threadNum];
	for(int i = 0; i < threadNum; i++)
		pthread_create(&pthread_id[i], NULL, ThreadFunc, NULL);
	
	return 0;
}

int CThreadPool::StopAll()
{
	if(shutdown)
		return -1;
	cout << "i will end all thread" << endl;
	
	shutdown = true;
	pthread_cond_broadcast(&pthreadCond);
	
	for (int i = 0; i < threadNum; i++)
		pthread_join(pthread_id[i], NULL);

	delete[] pthread_id;
	pthread_id = NULL;

	pthread_mutex_destroy(&pthreadMutex);
	pthread_cond_destroy(&pthreadCond);
	
	return 0;
}

int CThreadPool::getTaskSize()
{
	return vecTasklist.size();
}
