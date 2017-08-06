#include <list>
#include <mutex>
#include <algorithm>

/*
 * 在process_data中调用func互斥量失效
 * 不要将保护数据的指针或引用传到互斥量作用域之外
 */
class some_data
{
private:
    int a;
    std::string b;
public:
    void do_something();
};

class data_wrapper
{
private:
    some_data data;
    std::mutex m;
public:
    template <typename Function>
            void process_data(Function func)
    {
        std::lock_guard<std::mutex> guard(m);
        func(data);
    }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
    unprotected = &protected_data;
}

data_wrapper x;
void foo()
{
    x.process_data(malicious_function);
    unprotected->do_something();
}

int main()
{
    return 0;
}
