#ifndef _WATCHDOG_H
#define _WATCHDOG_H

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <functional>

class WatchDog
{
public:
    static bool start(const std::function<void()>& childProcess)
    {
        m_childProcess = childProcess;

        int pid = fork();
        if (pid)
        {
            // 父进程一直监视子进程的运行状态
            while (true)
            {
                // 捕获子进程结束信号
                assert(signal(SIGCHLD, forkChildProcess) != SIG_ERR);
                // 父进程挂起，当有信号来时被唤醒
                pause();
            }
        }
        else if (pid < 0)
        {
            return false;
        }

        if (m_childProcess != nullptr)
        {
            m_childProcess();
        }
        return true;
    }

private:
    static void forkChildProcess(int)
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

        // 检测是否生成了core文件
        if (WCOREDUMP(status))
        {
            printf("Child process core dump file generated\n");
        }

        // 等待3秒钟重新启动子进程
        sleep(3);

        pid = fork();
        if (pid == 0)
        {
            printf("Fork new child process\n");
            if (m_childProcess != nullptr)
            {
                m_childProcess();
            }
        }
    }

private:
    static std::function<void()> m_childProcess;
};

std::function<void()> WatchDog::m_childProcess = nullptr;

#endif
