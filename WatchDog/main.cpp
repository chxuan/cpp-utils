/************************************************
 * 该例程讲解Linux软件看门狗的优雅编写方法
 *
 * 编写WatchDog有很多种方式：
 * a.一个WatchDog.sh脚本程序
 * b.一个WatchDog.exe可执行程序
 * c.一个可执行程序里面包含WatchDog
 *
 * 本例程就是使用的c方式，通过父进程监控子进程的运行状态来实现的
 * 其中父进程就是子进程（具体的任务进程）的WatchDog
************************************************/
#include "WatchDog.hpp"

void childProcess()
{
    int i = 0;
    while (true)
    {
        ++i;
        printf("i: %d, pid: %d, ppid: %d\n", i, getpid(), getppid());
        if (i == 10)
        {
            // 子进程主动结束
            //exit(0);
            char* p = NULL;
            *p = 1;
        }
        sleep(1);
    }
}

int main()
{
    printf("Main pid: %d\n", getpid());

    // 启动看门狗进程
    bool ret = WatchDog::start(childProcess);
    if (!ret)
    {
        printf("Init watch dog failed\n");
        return 1;
    }

    return 0;
}
