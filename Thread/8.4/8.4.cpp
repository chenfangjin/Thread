#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
	cout << "start count" << endl;
	for (int i = 5; i > 0; i--)
	{
		cout << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
	cout << "hello comedy"<< endl;
	return 0;
}
