#ifndef _ETERNITY_NONCOPYABLE_H_
#define _ETERNITY_NONCOPYABLE_H_
/*****************************************************************************\
 *	This file is part of EternityNet
 *	@file
 *	@module
 *	@author		Yangwl
 *	@date		2013-8-12
 *	@email      39441733@qq.com  & ywlfield@gmail.com
 *	@brief      token cant copyable class        
 *	@change
 *								\*****************************************************************************/

namespace ety    // 好拼
{

class NonCopyable
{
protected:
	NonCopyable(){}
	~NonCopyable(){}

private:
	NonCopyable(const NonCopyable& );
	const NonCopyable& operator=(const NonCopyable& );

};	

}
#endif
