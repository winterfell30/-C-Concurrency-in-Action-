#include <string>
#include <future>

struct X
{
    void foo(int, const std::string&);
    std::string bar(std::string const&);
};

X x;
auto f1 = std::async(&X::foo, &x, 42, "hello");    //p->foo(42, "hello"), p是指向x的指针
auto f2 = std::async(&X::bar, x, "goodbye");       //tmp.bar(goodbye), tmp是x的拷贝副本

struct Y
{
    double operator()(double);
};
Y y;
auto f3 = std::async(Y(), 3.141);          //调用tmp(3.141),tmp通过y的移动构造函数得到
auto f4 = std::async(std::ref(y), 2.718);  //调用y(2.718)
X baz(X&);
std::async(baz, std::ref(x));              //调用baz(x)
class move_only
{
    public:
        move_only();
        move_only(const move_only&) = delete;
        move_only(move_only&&);
        move_only& operator=(const move_only&) = delete;
        move_only& operator=(move_only&&);

        void operator()();
};

auto f5 = std::async(move_only);          //调用tmp(), tmp是通过std::move(move_only())构造得到
auto f6 = std::async(std::launch::async, Y(), 1.2);     //新的独立线程上执行
auto f7 = std::async(std::launch::deferred, baz, std::ref(x));      //在wait()或get()调用时执行
auto f8 = std::async(
        std::launch::deferred | std::launch::async,
        baz, std::ref(x));
auto f9 = std::async(baz, std::ref(x));
f7.wait();

