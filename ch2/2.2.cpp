#include <iostream>
#include <thread>

struct func
{
	int &i;
	func(int& i_) : i(i_) {}
	void operator()()
	{
		for (unsigned j = 0; j < 1000000; ++j)
		{
			do_something(i);
		}
	}
};

void do_something_in_current_thread() {}

//避免应用程序在引发异常的时候被终止
//在存在异常的时候也要调用join()
void f()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		do_something_in_current_thread();
	}
	catch (...)
	{
		t.join();
		throw;
	}
	t.join();
}

int main()
{
	f();
	return 0;
}
