#include <iostream>
#include <thread>
#include <list>
#include <mutex>

using namespace std;

class A
{
public:
	void inCommand()
	{
		for(int i = 0; i < 1000; i++)
		{
			lock(mylock1,mylock2);
			lock_guard<mutex> myguard1(mylock1,adopt_lock);
			lock_guard<mutex> myguard2(mylock2,adopt_lock);
		//	mylock.lock();
			ticket.push_back(i);
			cout << "a command is comming" << endl;
		//	mylock.unlock();
		}
	}
	
	void outCommand()
	{
		for(int j = 0; j < 1000; j++)
		{
			lock(mylock1,mylock2);
			lock_guard<mutex> myguard1(mylock1,adopt_lock);
			lock_guard<mutex> myguard2(mylock2,adopt_lock);
			//	mylock.lock();
			if(!ticket.empty())
			{
				int command = ticket.front();
				ticket.pop_front();	
				cout << "command is :" << command << endl;
			//	mylock.unlock();
			}
			else
			{
				cout << "there is no people" << endl;	
			//	mylock.unlock();
			}
		}
		
	}
	
private:
	list<int> ticket;
	mutex mylock1;
	mutex mylock2;
};

int main(int argc, char *argv[])
{
	A a;
	thread thread1(&A::inCommand, &a);
	thread thread2(&A::outCommand, &a);
	thread1.join();
	thread2.join();

	cout << "the main thread is end;" << endl;
	return 0;
}
