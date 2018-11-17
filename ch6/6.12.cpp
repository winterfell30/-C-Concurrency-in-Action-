std::map<Key, Value> threadsafe_lookup_table::get_map() const
{
    std::vector<std::unique_lock<boost::shared_mutex> > locks;
    for (size_t i = 0; i < buckets.size(); ++i)
    {
        locks.push_back(std::unique_lock<boost::shared_mutex>(buckets[i].mutex));
    }
    std::map<Key, Value> res;
    for (size_t i = 0; i < buckets.size(); ++i)
    {
        for (bucket_iteartor it = buckets[i].data.begin(); it != buckets[i].data.end(); ++it)
        {
            res.insert(*it);
        }
    }
    return res;
}