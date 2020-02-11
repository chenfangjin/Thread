#include<iostream>
#include<thread>

using namespace std;

class A
{
public:
	int myNum;
	A(int num):myNum(num)
	{
		cout << "createFunction is running" << num << endl;
	}
	A(const A &a):myNum(a.myNum)
	{
		cout << "copyFunction is running" << endl;
	}
	
	void myFunction(int num)
	{
		myNum = num;
		cout << "memberFunction is running" <<myNum <<endl;
	}

	~A()
	{	
		cout << "cancelFunction is running" << endl;
	}
};
void myFunc(unique_ptr<int> ptr)
{
	cout << "ptr point to :" << *ptr << endl;
	return;
}

int main(int argc, char* argv[])
{
	unique_ptr<int> ptrq(new int(100));
	thread mythread1(myFunc, move(ptrq));
	
	A a(999);
	thread mythread2(&A::myFunction, a, 99);
	
	mythread1.join();
	mythread2.join();
	
	cout << "the main thread is end" << endl;
	return 0;
}
