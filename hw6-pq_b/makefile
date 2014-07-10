all: pq_b.func.demo

pq_b.func.demo: pq_b.o pq_b.func.tester utility.o
	gcc -o pq_b.func.demo pq_b.o pq_b.func.tester utility.o

pq_b.perf.demo: pq_b.o pq_b.perf.tester
	gcc -o pq_b.perf.demo pq_b.o pq_b.perf.tester

pq_b.o: pq_b.c
	gcc -c -o pq_b.o pq_b.c

pq_b.func.tester: pq_b.func.tester.c
	gcc -c -o pq_b.func.tester pq_b.func.tester.c

utility.o: utility.c
	gcc -c -o utility.o utility.c

pq_b.perf.tester: pq_b.perf.tester.c
	gcc -c -o pq_b.perf.tester pq_b.perf.tester.c

clean:
	rm -f *.demo *.tester *.o
