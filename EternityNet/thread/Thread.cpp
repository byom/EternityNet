#include "Thread.h"
#include <stdlib.h>
#include "../utilities/LogUtil.h"

using namespace ety;
using namespace std;

namespace ety{

Thread::Thread(bool isDetached) :mDetached(isDetached) {}

void* Thread::startThread(void* pVoid) {
	WriteLog("start Thread LogInfo --");
	Thread* aThread = static_cast<Thread*>(pVoid);
	assert(aThread);
	aThread->mResult = aThread->run();
	aThread->setCompleted();
	return aThread->mResult;
}

Thread::~Thread() {}

void Thread::start() {
	// init
	int status = pthread_attr_init(&mThreadAttribute);
	if(status) {
		printError("pthread_attr_init failed at", status,
			__FILE__, __LINE__);
		exit(status);
	}

	status = pthread_attr_setscope(&mThreadAttribute,
		PTHREAD_SCOPE_SYSTEM);
	if(status) {
		printError("pthread_attr_setscope failed at", status,
			__FILE__, __LINE__);
		exit(status);
	}

	if(mDetached)
	{
		status = pthread_attr_setdetachstate(&mThreadAttribute,
			PTHREAD_CREATE_DETACHED);	
		if(status) {
			printError("pthread_attr_setdetachstate failed at", status,
				__FILE__, __LINE__);
			exit(status);
		}
	}


	status = pthread_create(&mThreadID, &mThreadAttribute,
		Thread::startThread, (void*)this);	
	if(status) {
		printError("pthread_create failed at", status,
			__FILE__, __LINE__);
		exit(status);
	}

	status = pthread_attr_destroy(&mThreadAttribute);
	if(status) {
		printError("pthread_attr_destroy failed at", status,
			__FILE__, __LINE__);
		exit(status);
	}
}


void* Thread::join() {
	int status = pthread_join(mThreadID, NULL);
	if(status) {
		printError("pthread_join failed at", status,
			__FILE__, __LINE__);
		exit(status);
	}
	return mResult;
}

void Thread::setCompleted() {
	// completion handled by pthread_join()
	mIsCompleted = true;
}

void Thread::printError(char * msg, int status, char* fileName, int lineNumber) {
	cout << msg << " " << fileName << ":" << lineNumber <<"-" << status << endl;
}

}
