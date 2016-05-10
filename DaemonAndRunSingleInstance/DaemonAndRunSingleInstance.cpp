/************************************************
 * 该例程讲解Linux下守护进程只运行一个实例的编程实现
************************************************/
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/param.h>  // NOFILE
#include <sys/stat.h>   // umask
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string>

#ifndef PATH_MAX
#define PATH_MAX 1024   // 默认最大路径长度
#endif

std::string currentExeName()
{
    char buf[PATH_MAX] = {'\0'};

    int ret = readlink("/proc/self/exe", buf, PATH_MAX);
    if (ret < 0 || ret >= PATH_MAX)
    {
        return "";
    }

    std::string path(buf);
    int pos = path.find_last_of("/");
    if (pos == -1)
    {
        return "";
    }

    path = path.substr(pos + 1, path.size() - 1);

    return path;
}

bool runSingleInstance()
{
    // 获取当前可执行文件名
    std::string processName = currentExeName();
    if (processName.empty())
    {
        exit(1);
    }

    // 打开或创建一个文件
    std::string filePath = std::string("/var/run/") + processName + ".pid";
    int fd = open(filePath.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        printf("Open file failed, error : %s", strerror(errno));
        exit(1);
    }

    // 将该文件锁定
    // 锁定后的文件将不能够再次锁定
    struct flock fl;
    fl.l_type = F_WRLCK; // 写文件锁定
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    int ret = fcntl(fd, F_SETLK, &fl);
    if (ret < 0)
    {
        if (errno == EACCES || errno == EAGAIN)
        {
            printf("%s already locked, error: %s\n", filePath.c_str(), strerror(errno));
            close(fd);
            return false;
        }
    }

    // 锁定文件后，将该进程的pid写入文件
    char buf[16] = {'\0'};
    sprintf(buf, "%d", getpid());
    ftruncate(fd, 0);
    ret = write(fd, buf, strlen(buf));
    if (ret < 0)
    {
        printf("Write file failed, file: %s, error: %s\n", filePath.c_str(), strerror(errno));
        close(fd);
        exit(1);
    }

    // 函数返回时不需要调用close(fd)
    // 不然文件锁将失效
    // 程序退出后kernel会自动close
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
    // 初始化守护进程
    bool ret = initDaemon();
    if (!ret)
    {
        printf("Init daemon failed\n");
        return 1;
    }

    if (!runSingleInstance())
    {
        printf("Process is already running\n");
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
