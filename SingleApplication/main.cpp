/************************************************
 * 该例程讲解Linux下程序只运行一个实例的编程实现
 *
 * 编写只运行一个实例的程序有很多种方式，比如通过管道
 * 共享内存、文件锁等，主要是要有一个全局flag标志该程序
 * 已经在运行了，本程序使用文件锁来实现单实例
************************************************/
#include "SingleApplication.hpp" 

int main()
{
    if (SingleApplication::isRunning())
    {
        printf("Process is already running\n");
        return 1;
    }

    printf("Process start...\n");
    sleep(5);
    printf("Process end...\n");

    return 0;
}
