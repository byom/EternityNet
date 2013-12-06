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
namespace ety    // ��ƴ
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

	// �����׽ӿں�һ������ʹ���еĵ�ַ����
	int SetReuseAddr(bool b);

	// ��send(),recv()��������ʱ��������״����ԭ�򣬷��ղ���Ԥ�ڽ���,�������շ�ʱ�ޣ�
	int SetTimeOpt(int opt, int ms);

	// ���� Nagle�㷨
	int SetTcpNoDelay(bool b);

	// ���� �������׽ӿڻ������е����ݴ���ʽ.
	int SetSoLinger(bool b, int sec);

	// ��������ģʽ.
	int SetNonBlocking(bool b);

private:
	int mSockfd;
};
}
#endif