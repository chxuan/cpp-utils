#include "server.hpp"

int main()
{
    event_loop event;

    server s;
    s.start();

    event.loop();
    return 0;
}
