#include "Thread.h"
#include "../utilities/LogUtil.h"
#include <stdio.h>


int s = 0;

class communicatingThread: public ety::Thread {
	public:
			communicatingThread(int ID) : myID(ID) {}
			virtual void* run();
	private:
			int myID;
};

void* communicatingThread::run() 
{
		cout << "Thread " << myID << " is running!" << endl;
		// increment s by million times
		for (int i = 0; i < 1000000; i++) s+=1;
		return 0;
}

int main() {
		StartLog("Thread");
		communicatingThread thread1(1);
		communicatingThread thread2(1);
		thread1.start();
		thread2.start();
		thread1.join();
		thread2.join();

		cout<<"s = "<< s <<endl;

		return 0;

}
