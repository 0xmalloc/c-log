#include "log.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sig_alarm (int signo)
{
	exit (0);
}
int main()
{
	alarm (10);
	if (signal (SIGALRM, sig_alarm) == SIG_ERR)
	{
		printf("%s\n", "signal error");
	}
	log_init (LL_DEBUG, "ultimate_test", "./");
	while (1)
	{
		LOG_TRACE("This is a test message!!!");
	}
	return 0;
}
