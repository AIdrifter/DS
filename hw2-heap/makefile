all: heap.func.demo heap.perf.demo

heap.func.demo: heap.o heap.func.tester utility.o
	gcc heap.o heap.func.tester utility.o -o heap.func.demo

heap.perf.demo: heap.o heap.perf.tester
	gcc heap.o heap.perf.tester -o heap.perf.demo

heap.o: heap.c
	gcc -c heap.c -o heap.o

heap.func.tester: heap.func.tester.c 
	gcc -c heap.func.tester.c -o heap.func.tester

utility.o: utility.c
	gcc -c utility.c -o utility.o

heap.perf.tester: heap.perf.tester.c
	gcc -c heap.perf.tester.c -o heap.perf.tester

clean:
	rm -rf *.o *.demo *.tester
