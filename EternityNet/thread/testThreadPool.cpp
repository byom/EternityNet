#include "ThreadPool.h"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace ety;

#define SafeRealese(x) \
{ if ( x ) { delete (x); (x) = 0; } }


class SampleJober: public ety::Jober
{
public:
	SampleJober(int id):Jober(id){}
	~SampleJober(){};

	unsigned virtual doJob()
	{
		printf("JoberID:%d doing now!!\n", mJobID);
		return 0;
	}

};

int main(){

ThreadPool* pPool = new ThreadPool(5);
pPool->init();
	for (int i = 0; i < 10; i++)
	{
		SampleJober* pJob = new SampleJober(i);
		pPool->addJober( pJob );
	}

pPool->join();

SafeRealese( pPool );

return 0;
}
