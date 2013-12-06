#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "ThreadInc.h"

using namespace ety;
pid_t gettid()
{
	return syscall(SYS_gettid);
}

void printids(const char *s)
{
	pid_t	  pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid_l %lu tid_u (ox%x)\n", s, (unsigned int)pid, tid, gettid(), (unsigned int)tid);
}
Mutex m;
void* thr_fn(void *arg)
{
	AutoMutex l(m);
	printf("Curent Thread:%d; ===============================\n", gettid());
	for(int i = 0; i < 5; i++)
	{
		sleep(1);
		printf("print msg i = %d;\n", i);	
	}

	return NULL;
}


Mutex m2;
Condition cond;
int condInt = 0;
void* waitFn(void *arg)
{
	m2.lock();
	if (condInt != 1)
	  cond.wait(m2);
	printf("----waitFn done----\n");
	m2.unlock();
}
void* firstFn(void *arg)
{
	m2.lock();
	condInt = 1;
	cond.signal();
	printf("----First Done----\n");
	m2.unlock();
}

pthread_t ntid;
int main(void)
{

	// test Condition	
	int err;
	pthread_t ntid;
	err = pthread_create(&ntid, NULL, waitFn, NULL);
	if (err != 0 ){
		fprintf(stderr, "can't create thread : %s\n", strerror(err));
		exit(1);
	}
	sleep(2);
	err = pthread_create(&ntid, NULL, firstFn, NULL);
	if (err != 0 ){
		fprintf(stderr, "can't create thread : %s\n", strerror(err));
		exit(1);
	}

	sleep(2);
	// test Mutex
	for ( int i = 0; i < 5; i++){
	int err;
	pthread_t ntid;
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0 ){
		fprintf(stderr, "can't create thread : %s\n", strerror(err));
		exit(1);
	}
	}
	printids("main thread:");

	sleep(30);

	return 0;
}
