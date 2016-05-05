/************************************************
 * 该例程讲解Linux守护进程的编程方法
************************************************/
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool initDaemon()
{
    // 屏蔽一些有关控制终端操作的信号
    // 防止守护进程没有正常运转起来时，因控制终端受到干扰退出或挂起
    signal(SIGINT, SIG_IGN); // 终端中断
    signal(SIGHUP, SIG_IGN); // 连接挂断
    signal(SIGQUIT, SIG_IGN);// 终端退出
    signal(SIGPIPE, SIG_IGN);// 向无读进程的管道写数据
    signal(SIGTTOU, SIG_IGN);// 后台程序尝试写操作
    signal(SIGTTIN, SIG_IGN);// 后台程序尝试读操作
    signal(SIGTERM, SIG_IGN);// 终止
    signal(SIGCHLD, SIG_IGN);// 忽略子进程退出信号，防止僵尸进程产生

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
    bool ret = initDaemon();
    if (!ret)
    {
        return 1;
    }

    FILE* file = NULL;
    time_t t = 0;

    // 每隔10秒向test.log报告运行状态
    while (true)
    {
        sleep(10);
        file = fopen("./var/test.log", "a+");
        if (file != NULL)
        {
            t = time(NULL);
            fprintf(file, "I am here at %s\n", asctime(localtime(&t)));
            fclose(file);
        }
    }

    return 0;
}

