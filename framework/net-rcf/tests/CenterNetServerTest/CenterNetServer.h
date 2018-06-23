/*************************************************************************
	> File Name: CenterNetServer.h
	> Author: 
	> Mail: 
	> Created Time: 2016年01月10日 星期日 20时30分04秒
 ************************************************************************/

#ifndef _CENTERNETSERVER_H
#define _CENTERNETSERVER_H

#include "RPCProtocolDefine.h"
#include "RCFServerWrapper.hpp"
#include "RCFClientWrapper.hpp"

class CenterNetServer;

class RCFMessageHandler
{
public:
    RCFMessageHandler(CenterNetServer* centerNetServer);
    ~RCFMessageHandler();

public:
    bool queryPeopleInfoByID(int id, PeopleInfoMessage& peopleInfo);

private:
    CenterNetServer*            m_centerNetServer;
};

class CenterNetServer
{
public:
    CenterNetServer();
    ~CenterNetServer();

public:
    bool start();
    bool stop();

public:
    typedef boost::shared_ptr<RCFServerWrapper<I_RPCMessageHandler> > RCFServerWrapperPtr;
    RCFServerWrapperPtr         m_rcfServerWrapper;

    typedef boost::shared_ptr<RCFClientWrapper<I_RPCMessageHandler> > RCFClientWrapperPtr;
    RCFClientWrapperPtr         m_rcfDBServerClientWrapper;

private:
    typedef boost::shared_ptr<RCFMessageHandler> RCFMessageHandlerPtr;
    RCFMessageHandlerPtr        m_rcfMessageHandler;
};

#endif
