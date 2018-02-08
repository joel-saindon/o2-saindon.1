proc_fan: main.c makeargv.c testsim
	cc -c main.c makeargv.c
	cc main.o makeargv.o -o proc_fan

test: test.c makeargv.c
	cc -c test.c makeargv.c
	cc test.o makeargv.o -o test

testsim: testsim.c
	cc -c testsim.c
	cc testsim.o -o testsim

clean: 
	rm *.o proc_fan testsim test 
