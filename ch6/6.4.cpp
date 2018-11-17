template<typename T>

class queue
{
private:
    struct node
    {
        T data;
        std::unique_ptr<node> next;

        node(T node_):
            data(node_) {}
    };

    std::unique_ptr<node> head;
    node* tail;
public:
    queue()
    {}
    queue(const queue& other) = delete;
    queue& operator=(const queue& other) = delete;
    std::shared_ptr<T> try_pop()
    {
        if (!head)
        {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(head->data));
        std::unique_ptr<node> const old_head = std::move(head);
        head = std::move(old_head->next);
        return res;
    }
    void push(T new_value)
    {
        std::unique_ptr<node> p(new node(std::move(new_value)));
        node* new_tail = p.get();
        if (tail)
        {
            tail->next = std::move(p);
        }
        else
        {
            head = std::move(p);
        }
        tail = new_tail;
    }
};