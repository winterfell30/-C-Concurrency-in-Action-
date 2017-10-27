std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

void foo()              //ÿ�ζ�Ҫ����Ч�ʵ�
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
//һ���߳���@λ���п����ȷ����ڴ��ڴ��������ڴ��������ڼ���һ���߳��ж϶���Ϊnull�Ϳ��ܵ���do_something()��ʵ����resource_ptr��û�б��������
