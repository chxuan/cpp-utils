/************************************************
 * 该例程讲解Linux守护进程的编程方法
************************************************/
#include "Daemon.hpp"

int main()
{
    // 启动守护进程
    bool ret = Daemon::start();
    if (!ret)
    {
        printf("Init daemon failed\n");
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

