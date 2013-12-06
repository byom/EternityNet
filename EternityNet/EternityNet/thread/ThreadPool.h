#ifndef _ETERNITY_THREADPOOL_H_
#define _ETERNITY_THREADPOOL_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      ����������е��̳߳� , based on worker quene 
				���ݽ�����joberΪָ��, jober���������ڻ���ִ������������̳߳��ͷ�
				�����������ڶ���ʱ
	@change
\*****************************************************************************/
#include <iostream>
#include <vector>

#include"ThreadInc.h"

using namespace std;
using namespace ety;

namespace ety    // ��ƴ
{
/////// code /////
class Jober{
public:

	Jober(int id):mJobID(id){}
	virtual ~Jober(){}

	unsigned virtual doJob()
	{
		return 0;
	}

	int mJobID;

};

class ThreadPool{
public:
	ThreadPool();
	ThreadPool(int threadNum);
	virtual ~ThreadPool();

	void init();
	void join(int maxSecs = 2);

	bool addJober(Jober* jober);
	bool fetchJober(Jober **jober);

	static void* startThreadPool(void* param);

	Mutex       mMutexSync;
	Mutex       mMutexCompletion;

private:
	int         mMaxThreads;
	Condition   mCond;
	Condition   mAvalidJobs;
	Condition   mAvalidThreads;

	vector<Jober *> mJoberQuene;
	int         mHeadIndex;
	int         mTailIndex;

	int         mIncompleteWork;
	int         mJoberQueneSize;

};

}
#endif
