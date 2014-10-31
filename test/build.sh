#!/bin/bash
SRCPATH="../src/"
rm -f test_log test_pthread_log ultimate_test
g++ -o test_log  "$SRCPATH"log.c    test.c  -lpthread  -I "$SRCPATH"
g++ -o bench_test  "$SRCPATH"log.c    bench_test.c  -lpthread  -I "$SRCPATH"
g++ -o test_pthread_log  "$SRCPATH"log.c    thread_test.c -lpthread -I "$SRCPATH"
g++ -o ultimate_test  "$SRCPATH"log.c    ultimate_test.c  -I "$SRCPATH"

if ls *.access >/dev/null 2>/dev/null  
then
	rm *.access
fi
if ls *.error >/dev/null 2>/dev/null  
then 
	rm *.error
fi
