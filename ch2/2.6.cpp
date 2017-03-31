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


//���2.3ֱ��move�����Ǵ���
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
	//����һ��Ҫ���ֳ���仰�ǹ���һ���������������һ��������Ϊt�ĺ���
	//����Ҫ�����Ż��߻����Ű�std::thread()���������ֳ���һ������
	//��������û��ע�����޷�����ͨ����
	scoped_thread t({ std::thread(func(some_local_state)) });    
	do_something_in_current_thread();
}

int main()
{
	f();
	std::cout << sum;
	return 0;
}
