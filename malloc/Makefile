trace : main.cpp
	g++  -shared -fPIC -o mtrace.so main.cpp
test : test.c
	gcc test.c -Wl,--no-as-needed -ldl

all : test, trace
	LD_PRELOAD=./mtrace.so ./a.out
