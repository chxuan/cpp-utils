#include "BindCPU.hpp"

int main()
{
    printf("*****Process bind CPU sample*****\n");
    unsigned int cpuNum = BindCPU::systemCPUNum();
    printf("Current system has %u CPU(s)\n", cpuNum);

    std::vector<unsigned int> runningCPUVector;
    if (!BindCPU::currentProcessAffinity(runningCPUVector))
    {
        printf("Get current process was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector)
    {
        printf("Current process is running at %u CPU\n", iter);
    }

    std::vector<unsigned int> needBindCPUVector {0, 2};
    if (!BindCPU::setCurrentProcessAffinity(needBindCPUVector))
    {
        printf("Current process bind CPU failed\n");
        return 1;
    }

    printf("Current process bind CPU success\n");

    runningCPUVector.clear();
    if (!BindCPU::currentProcessAffinity(runningCPUVector))
    {
        printf("Get current process was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector)
    {
        printf("Current process is running at %u CPU\n", iter);
    }

    printf("\n*****Thread bind CPU sample*****\n");
    runningCPUVector.clear();
    if (!BindCPU::currentThreadAffinity(runningCPUVector))
    {
        printf("Get current thread was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector)
    {
        printf("Thread %lu is running at %u CPU\n", pthread_self(), iter);
    }

    needBindCPUVector.clear();
    needBindCPUVector.push_back(1);
    if (!BindCPU::setCurrentThreadAffinity(needBindCPUVector))
    {
        printf("Current thread bind CPU failed\n");
        return 1;
    }

    printf("Thread %lu bind CPU success\n", pthread_self());

    runningCPUVector.clear();
    if (!BindCPU::currentThreadAffinity(runningCPUVector))
    {
        printf("Get current thread was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector)
    {
        printf("Thread %lu is running at %u CPU\n", pthread_self(), iter);
    }

    return 0;
}
