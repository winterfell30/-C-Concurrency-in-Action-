#include <iostream>
#include <thread>
#include <string>

static int sum;

void do_something(int i)
{
	sum++;
}

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

void some_function() { std::cout << "call" << std::endl; }
void some_other_function(int i) { std::cout << i << std::endl; }
void do_something_in_current_thread() {}


//相比2.3直接move而不是创建
class scoped_thread
{
public:
	explicit scoped_thread(std::thread t_) :
		t(std::move(t_))
	{
		std::cout << "2333" << std::endl;
		if (!t.joinable())
			throw std::logic_error("No thread");
	}
	~scoped_thread()
	{
		std::cout << "2333" << std::endl;
		t.join();
	}
	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
private:
	std::thread t;
};

void f()
{
	int some_local_state = 0;
	//这里一定要体现出这句话是构造一个对象而不是声明一个函数名为t的函数
	//所以要用括号或者花括号把std::thread()包起来体现出是一个变量
	//这里书里没有注意是无法测试通过的
	scoped_thread t({ std::thread(func(some_local_state)) });    
	do_something_in_current_thread();
}

int main()
{
	f();
	std::cout << sum;
	return 0;
}
