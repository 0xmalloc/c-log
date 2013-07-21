#!/bin/bash
SRCPATH="../src/"
rm test_log test_pthread_log
g++ -o test_log  "$SRCPATH"log.c    test.c  -lpthread  -I "$SRCPATH"
g++ -o bench_test  "$SRCPATH"log.c    bench_test.c  -lpthread  -I "$SRCPATH"
g++ -o test_pthread_log  "$SRCPATH"log.c    thread_test.c -lpthread -I "$SRCPATH"

if ls *.access >/dev/null 2>/dev/null  
then
	rm *.access
fi
if ls *.error >/dev/null 2>/dev/null  
then 
	rm *.error
fi
