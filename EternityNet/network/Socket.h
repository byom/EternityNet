#ifndef _ETERNITY_SOCKET_H_
#define _ETERNITY_SOCKET_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief              
	@change
\*****************************************************************************/
#include "IpAddress.h"
#include "../utilities/NonCopyable.h"
#include "../utilities/LogUtil.h"

#define INVALID_HANDLE   -1

using namespace ety;
namespace ety    // 好拼
{
class Socket:public NonCopyable
{
public:
	Socket():mSockfd(INVALID_HANDLE){}

	explicit Socket(int fd):mSockfd(fd){}

	~Socket();

	int Init();

	void Close();

	int Bind(IpAddress& addr);

	int Connect(IpAddress& addr);

	int Listen();

	int Accept(IpAddress& addr);

	int GetSocketfd(){ return mSockfd; }

	int GetSocketError(int sockfd);

	void Shutdown(int sd);

	const IpAddress GetLocalAddress();

	const IpAddress GetPeerAddress();


	int SetIntOpt(int opt, bool b);

	// 允许套接口和一个已在使用中的地址捆绑
	int SetReuseAddr(bool b);

	// 在send(),recv()过程中有时由于网络状况等原因，发收不能预期进行,而设置收发时限：
	int SetTimeOpt(int opt, int ms);

	// 禁用 Nagle算法
	int SetTcpNoDelay(bool b);

	// 设置 残留在套接口缓冲区中的数据处理方式.
	int SetSoLinger(bool b, int sec);

	// 设置阻塞模式.
	int SetNonBlocking(bool b);

private:
	int mSockfd;
};
}
#endif