#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>

void do_works(int i) {}

void f()
{
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 20; i++)
	{
		threads.push_back(std::thread(do_works, i));
	}
	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));
}

int main()
{
	f();
	return 0;
}
