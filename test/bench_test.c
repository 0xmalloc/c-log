#include "log.h"
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*
 * 单线程压力测试
 * */
int common_test()
{
	log_debug("testing write log befor log_init: %s\n", "haha");
}

void test01()
{
    //init  log
	//log_init(LL_TRACE, "mysql", "./log");
	log_init(LL_TRACE, "bench", "./");
    
	int i;
	char _strbuf[1024*1024*4];

	char *_log_str = "You got something wrong here";	
	for(i = 0; i < 10000; i++)
	{
		strncat(_strbuf, _log_str, strlen(_log_str));
	}
	printf("Log size of each log:%d", strlen(_strbuf));	
	for(i = 0; i < 1000000000; i++)
	{
		log_notice("%s [value:%d]\n", _strbuf, i);
    }
}

int main()
{
    test01();
}
