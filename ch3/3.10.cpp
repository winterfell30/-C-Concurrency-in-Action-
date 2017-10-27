class Y
{
    private:
        int some_detail;
        mutable std::mutex m;
        int get_detail() const
        {
            std::lock_guard<std::mutex> lk(m);
            return some_detail;
        }
    public:
        Y(int sd):some_detail(sd) {}
        friend bool operator==(Y const& lhs, Y const& rhs)
        {
            if (&lhs == &rhs)
                return true;
            const int lhs_val = lhs.get_detail();
            const int rhs_val = rhs.get_detail();
            return lhs_val == rhs_val;
        }
};
