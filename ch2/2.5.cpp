#include <iostream>
#include <thread>
#include <string>

void some_function() { std::cout << "call" << std::endl; }
void some_other_function(int i) { std::cout << i << std::endl; }

std::thread f()
{
	void some_function();
	return std::thread(some_function);
}

std::thread g()
{
	void some_other_function(int);
	std::thread t(some_other_function, 42);
	return t;
}

void ff(std::thread t) 
{
	t.detach();
};
void gg()
{
	void some_function();
	ff(std::thread(some_function));
	std::thread t(some_function);
	ff(std::move(t));
}

int main()
{
	std::thread t(g());
	t.join();
	gg();
	return 0;
}
