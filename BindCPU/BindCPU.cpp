#include <unistd.h>
#ifndef __USE_GNU
#define __USE_GNU   // 为了使用SET_SET()等宏定义，但unistd.h里面好像已经定义了
#endif
#include <sched.h>
#include <stdio.h>

unsigned int systemCpuNum()
{
    return sysconf(_SC_NPROCESSORS_CONF);
}

int main()
{
    unsigned int cpuNum = systemCpuNum();
    printf("Current system has %u CPU(s)\n", cpuNum);

    cpu_set_t cpuSet;
    CPU_ZERO(&cpuSet);

    return 0;
}
