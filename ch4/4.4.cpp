template<typename T>
class threadsafe_queue
{
    private:
        std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
    public:
        void push(T new_value)
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(new_value);
            data.cond.notify_one();
        }

        void wait_and_pop(T& value)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, []{return !data_queue.empty();});
            value = data_queue.front();
            data_queue.pop();
        }
};

threadsafe_queue<data_chunk> data_queue;

void data_prepare_thread()
{
    while (more_data_to_prepare())
    {
        const data_chunk data = prepare_data();
        data_queue.push(data);
    }
}

void data_process_thread()
{
    while (true)
    {
        data_chunk data;
        data_queue.wait_and_pop(data);
        process(data);
        if (is_last_chunk(data))
            break;
    }
}
