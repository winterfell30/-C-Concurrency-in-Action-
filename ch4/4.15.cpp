struct card_insert
{
    std::string account;
};

class atm
{
    messaging::receiver incoming;
    messaging::sender back;
    messaging::sender interface_hardware;
    void (atm::*state)();

    std::string account;
    std::string pin;

    void waiting_for_card()
    {
        interface_hardware.send(display_enter_card());
        incoming.wait().handle<card_insert>([&](const card_insert &mes)
        {
            account = msg.account;
            pin = "";
            interface_hardware.send(display_enter_pin());
            state = &atm::getting_pin;
        })
    }
    void getting_pin();
public:
    void run()
    {
        state = &atm::waiting_for_card;
        try
        {
            for (;;)
            {
                (this->*state)();
            }
        }
        catch (const messaging::close_queue&)
        {

        }
    }
};