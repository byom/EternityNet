#include "Acceptor.h"
#include "Connection.h"
#include "../utilities/LogUtil.h"

// EF_TEMP 把这个移到LogUtil.h里面吧
#define PrintErr( x ) 	if ( ( x ) < 0 ) \
	{	\
		WriteErrLog("[File:%s,Line:%d] Error", __FILE__, __LINE__);	\
	}	\

using namespace ety;

Acceptor::Acceptor(int port):
  mAddr(port)
, mSockListen(INVALID_HANDLE)
, mSockConnect(INVALID_HANDLE)
, mIsEstablish(false)
{

}

Acceptor::Acceptor():
  mAddr(INVALID_PORT)
, mSockListen(INVALID_HANDLE)
, mSockConnect(INVALID_HANDLE)
, mIsEstablish(false)
{
	
}

Acceptor::~Acceptor()
{
	
}

void Acceptor::Listen()
{
	mSockListen.Init();
	mSockListen.SetNonBlocking(true);
	mSockListen.SetReuseAddr(true);
	mSockListen.Bind(mAddr);
	mSockListen.Listen();
}

ConnectionPtr Acceptor::Accept()
{
	IpAddress remote(INVALID_PORT);
	int fd = mSockListen.Accept(remote);
	PrintErr( fd );

	WriteLog("Accepted Connect from fd:%d.", fd );

	mIsEstablish = true;
	ConnectionPtr conn(new Connection(remote, mAddr, fd));

	return conn;
}
