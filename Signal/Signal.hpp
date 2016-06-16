#include <signal.h>
#include <functional>
#include <unordered_map>

namespace
{
std::unordered_map<int, std::function<void()>> signalMap;
void handleSignal(int sig)
{
    signalMap[sig]();
}
}

class Signal
{
public:
    static void signal(int sig, const std::function<void()>& func)
    {
        signalMap.emplace(sig, func);
        ::signal(sig, handleSignal);
    }
};
