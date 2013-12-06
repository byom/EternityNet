#ifndef _ETERNITY_RWLOCK_H_
#define _ETERNITY_RWLOCK_H_
/*****************************************************************************\
 *	This file is part of EternityNet
 *	@file
 *	@module
 *	@author		Yangwl
 *	@date		2013-8-12
 *	@email      39441733@qq.com  & ywlfield@gmail.com
 *	@brief              
 *	@change
 \*****************************************************************************/

#include <pthread.h>
#include "../utilities/NonCopyable.h"

namespace ety    // 好拼
{
using namespace ety;

class RWLock : private NonCopyable
{
public:
	unsigned int rdCount;
	unsigned int wrCount;

	RWLock():rdCount(0), wrCount(0)
	{
		::pthread_rwlock_init(&m_rwlock, NULL);
	}
	~RWLock()
	{
		::pthread_rwlock_destroy(&m_rwlock);
	}

	void rdlock()
	{
		::pthread_rwlock_rdlock(&m_rwlock);
		rdCount++;
	}

	void wrlock()
	{
		::pthread_rwlock_wrlock(&m_rwlock);
		rdCount++;
		wrCount++;
	}

	void unlock()
	{
		::pthread_rwlock_unlock(&m_rwlock);
		rdCount--;
	}	

private:
	pthread_rwlock_t m_rwlock;

};

}
#endif
