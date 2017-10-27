template <typename T, typename Container = std::deque<T> >
class queue
{
    public:
        explicit queue(const Container&);
        explicit queue(Container&& = Container());
        template<typename Alloc> queue(const Alloc&);
        template<typename Alloc> queue(const Container&, const Alloc&);
        template<typename Alloc> queue(Container&&, const Alloc&);
        template<typename Alloc> queue(queue&&, const Alloc&);

        void swap(queue& q);
        
        bool empty() const;
        size_type size() const;

        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        void push(const T& x);
        void push(T&& x);
        void pop();
        template<typename... Args> void emplace(Args&&... args);
}
