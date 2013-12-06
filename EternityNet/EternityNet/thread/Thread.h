#ifndef _ETERNITY_THREAD_H_
#define _ETERNITY_THREAD_H_
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

#include <iostream>
#include <pthread.h>
#include <cassert>
#include <error.h>


namespace ety    // บรฦด
{
using namespace ety;
/////// code /////

class Thread {
public:
	Thread(bool isDetached = false);
	virtual ~Thread();
	void start();
	void* join();
private:

	pthread_t mThreadID;
	bool mDetached;
	bool mIsCompleted;
	pthread_attr_t mThreadAttribute;

	Thread(const Thread&);
	const Thread& operator=(const Thread&);
	
	void setCompleted();
	void* mResult;
	virtual void* run() {}
	static void* startThread(void* pVoid);

	void printError(char * msg, int status, char* fileName, int lineNumber);
};

}
#endif
