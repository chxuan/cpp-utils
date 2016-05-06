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
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

void childProcessFunc()
{
    int i = 0;
    while (true)
    {
        ++i;
        printf("i: %d, pid: %d, ppid: %d\n", i, getpid(), getppid());
        if (i == 100)
        {
            exit(0);
        }
        sleep(1);
    }
}

void forkChildProcess(int)
{
    int status = 0;
    wait(&status);

    if (WIFSIGNALED(status))
    {
        int signalNum = WTERMSIG(status);
        printf("Signal num: %d\n", signalNum);
    }

    sleep(3);
    int pid = fork();
    if (pid == 0)
    {
        printf("Fork new child process\n");
        childProcessFunc();
    }
}

bool initWatchDog()
{
    int pid = fork();
    if (pid)
    {
        // 父进程一直监视子进程的运行状态
        while (true)
        {
            signal(SIGCHLD, forkChildProcess);
            pause();
        }
    }
    else if (pid < 0)
    {
        return false;
    }

    return true;
}

int main()
{
    printf("Main pid: %d\n", getpid());
    printf("Init watch dog\n");

    bool ret = initWatchDog();
    if (!ret)
    {
        return 1;
    }

    // 运行子进程代码
    childProcessFunc(); 

    return 0;
}
