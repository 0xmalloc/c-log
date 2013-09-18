#include "log.h"
#include <sys/file.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

Log_Writer WARN_W;
Log_Writer INFO_W;
__thread char Log_Writer::m_buffer[_LOG_BUFFSIZE];

bool log_init(LogLevel l, const char* p_modulename, const char* p_logdir)
{
	char _location_str[_LOG_PATH_LEN];
	snprintf(_location_str, _LOG_PATH_LEN, "%s/%s.access", p_logdir, p_modulename);	
	INFO_W.loginit(l, _location_str);
	snprintf(_location_str, _LOG_PATH_LEN, "%s/%s.error", p_logdir, p_modulename);
	//warning级别以上日志去WARN_W  去向由宏决定的 请见macro_define.h
	if(l > LL_WARNING)
		WARN_W.loginit(l, _location_str);
	else
		WARN_W.loginit(LL_WARNING, _location_str);
	return true;
}

const char* Log_Writer::logLevelToString(LogLevel l) {
        switch ( l ) {
			case LL_DEBUG:
				return "DEBUG";
			case LL_TRACE:
				return "TRACE";
			case LL_NOTICE:
				return "NOTICE";
			case LL_WARNING:
				return "WARN" ;
			case LL_ERROR:
				return "ERROR";
			default:
				return "UNKNOWN";
        }
}
	
bool Log_Writer::checklevel(LogLevel l)
{
	if(l >= m_system_level)
		return true;
	else
		return false;
}

bool Log_Writer::loginit(LogLevel l, const  char *filelocation, bool append, bool issync)
{
	MACRO_RET(NULL != fp, false);
    m_system_level = l;
    m_isappend = append; 
    m_issync = issync; 
	if(strlen(filelocation) >= (sizeof(m_filelocation) -1))
	{
		fprintf(stderr, "the path of log file is too long:%d limit:%d\n", strlen(filelocation), sizeof(m_filelocation) -1);
		exit(0);
	}
	//本地存储filelocation  以防止在栈上的非法调用调用
	strncpy(m_filelocation, filelocation, sizeof(m_filelocation));
	m_filelocation[sizeof(m_filelocation) -1] = '\0';
	
	if('\0' == m_filelocation[0])
	{
		fp = stdout;
		fprintf(stderr, "now all the running-information are going to put to stderr\n");
		return true;
	}
	
	fp = fopen(m_filelocation, append ? "a":"w");
	if(fp == NULL)
	{
		fprintf(stderr, "cannot open log file,file location is %s\n", m_filelocation);
		exit(0);
	}
	//setvbuf (fp, io_cached_buf, _IOLBF, sizeof(io_cached_buf)); //buf set _IONBF  _IOLBF  _IOFBF
	setvbuf (fp,  (char *)NULL, _IOLBF, 0);
	fprintf(stderr, "now all the running-information are going to the file %s\n", m_filelocation);
	return true;
}

int Log_Writer::premakestr(char* m_buffer, LogLevel l)
{
    time_t now;
	now = time(&now);;
	struct tm vtm; 
    localtime_r(&now, &vtm);
    return snprintf(m_buffer, _LOG_BUFFSIZE, "%s: %02d-%02d %02d:%02d:%02d ", logLevelToString(l),
            vtm.tm_mon + 1, vtm.tm_mday, vtm.tm_hour, vtm.tm_min, vtm.tm_sec);
}

bool Log_Writer::log(LogLevel l, char* logformat,...)
{
	MACRO_RET(!checklevel(l), false);
	int _size;
	int prestrlen = 0;
	
	char * star = m_buffer;
	prestrlen = premakestr(star, l);
	star += prestrlen;
	
	va_list args;
	va_start(args, logformat);
	_size = vsnprintf(star, _LOG_BUFFSIZE - prestrlen, logformat, args);
	va_end(args);
	
	if(NULL == fp)
		fprintf(stderr, "%s", m_buffer);
	else
		_write(m_buffer, prestrlen + _size);
	return true;
}

bool Log_Writer::_write(char *_pbuffer, int len)
{
	if(0 != access(m_filelocation, W_OK))
	{	
		pthread_mutex_lock(&m_mutex);
		//锁内校验 access 看是否在等待锁过程中被其他线程loginit了  避免多线程多次close 和init
		if(0 != access(m_filelocation, W_OK))
		{
			logclose();
			loginit(m_system_level, m_filelocation, m_isappend, m_issync);
		}
		pthread_mutex_unlock(&m_mutex);
	}

	if(1 == fwrite(_pbuffer, len, 1, fp)) //only write 1 item
	{
		if(m_issync)
          	fflush(fp);
		*_pbuffer='\0';
    }
    else 
	{
        int x = errno;
	    fprintf(stderr, "Failed to write to logfile. errno:%s    message:%s", strerror(x), _pbuffer);
	    return false;
	}
	return true;
}

LogLevel Log_Writer::get_level()
{
	return m_system_level; 
}

bool Log_Writer::logclose()
{
	if(fp == NULL)
		return false;
	fflush(fp);
	fclose(fp);
	fp = NULL;
	return true;
}



