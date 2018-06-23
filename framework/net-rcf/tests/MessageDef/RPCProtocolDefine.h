#ifndef _RPCPROTOCOLDEFINE_H
#define _RPCPROTOCOLDEFINE_H

#include <RCF/RCF.hpp>
#include "PeopleInfoMessage.h"

RCF_BEGIN(I_RPCMessageHandler, "I_RPCMessageHandler")
    RCF_METHOD_R2(bool, queryPeopleInfoByID, int, PeopleInfoMessage&)
RCF_END(I_RPCMessageHandler)

#endif
