std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

void foo()              //每次都要加锁效率低
{
    std::unique_lock<std::mutex> lk(resource_mutex);
    if (!resource_ptr)
    {
        resource_ptr.reset(new some_resource);
    }
    lk.unlock();
    resource_ptr->do_something();
}

void undefined_behaviour_with_double_checked_locking()
{
    if (!resource_ptr)
    {
        std::lock_guard<std::mutex> lk(resource_ptr);
        if (!resource_ptr)
        {
            resource_ptr.reset(new some_resource);      //@
        }
    }
    resource_ptr->do_something();
}
//一个线程在@位置有可能先分配内存在创建对象，在创建对象期间另一个线程判断对象不为null就可能调用do_something()，实际上resource_ptr还没有被构造出来
