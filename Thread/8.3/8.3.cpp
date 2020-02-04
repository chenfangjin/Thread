#include <iostream>
#include <thread>
using namespace std;

void thfunc(int &n)
{
	cout << n << endl;
	n = n+20;
}

int main(int argc, char *argv[])
{ 
	int n = 0;
	cout << n << endl;
	thread t1(thfunc, ref(n));
	thread t2(move(t1));
	t2.join();
	
	cout << n << endl;
	return 0;
}
