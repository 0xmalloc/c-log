#include "log.h"
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
/*
 * 基本功能测试
 */
int common_test()
{
	log_debug("testing write log befor log_init: %s\n", "haha");
}

void test01()
{
	//测试init 之前调用log_wwarn的结果
	common_test();
    //init  log
	//log_init(LL_TRACE, "mysql", "./log");
	log_init(LL_TRACE, "mysql", "./");
    
	int i;
	char _strbuf[200*1024];

	char *_log_str = "You got something wrong here";	
	for(i = 0; i < 1; i++)
	{
		strncat(_strbuf, _log_str, strlen(_log_str));
	}
	common_test(); 
	
	for(i = 0; i < 1000000000; i++)
	{
		//sleep(1);
		if(0 == (i% 5))
			log_notice("%s [value:%d]\n", _strbuf, i);
		else if(1 == i % 5)
			log_debug("%s [value:%d]\n", _strbuf, i); 
		else if (2 == i % 5)
			log_trace("%s [value:%d]\n", _strbuf, i);
		else if (3 == i % 5)
			log_warn("%s [value:%d]\n", _strbuf, i);
		else 
			log_error("%s [value:%d]\n", _strbuf, i);
    }
}

int main()
{
    test01();
		
}
