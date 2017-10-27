#include <string>
#include <future>

struct X
{
    void foo(int, const std::string&);
    std::string bar(std::string const&);
};

X x;
auto f1 = std::async(&X::foo, &x, 42, "hello");    //p->foo(42, "hello"), p��ָ��x��ָ��
auto f2 = std::async(&X::bar, x, "goodbye");       //tmp.bar(goodbye), tmp��x�Ŀ�������

struct Y
{
    double operator()(double);
};
Y y;
auto f3 = std::async(Y(), 3.141);          //����tmp(3.141),tmpͨ��y���ƶ����캯���õ�
auto f4 = std::async(std::ref(y), 2.718);  //����y(2.718)
X baz(X&);
std::async(baz, std::ref(x));              //����baz(x)
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

auto f5 = std::async(move_only);          //����tmp(), tmp��ͨ��std::move(move_only())����õ�
auto f6 = std::async(std::launch::async, Y(), 1.2);     //�µĶ����߳���ִ��
auto f7 = std::async(std::launch::deferred, baz, std::ref(x));      //��wait()��get()����ʱִ��
auto f8 = std::async(
        std::launch::deferred | std::launch::async,
        baz, std::ref(x));
auto f9 = std::async(baz, std::ref(x));
f7.wait();

