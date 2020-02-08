#include <iostream>
#include <future>
#include <thread>

using namespace std;
int main()
{
	packaged_task<int()> task([](){return 7;});
	future<int> f1 = task.get_future();
	thread(move(task)).detach();
	
	future<int> f2 = async(launch::async, [](){return 8;});
	
	promise<int> p;
	future<int> f3 = p.get_future();
//	thread([&p]{p.set_value_at_thread_exit(9);}).detach();
	
	cout << "waiting...."<< flush;
	f1.wait();
	f2.wait();
//	f3.wait();
	
	cout << "results are computed: " << f1.get() << f2.get() << endl;
	return 0;
}
