#include <iostream>
#include <thread>
#include <list>

using namespace std;

class A
{
public:
	void inCommand()
	{
		for(int i = 0; i < 1000; i++)
		{
			ticket.push_back(i);
			cout << "a command is comming" << endl;
		}
	}
	
	void outCommand()
	{
		for(int j = 0; j < 1000; j++)
		{
			if(!ticket.empty())
			{
				int command = ticket.front();
				ticket.pop_front();	
				cout << "command is :" << command << endl;
			}
			else
			{
				cout << "there is no people" << endl;	
			}
		}
		
	}
	
private:
	list<int> ticket;
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
