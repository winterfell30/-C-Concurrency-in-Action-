template <>
class package_task<std::string(std::vector<char>*, int)>
{
    public:
        template<typename Callable>
        explicit package_task(Callable&& f);
        std::future<std::string> get_future();
        void operator()(std::vector<char>*, int);
}
