#ifndef _ETERNITY_SINGLETON_H_
#define _ETERNITY_SINGLETON_H_
/*****************************************************************************\
 *	This file is part of EternityNet
 *	@file		singleton.h
 *	@module
 *	@author		Yangwl
 *	@date		2013-8-12
 *	@email      39441733@qq.com  & ywlfield@gmail.com
 *	@brief      单件模板类 , 不是线程安全的. 
 *				如果想在多线程中使用, 可以在Instance()函数中添加自动锁来实现.
 *	@change
 *	@usage		class Test{ ... };
 *	
 *	typedef Eternity::Singleton<Test> TestSingleton;;   // Global declaration
 *	TestSingleton::Instance().function();
 *
 *																					\*****************************************************************************/

namespace ety
{

	template<typename T>
	class Singleton{
	public:
		static T& Instance()
		{
			if ( 0 == s_pSingleton )
			{
				s_pSingleton = new(T)();
				atexit(destroy);
			}
			return *s_pSingleton;
		}
	protected:
		Singleton(){}
		virtual ~Singleton(){}
													
	private:
		Singleton(const Singleton& ){}
		Singleton& operator=(const Singleton& ){}

		static void destroy()
		{
			if ( 0 != s_pSingleton )
			{
				delete(s_pSingleton);
				s_pSingleton = 0;
			}
		}
		static T* volatile s_pSingleton;
	};

	template<typename T>
	T* volatile Singleton<T>::s_pSingleton = 0;

}

#endif


//class Test{
//public:
//	void printsth(){
//		printf("singleton_info");
//	}
//};
//
//typedef Eternity::Singleton<Test> TestSingleton;
//TestSingleton::Instance().printsth();
