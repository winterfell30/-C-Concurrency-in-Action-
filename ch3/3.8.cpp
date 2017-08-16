#include <stack>
#include <mutex>
#include <memory>

class hierarchical_mutex
{
public:
    explicit hierarchical_mutex(unsigned long value) :
            hierarchy_value(value), previous_hierarcy_value(0) {}
    void lock()
    {
        check_for_hierarchy_violation();
        internal_mutex.lock();
        update_hierarchy_value();
    }
    void unlock()
    {
        this_thread_hierarchy_value = previous_hierarcy_value;
        internal_mutex.unlock();
    }
    bool try_lock()
    {
        check_for_hierarchy_violation();
        if (!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
private:
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarcy_value;
    static thread_local unsigned long this_thread_hierarchy_value;
    void check_for_hierarchy_violation()
    {
        if (this_thread_hierarchy_value <= hierarchy_value)
        {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update_hierarchy_value()
    {
        previous_hierarcy_value = this_thread_hierarchy_value;
        this_thread_hierarchy_value = hierarchy_value;
    }
};
