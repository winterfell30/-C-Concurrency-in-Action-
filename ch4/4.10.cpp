#include <future>

void process_connection(connection_set& connections)
{
    while (!done(connections))
    {
        for (connection_iterator connection = connections.begin(), end = connections.end();
                connection != end; ++connection)
        {
            if (connection->has_incoming_data())
            {
                data_package data = connection->incoming();
                std::promise<payload_type>& p = connection->get_promise(data.id);
                p.set_value(data.payload);
            }
            if (connection->has_outgoing_data())
            {
                outgoing_package data = connection->top_of_outgoing_queue();
                connection->send(data.payload);
                data.promise.set_value(true);
            }
        }
    }
}
