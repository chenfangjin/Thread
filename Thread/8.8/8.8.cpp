#include <iostream>
#include <vector>
#include <thread>

using namespace std;

vector<int> parameter = {1,2,3};

void myFunc(int num)
{
	cout << num << "+" << parameter[0] << parameter[1] << parameter[2] << endl;
	return;
}

int main()
{
	vector<thread> vecThread;
	for(int i = 0; i < 10; i++)
	{
		vecThread.push_back(thread(myFunc, i));
	}
	
	for(auto iter = vecThread.begin(); iter != vecThread.end(); iter++)
	{
		iter->join();
	}
	
	cout << "main thread is end;" << endl;
	
	return 0;
	
}
