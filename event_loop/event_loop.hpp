#pragma once

#include <unistd.h>
#include <signal.h>
#include <iostream>

class event_loop
{
public:
    event_loop()
    {
        set_sigint_handle();
    }

    void loop()
    {
        sleep(-1);
    }

    static bool is_active() 
    {
        return active_;
    }

private:
    static void sigint_handle(int sig)
    {
        std::cout << "end, sig: " << sig << std::endl;
        active_ = false;
    }

    void set_sigint_handle()
    {
        struct sigaction act;
        act.sa_handler = sigint_handle;
        act.sa_flags = SA_INTERRUPT;

        sigaction(SIGINT, &act, nullptr);
    }

private:
    static bool active_;
};

bool event_loop::active_ = true;
