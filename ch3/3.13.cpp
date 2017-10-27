class dns_entry;

class dns_cache
{
    std::map<std::string, dns_entry> entries;
    mutable boost::shared_mutex entry_mutex;
public:
    dns_entry find_entry(const std::string& domain) const
    {
        std::shared_lock<std::shared_mutex> lk(entry_mutex);
        const std::map<std::string, dns_entry>::const_iterator it = 
            entries.find(domain);
        return (it == entries.end() ? dns_entry() : it->second);
    }
    void update_or_add_entry(const std::string& domain, const dns_entry& dns_details)
    {
        std::lock_guard<std::shared_mutex> lk(entry_mutex);
        entries[domain] = dns_details;
    }
}
