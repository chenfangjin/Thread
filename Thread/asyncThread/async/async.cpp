#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>

using namespace std;

mutex m;
struct X
{
	void foo(int i, const string &str)
	{
		lock_guard<mutex> lk(m);
		cout << str << ' ' << i << endl;
	}
	void bar(const string &str)
	{
		lock_guard<mutex> lk(m);
		cout << str << endl;	
	}
	int operator()(int i)
	{
		lock_guard<mutex> lk(m);
		cout << i << endl;
		return i + 10;
	}
};

template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
	auto len = end - beg;
	RandomIt mid = beg+ len/2;
	auto handle = async(launch::async, parallel_sum<RandomIt>, mid, end);
	int sum = parallel_sum(beg, mid);
	return sum + handle.get();
	
}

int main()
{
	vector<int> v(10000,1);
	cout << "The sum is " << parallel_sum(v.begin(), v.end()) << endl;;
	
	X x;
	
	auto a1 = async(&X::foo, &x, 43, "Hello");
	
	auto a2 = async(launch::deferred, &X::bar, x, "world");
	
	auto a3 = async(launch::async, X(), 43);
	
	a2.wait();

	cout << a3.get() << endl;
	
	return 0;
}
