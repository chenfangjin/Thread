#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

mutex mymutex;
once_flag myFlag;

class myClass
{
private:
	myClass(){};
private:
	static myClass *myPtr;
public:
	static void singleCreate()
	{
		myPtr = new myClass();
		static delClass mydelclass;	
	}
	static myClass *getInstance()
	{
		call_once(myFlag, singleCreate);
	//	if(myPtr == NULL)
	//	{
	//		unique_lock<mutex> mylock(mymutex);
	//		if(myPtr == NULL)
	//		{
	//			myPtr = new myClass();
	//			static delClass mydelclass;
	//		}
	//	}
			return myPtr;
	}
	class delClass
	{
	public:
		~delClass()
		{
			delete myPtr;
			cout << "delete myPtr" << endl;
		}
	};
	void myPrint()
	{
		cout << "hello comedy" << endl;
	}
};

myClass *myClass::myPtr = NULL;

void myFunc()
{
	myClass *myptr1 = myClass::getInstance();
	myptr1->myPrint();
	cout << "hello yan" << endl;
}

int main(int argv, char *argc[])
{
	thread t1(myFunc);
	thread t2(myFunc);
	t1.join();
	t2.join();
	cout << " main thread end" << endl;
	return 0;
}
