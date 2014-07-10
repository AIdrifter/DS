all: rmq.func.demo

rmq.func.demo: rmq.o rmq.func.tester utility.o
	gcc -o rmq.func.demo rmq.o rmq.func.tester utility.o

rmq.perf.demo: rmq.o rmq.perf.tester
	gcc -o rmq.perf.demo rmq.o rmq.perf.tester

rmq.o: rmq.c
	gcc -c -o rmq.o rmq.c

rmq.func.tester: rmq.func.tester.c
	gcc -c -o rmq.func.tester rmq.func.tester.c

utility.o: utility.c
	gcc -c -o utility.o utility.c

rmq.perf.tester: rmq.perf.tester.c
	gcc -c -o rmq.perf.tester rmq.perf.tester.c

clean:
	rm -f *.demo *.tester *.o
