all: stack.func.demo stack.perf.demo

stack.func.demo: stack.o stack.func.tester utility.o
	gcc stack.o stack.func.tester utility.o -o stack.func.demo

stack.perf.demo: stack.o stack.perf.tester
	gcc stack.o stack.perf.tester -o stack.perf.demo

stack.o: stack.c
	gcc -c stack.c -o stack.o

stack.func.tester: stack.func.tester.c 
	gcc -c stack.func.tester.c -o stack.func.tester

utility.o: utility.c
	gcc -c utility.c -o utility.o

stack.perf.tester: stack.perf.tester.c
	gcc -c stack.perf.tester.c -o stack.perf.tester

clean:
	rm -rf *.o *.demo *.tester
