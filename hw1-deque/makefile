all: deque.func.demo

deque.func.demo: deque.o deque.func.tester utility.o
	gcc -o deque.func.demo deque.o deque.func.tester utility.o

deque.perf.demo: deque.o deque.perf.tester 
	gcc -o deque.perf.demo deque.o deque.perf.tester 

deque.o: deque.c
	gcc -c -o deque.o deque.c

deque.func.tester: deque.func.tester.c
	gcc -c -o deque.func.tester deque.func.tester.c

utility.o: utility.c
	gcc -c -o utility.o utility.c

deque.perf.tester: deque.perf.tester.c
	gcc -c -o deque.perf.tester deque.perf.tester.c

clean:
	rm -f *.o *.demo *.tester
