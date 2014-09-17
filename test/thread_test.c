#include "log.h"
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
/*
 * 测试是否多线程安全
 * */
bool quit = false;
void signal_handler(int sig){
	switch(sig){
		case SIGTERM:
		case SIGINT:
			quit = true;
			break;
	}
	printf("bingo sig\n");
}

void* test01(void *)
{
    int i;
	char _strbuf[200*1024];

	char *_log_str = "You got something wrong here";	
	for(i = 0; i < 1; i++)
	{
		strncat(_strbuf, _log_str, strlen(_log_str));
	}

    for(i=0;i<1000000000;i++)
	{
		//测试日志是否立即写入到文件
		sleep(1);
		if(0 == (i% 5)) 
            LOG_NOTICE("%s [value:%d]", _strbuf, i);
        else if(1 == i % 5)
            LOG_DEBUG("%s [value:%d]", _strbuf, i); 
        else if (2 == i % 5)
            LOG_TRACE("%s [value:%d]", _strbuf, i);
        else if (3 == i % 5)
            LOG_WARN("%s [value:%d]", _strbuf, i);
        else    
            LOG_ERROR("%s [value:%d]", _strbuf, i);	
		if(quit)
			break;
    }
}

int main()
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
	log_init(LL_TRACE, "session", "./");
	
	pthread_t pid[20];
	int i = 0;
	int ret = 0;
	for(; i < 20; i++)
	{
		ret = pthread_create(&pid[i], NULL, test01, NULL);
		MACRO_WARN_RET(0 != ret, -1, "pthread_create error[ret:%d]", ret)
	}
	for(i = 0; i < 20; i++)
	{
		pthread_join(pid[i], NULL);
	}
		
}
