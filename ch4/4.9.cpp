std::mutex mut;
std::deque<std::package_task<void()> > tasks;

bool gui_shutdown_message_receive();

void get_and_process_gui_message();

void gui_thread()
{
    while (!gui_shutdown_message_received())
    {
        get_and_process_gui_message();
        std::package_task<void()> task;
        {
            std::lock_guard<std::mutex> lk(mut);
            if (tasks.empty())
                continue;
            task = std::move(tasks.front());
            tasks.pop_front();
        }
        task();
    }
}

std::thread gui_bg_thread(gui_thread);

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
    std::package_task<void()> task(f);
    std::future<void> res = task.get_future();
    std::lock_guard<std::mutex> lk(mut);
    tasks.push_back(std::move(task));
    return res;
}
