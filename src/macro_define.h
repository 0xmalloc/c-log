#ifndef  _MACRO_DEFINE
#define  _MACRO_DEFINE
//============basic===================

#define log_error(log_fmt, log_arg...) \
    WARN_W.log(LL_ERROR, log_fmt, ##log_arg)

#define log_warn(log_fmt, log_arg...) \
	WARN_W.log(LL_WARNING, log_fmt, ##log_arg)

#define log_notice(log_fmt, log_arg...) \
	INFO_W.log(LL_NOTICE, log_fmt, ##log_arg)

#define log_trace(log_fmt, log_arg...) \
    INFO_W.log(LL_TRACE, log_fmt, ##log_arg)

#define log_debug(log_fmt, log_arg...) \
    INFO_W.log(LL_DEBUG, log_fmt, ##log_arg)

//============extend===================
#define MACRO_RET(condition, return_val) {\
    if (condition) {\
        return return_val;\
    }\
}

#define MACRO_WARN(condition, log_fmt, log_arg...) {\
    if (condition) {\
        log_warn( log_fmt, ##log_arg);\
    }\
}

#define MACRO_WARN_RET(condition, return_val, log_fmt, log_arg...) {\
    if ((condition)) {\
        log_warn( log_fmt, ##log_arg);\
		return return_val;\
    }\
}
#endif
