#include <iostream>
#include <thread>

using namespace std;

class myTest
{
public:
	int parameter;
	myTest(int i): parameter(i)
	{
		cout << "myTest's createFunction is running" << endl;
	}
	
	myTest(const myTest &test2) : parameter(test2.parameter)
	{
		cout << "myTest's copyFunction is running" << endl;
	}
	
	~myTest()
	{
		cout << "myTest's removeFunction is running" << endl;
	}
	void operator()()
	{
		cout << "my thread is created" << endl;
		cout << "my parameter is :" << parameter << endl;
		//....do something
		cout << "my thread is end" << endl;
	}

};

int main(int argc, char *argv[])
{
	int x = 99;
	myTest test(x);
	thread mythread(test);
	mythread.detach();
	
	cout << "the main thread is end " << endl;
	return 0;
}
