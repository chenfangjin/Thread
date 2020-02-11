#include <iostream>
#include <thread>

using namespace std;
class A
{
public:
	mutable	int i;
	A(int a):i(a){cout << "createFunction is running"<<"thread id is:"<< this_thread::get_id() << endl;}
	A(const A &a):i(a.i){cout << "copyFunction is running" <<"thread id is:" <<this_thread::get_id() << endl;}
	~A(){cout << "cancelFunction is running" << "thread id is" << this_thread::get_id() << endl;}
};

void myFunc(const A &a)
{
	a.i = 100;
	cout <<this_thread::get_id()<<"thread's parameter is :"<< a.i << endl;
}

int main()
{
	cout <<"the main thread id is:"<< this_thread::get_id() << endl;
	int par = 99;
	A a(par);
	thread mythread(myFunc,ref(a));
	
	mythread.join();
		cout <<this_thread::get_id()<< "thread's paramter is : "<<a.i << endl;
	return 0;
	
}
