/************************************************
 * 该例程是守护进程和看门狗进程的编程实现
************************************************/
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/param.h>  // NOFILE
#include <sys/stat.h>   // umask
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

void childProcessFunc()
{
    FILE* file = NULL;
    time_t t = 0;
    int i = 0;

    // 每隔5秒向test.log报告运行状态
    while (true)
    {
        ++i;
        sleep(5);
        file = fopen("./var/test.log", "a+");
        if (file != NULL)
        {
            t = time(NULL);
            fprintf(file, "i: %d, I am here at %s\n", i, asctime(localtime(&t)));
            fclose(file);
        }

        if (i == 5)
        {
            // 子进程主动退出
            exit(0);
        }
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
            assert(signal(SIGCHLD, forkChildProcess) != SIG_ERR);
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

bool initDaemon()
{
    // 屏蔽一些有关控制终端操作的信号
    // 防止守护进程没有正常运转起来时，因控制终端受到干扰退出或挂起
    assert(signal(SIGINT, SIG_IGN) != SIG_ERR); // 终端中断
    assert(signal(SIGHUP, SIG_IGN) != SIG_ERR); // 连接挂断
    assert(signal(SIGQUIT, SIG_IGN) != SIG_ERR);// 终端退出
    assert(signal(SIGPIPE, SIG_IGN) != SIG_ERR);// 向无读进程的管道写数据
    assert(signal(SIGTTOU, SIG_IGN) != SIG_ERR);// 后台程序尝试写操作
    assert(signal(SIGTTIN, SIG_IGN) != SIG_ERR);// 后台程序尝试读操作
    assert(signal(SIGTERM, SIG_IGN) != SIG_ERR);// 终止

    // [1] 创建一个子进程，父进程退出
    int pid = fork();
    if (pid)
    {
        // 父进程退出
        exit(0);
    }
    else if (pid < 0)
    {
        return false;
    }

    // 子进程继续运行
    
    // [2] 在子进程中创建新的会话，setsid有三个作用
    // a.让进程摆脱原会话的控制
    // b.让进程摆脱原进程组的控制
    // c.让进程摆脱原控制终端的控制
    int ret = setsid();
    if (ret < 0)
    {
        return false;
    }

    // [3] 禁止进程重新打开控制终端
    // 进程已经成为无终端的会话组长，但它可以重新申请打开一个控制终端
    // 可以通过使进程不再成为会话组长来禁止进程重新打开控制终端
    pid = fork();
    if (pid)
    {
        // 结束第一个子进程
        exit(0);
    }
    else if (pid < 0)
    {
        return false;
    }

    // 第二个子进程继续运行

    // [4] 关闭打开的文件描述符
    // 进程从创建它的父进程那里继承了打开的文件描述符，如果不关闭，将会浪费系统资源，
    // 造成进程所在的文件系统无法卸下以及引起无法预料的错误
    for (int i = 0; i < NOFILE; ++i)
    {
        close(i);
    }

    // [5] 改变当前工作目录
    // 进程活动时，其工作目录所在的文件系统不能卸下，一般将工作目录改变到根目录
    ret = chdir("/");
    if (ret < 0)
    {
        return false;
    }

    // [6] 重新设置文件创建掩码
    // 进程从创建它的父进程那里继承了文件创建掩码，它可能修改守护进程所创建的文件的存取位
    // 所以将文件创建掩码清除
    umask(0);

    return true;
}

int main()
{
    // 注意：要编写带有看门狗并且后台运行的程序
    // 需要先初始化守护进程（让该程序成为后台程序）
    // 然后才初始化看门狗进程
    
    // 初始化守护进程
    bool ret = initDaemon();
    if (!ret)
    {
        return 1;
    }

    // 初始化看门狗进程
    ret = initWatchDog();
    if (!ret)
    {
        return 1;
    }

    // 运行子进程代码
    childProcessFunc(); 

    return 0;
}
