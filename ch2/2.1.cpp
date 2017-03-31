#include <iostream>
#include <thread>

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

//����detach()��ʽ�������ȴ��߳�
//�����������dosomething�ͻ�����Ѿ������ٵı���
void oops()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();            //sumֵ���̶�
	//my_thread.join();            //sum=1000000
}

int main()
{
	oops();
	std::cout << sum << std::endl;
	return 0;
}
