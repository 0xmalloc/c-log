##What is c-log
a fast ,stable and thread-safe log lib(logger) for C/C++ language

##How to complie 
you can use  "sh build.sh" to build the testing application and also i suggest you to `run "./bench_test" (single_thread)to see the performance`

you can use this log module by the follow  guiding:
```cpp
    log_init(LL_TRACE, "mysql", "./log/");
	LOG_NOTICE("%s [time:%d]", "test calling log", time(NULL));
	LOG_DEBUG("debug msg,only write to log when the loglevel bigger than or equal to debug [time:%d]", time(NULL));
	LOG_WARN("warnning msg will be writing to the error files [time:%d]", time(NULL));
	LOG_ERROR("you also can change  number of output files by rewrite the macro_define.h");
```
and also you don't need to call close befor your application exit
if you insist to calling close,please use WARN_W.log_close() INFO_W.log_close() and so so.

this module also provide some convenient macro, you can use it in the following scene
```cpp
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
```
The performance of this log module is really depend on how fast your disk is.
here is test result:

    case 1
        Record Size: 280kb
    	Cost Time: 42 seconds
    	Data File Size: 20GB
    	yes. we write 20GB file in 102s,that's means we write 200MB per second.and
    	also this is the limitation of SATA.

    case 2 
        Record Size: 56byte
    	Record Write per Senconds:200,000
    	yes,in it's general useage,you can gain high qps from this log module

what will be the next?


##About Author

```javascript
  var 0xmalloc = {
    nickName  : "zealot yin",
    email : '0xmalloc@gmail.com',
    site : "http://www.cnblogs.com/Creator/"
    weibo : "http://www.weibo.com/zealotyin"
  }
```
