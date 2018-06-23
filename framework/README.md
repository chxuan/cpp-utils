framework set
===================


目前该框架集合包括日志框架、网络框架、常用工具库、线程池，之后还会添加db框架、消息队列框架等。

----------


依赖的第三方库
-------------

> - clog依赖log4cpp、utils
> - net-tcpserver依赖boost.asio
> - net-thrift依赖thrift、boost
> - net-rcf依赖RCF、boost
> - utils依赖libuuid、openssl

开发平台
-------------

该框架集合是在CentOS-7-x86_64下开发的，CMake版本是3.4.1，gcc版本是4.8.x。


开发平台搭建
-------------

[developmentkit](https://github.com/chxuan/developmentkit)是该框架集合所依赖的三方库以及三方库的源代码仓库，使用git将[developmentkit](https://github.com/chxuan/developmentkit)克隆到本地计算机，并将这些三方库拷贝到/usr/local下，并在/etc/bashrc添加环境变量。

```bash
export BOOST_INCLUDE_PATH="/usr/local/3rdParty/boost/include"
export BOOST_LIB_PATH="/usr/local/3rdParty/boost/lib"
export THRIFT_INCLUDE_PATH="/usr/local/3rdParty/thrift/include"
export THRIFT_LIB_PATH="/usr/local/3rdParty/thrift/lib"
export UUID_INCLUDE_PATH="/usr/local/3rdParty/uuid/include"
export UUID_LIB_PATH="/usr/local/3rdParty/uuid/lib"
export OPENSSL_INCLUDE_PATH="/usr/local/3rdParty/ssl/include"
export OPENSSL_LIB_PATH="/usr/local/3rdParty/ssl/lib"
export LOG4CPP_INCLUDE_PATH="/usr/local/3rdParty/log4cpp/include"
export LOG4CPP_LIB_PATH="/usr/local/3rdParty/log4cpp/lib"
export RCF_INCLUDE_PATH="/usr/local/3rdParty/RCF/include"
export RCF_LIB_PATH="/usr/local/3rdParty/RCF/lib"
export LD_LIBRARY_PATH="$RCF_LIB_PATH:$LOG4CPP_LIB_PATH:$OPENSSL_LIB_PATH:$UUID_LIB_PATH:$THRIFT_LIB_PATH:$BOOST_LIB_PATH:$LD_LIBRARY_PATH"
```

编辑完/etc/bashrc后执行以下命令，让更改立即生效。
```bash
sudo source /etc/bashrc
```


编译framework
-------------

```bash
cd framework
cmake .
make
make install
```

其中make将会自动编译出静态库和动态库并输出到各自项目的lib文件夹下，测试程序（例子程序）的可执行文件会输出到bin文件夹下，make install默认将编译好的静态库、动态库以及头文件安装到/usr/local/framework/目录下，编译好framework后，需要设置环境变量以便后续使用framework进行开发。


使用framework
-------------

###1.使用clog
```c++
//main.cpp
#include <iostream>
#include <string>
#include "LogWrapper.h"

int main()
{
    int a = 1;
    int b = 2;
    std::string str = "Hello world";

    // C风格
    logError("Error log");
    logWarn("Warn log");
    logInfo("a + b = %d", a + b);

    // C++风格
    logError() << "Hello world";
    logWarn() << "Hello world";
    logDebug() << "message: " << str;

    return 0;
}
```
正如你所看到的，使用clog提供的API很简单，有C风格和C++风格格式化输出方式，clog会同时将日志输出到屏幕和日志文件(logs/exename.log)，下面是输出日志。
```
2016-01-24 14:35:27,181: [ERROR] : main.cpp main(19) Error log
2016-01-24 14:35:27,181: [WARN ] : main.cpp main(20) Warn log
2016-01-24 14:35:27,181: [INFO ] : main.cpp main(21) a + b = 3
2016-01-24 14:35:27,182: [ERROR] : main.cpp main(24) Hello world
2016-01-24 14:35:27,182: [WARN ] : main.cpp main(25) Hello world
2016-01-24 14:35:27,182: [DEBUG] : main.cpp main(26) message: Hello world
```

###2.使用net-rcf
net-rcf是基于RCF（Remote Call Framework by Delta V Software）的库，其中net-rcf提供RPC（远程过程调用）和发布/订阅模式的通信方式，下面是RPC和发布/订阅模式的使用方式。

####使用RPC通信方式
要使用RPC，首先要定义客户端和服务器端的通信协议。
```c++
//RPCProtocolDefine.h
#include <RCF/RCF.hpp>
#include "PeopleInfoMessage.h"

RCF_BEGIN(I_RPCMessageHandler, "I_RPCMessageHandler")
    RCF_METHOD_R2(bool, queryPeopleInfoByID, int, PeopleInfoMessage&)
RCF_END(I_RPCMessageHandler)
```
其中queryPeopleInfoByID函数就是客户端向服务器发起请求用户信息的函数，下面是服务器端的代码。
```c++
//Server.cpp
#include <assert.h>
#include <iostream>
#include "RPCProtocolDefine.h"
#include "RCFServerWrapper.hpp"

class RCFMessageHandler
{
public:
    bool queryPeopleInfoByID(int id, PeopleInfoMessage& peopleInfo)
    {
        if (id == 1000)
        {
            peopleInfo.m_name = "Jack";
            peopleInfo.m_age = 24;
            
            return true;
        }

        return false;
    }
};

int main()
{
    RCFMessageHandler rcfMessageHandler;
    RCFServerWrapper<I_RPCMessageHandler> server(50002);

    bool ok = server.start(rcfMessageHandler);
    assert(ok);
    
    std::cin.get();
    
    ok = server.stop();
    assert(ok);

    return 0;
}
```
其中RCFMessageHandler类是服务器端进行消息处理的类，接下来是客户端的代码。
```c++
//Client.cpp
#include <iostream>
#include "RPCProtocolDefine.h"
#include "RCFClientWrapper.hpp"

int main()
{
    RCFClientWrapper<I_RPCMessageHandler> client("127.0.0.1", 50002);

    try
    {
        PeopleInfoMessage peopleInfo;
        int id = 1000;

        bool ok = client.rcfClientObject()->queryPeopleInfoByID(id, peopleInfo);
        if (ok)
        {
            std::cout << "name: " << peopleInfo.m_name << std::endl;
            std::cout << "age: " << peopleInfo.m_age << std::endl;
        }
    }
    catch (const RCF::Exception& e)
    {
        std::cout << "Error: " << e.getErrorString() << std::endl;
    }

    return 0;
}
```
####使用发布/订阅通信方式
要使用发布/订阅通信方式，首先也要定义发布端和订阅端的通信协议。
```c++
//PubSubProtocolDefine.h
#include <RCF/RCF.hpp>
#include <string>

RCF_BEGIN(I_PubSubMessageHandler, "I_PubSubMessageHandler")
    RCF_METHOD_V1(void, pushNews, const std::string&)
RCF_END(I_PubSubMessageHandler)
```
发布端调用pushNews将news发送到订阅端，下面是发布端的代码。
```c++
//Publisher.cpp
#include <assert.h>
#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include "PubSubProtocolDefine.h"
#include "RCFPublisherWrapper.hpp"

bool handleSubscriberConnect(RCF::RcfSession& session, const std::string& topicName)
{
    (void)session;
    (void)topicName;
    return true;
}

void handleSubscriberDisconnect(RCF::RcfSession& session, const std::string& topicName)
{
    (void)session;
    (void)topicName;
}

int main()
{
    RCFPublisherWrapper<I_PubSubMessageHandler> server(50003);
    bool ok = server.start();
    assert(ok);

    PublisherParam param;
    param.m_topicName = "news";
    param.m_onSubscriberConnect = handleSubscriberConnect;
    param.m_onSubscriberDisconnect = handleSubscriberDisconnect;
    ok = server.createPublisher(param);
    assert(ok);

    std::string newsDescription = "Good news";
    while (true)
    {
        server.rcfPublishObject(param.m_topicName)->publish().pushNews(newsDescription);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    }

    return 0;
}
```
发布端创建了“news“主题，订阅端也将订阅该主题，接下来是订阅端的代码。
```c++
//Subscriber.cpp
#include <assert.h>
#include <iostream>
#include <string>
#include "PubSubProtocolDefine.h"
#include "RCFSubscriberWrapper.hpp"

class RCFMessageHandler
{
public:
    void pushNews(const std::string& newsInfo)
    {
        std::cout << newsInfo << std::endl;
    }
};

int main()
{
    RCFSubscriberWrapper<I_PubSubMessageHandler> server;
    RCFMessageHandler rcfMessageHandler;

    bool ok = server.start();
    assert(ok);

    SubscriptionParam param;
    param.m_ip = "127.0.0.1";
    param.m_port = 50003;
    param.m_topicName = "news";
    ok = server.createSubscription(rcfMessageHandler, param);
    assert(ok);

    std::cin.get();

    return 0;
}
```

###3.使用threadpool
```c++
//main.cpp
#include <iostream>
#include "CThreadManage.h"
#include "CRealJob.h"

void doTask(void* jobData)
{
    std::cout << "Hello world" << std::endl;
    boost::this_thread::sleep_for(boost::chrono::milliseconds(50));
}

int main()
{
    CThreadManagePtr manage(new CThreadManage);
    manage->initThreadNum(10);

    for (int i = 0; i < 100; ++i)
    {
        CRealJobPtr job(new CRealJob(boost::bind(doTask, _1), NULL));
        manage->run(job);
    }

    boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
    std::cout << "##############END###################" << std::endl;
    return 0;
}
```
该线程池是一个通用的线程池框架，CThreadManage作为线程池的一个包装类，该例子创建了10个线程并且并发执行了100个任务，该任务最终体现为回调doTask函数，调用run函数时并没有真正的执行任务，而是将任务放入任务队列，然后通知空闲线程来取走任务，直到任务队列为空，main函数return时，线程池将等待正在执行的任务，直到任务执行完成并放弃执行任务队列的任务。








