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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void childProcessFunc()
{
    int i = 0;
    while (true)
    {
        ++i;
        printf("i: %d, pid: %d, ppid: %d\n", i, getpid(), getppid());
        if (i == 100)
        {
            // 子进程主动结束
            exit(0);
        }
        sleep(1);
    }
}

void forkChildProcess(int)
{
    int status = 0;
    // 等待子进程中断或终止，释放子进程资源
    // 否则死掉的子进程会变成僵尸进程
    int pid = wait(&status);
    if (pid < 0)
    {
        printf("error: %s\n", strerror(errno));
        return;
    }

    // 如果子进程是由于某种信号退出的，捕获该信号
    if (WIFSIGNALED(status))
    {
        int signalNum = WTERMSIG(status);
        printf("Child process was killed by signal num: %d\n", signalNum);
    }

    // 等待3秒钟重新启动子进程
    sleep(3);

    pid = fork();
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
            // 捕获子进程结束信号
            signal(SIGCHLD, forkChildProcess);
            // 父进程挂起，当有信号来时被唤醒
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

    // 初始化看门狗进程
    bool ret = initWatchDog();
    if (!ret)
    {
        printf("Init watch dog failed\n");
        return 1;
    }

    printf("Init watch dog success...\n");

    // 运行子进程代码
    childProcessFunc(); 

    return 0;
}
