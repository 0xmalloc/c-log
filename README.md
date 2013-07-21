c-log
=====

a fast and stable log lib for C/C++ language

you can use  "sh build.sh" to build the testing application
and also i suggest you to run "./bench_test" (single_thread)to see the performance of this module

you can use this log module by the follow  guiding:
	log_init(LL_TRACE, "mysql", "./log/");
	log_notice("%s [time:%d]\n", "test calling log", time(NULL));
	log_debug("debug msg,only write to log when the loglevel bigger than or equal to debug");
	log_warn("warnning msg will be writing to the error files");
	log_error("you also can change  number of output files by rewrite the macro_define.h");

and also you don't need to call close befor your application exit
if you insist to calling close,please use WARN_W.log_close() INFO_W.log_close() and so so.

this module also provide some convenient macro, you can use it in the following scene
	int function()
	{
		int ret;
		if()
		{
			ret = function_call();
			MACRO_RET(ret != 0, -1);
			MACRO_WARN(ret != 0, "function call failed  [ret:%d]", ret);
			MACRO_WARN_RET(ret != 0, -1, "function call failed  [ret:%d]", ret)
			
		}
	}

The performance of this log module is really depend on how fast your disk is.
here is test result:
1.	Record Size: 280kb
	Cost Time: 42 seconds
	Data File Size: 20GB
	yes. we write 20GB file in 102s,that's means we write 200MB per second.and
	also this is the limitation of SATA.

2.  Record Size: 56byte
	Record Write per Senconds:200,000
	yes,in it's general useage,you can gain high qps from this log module

what will be the next?
author:0xmalloc@gmail.com

you can use  "sh build.sh" to build the testing application
and also i suggest you to run "./bench_test" (single_thread)to see the performance of this module

you can use this log module by the follow  guiding:
	log_init(LL_TRACE, "mysql", "./log/");
	log_notice("%s [time:%d]\n", "test calling log", time(NULL));
	log_debug("debug msg,only write to log when the loglevel bigger than or equal to debug");
	log_warn("warnning msg will be writing to the error files");
	log_error("you also can change  number of output files by rewrite the macro_define.h");

and also you don't need to call close befor your application exit
if you insist to calling close,please use WARN_W.log_close() INFO_W.log_close() and so so.

this module also provide some convenient macro, you can use it in the following scene
	int function()
	{
		int ret;
		if()
		{
			ret = function_call();
			MACRO_RET(ret != 0, -1);
			MACRO_WARN(ret != 0, "function call failed  [ret:%d]", ret);
			MACRO_WARN_RET(ret != 0, -1, "function call failed  [ret:%d]", ret)
			
		}
	}

The performance of this log module is really depend on how fast your disk is.
here is test result:
1.	Record Size: 280kb
	Cost Time: 42 seconds
	Data File Size: 20GB
	yes. we write 20GB file in 102s,that's means we write 200MB per second.and
	also this is the limitation of SATA.

2.  Record Size: 56byte
	Record Write per Senconds:200,000
	yes,in it's general useage,you can gain high qps from this log module

what will be the next?
