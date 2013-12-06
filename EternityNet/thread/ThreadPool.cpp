#include"ThreadPool.h"
#include"../utilities/LogUtil.h"


namespace ety{

	ThreadPool::ThreadPool()
	{
		ThreadPool(4);	// default create 4 threads base on common CPU thread
	}

	ThreadPool::ThreadPool(int threadNum)
	{
		StartLog("ThreadPool");
		if (mMaxThreads < 1)  mMaxThreads=1;
		mMutexSync.lock();
		this->mMaxThreads = threadNum;
		this->mJoberQueneSize = threadNum;
		mJoberQuene.resize(mMaxThreads, NULL);
		mTailIndex = mHeadIndex = mIncompleteWork = 0;
		mMutexSync.unlock();
	}

	ThreadPool::~ThreadPool()
	{
		mJoberQuene.clear();
	}

	void ThreadPool::init()
	{
		for (int i=0; i<mMaxThreads; i++)
		{
			pthread_t tmpThread;
			pthread_create(&tmpThread, NULL, &ThreadPool::startThreadPool, (void*)this );
			WriteLog("Create %d Thread Successed", tmpThread );
		}
	}

	void ThreadPool::join(int maxSecs /*= 2*/)
	{
		while( mIncompleteWork > 0 )
			sleep(maxSecs);				// 等待所有任务完成

	}

	bool ThreadPool::addJober(Jober* jober)
	{
		mMutexCompletion.lock();
		mIncompleteWork++;
		mMutexCompletion.unlock();

		if ( mIncompleteWork > mJoberQueneSize )
			mAvalidThreads.wait();
		mMutexSync.lock();
		// 如果mIncompleteWork > QueneSize了 增加任务队列大小.
			mJoberQuene[mHeadIndex] = jober;
			WriteLog("Add Jober ID:%d", jober->mJobID);
			if (mJoberQueneSize != 1)
				mHeadIndex = (mHeadIndex + 1) % mJoberQueneSize;
			mAvalidJobs.signal();
		mMutexSync.unlock();
	}

	bool ThreadPool::fetchJober(Jober **jober)
	{
		if ( mIncompleteWork <= 0 )
			mAvalidJobs.wait();
		mMutexSync.lock();
			Jober* aJober = mJoberQuene[mTailIndex];
			WriteLog("====cur Incomplete:%d, TailIndex:%d \n", mIncompleteWork, mTailIndex);
				mJoberQuene[mTailIndex] = NULL;
			*jober = aJober;
			WriteLog("Handle Jober ID:%d .", aJober->mJobID);
			if ( mJoberQueneSize != 1)
				mTailIndex = (mTailIndex + 1) % mJoberQueneSize;

			mMutexCompletion.lock();
				mIncompleteWork--;
			mMutexCompletion.unlock();
			
			mAvalidThreads.signal();
		mMutexSync.unlock();

		return true;
	}

	void* ThreadPool::startThreadPool(void* param)
	{
		Jober* jober = NULL;
		ThreadPool* curThreadPool = (ThreadPool*)param;

		while ( curThreadPool->fetchJober(&jober) )
		{
			if (jober)
			{
				jober->doJob();
				delete jober;
				jober = NULL;
			}
		}
		return 0;
	}

}
