all: rsq.func.demo rsq.bonus2.func.demo

rsq.func.demo: rsq.o rsq.func.tester utility.o
	gcc -o rsq.func.demo rsq.o rsq.func.tester utility.o

rsq.o: rsq.c
	gcc -c -o rsq.o rsq.c

rsq.func.tester: rsq.func.tester.c
	gcc -c -o rsq.func.tester rsq.func.tester.c

utility.o: utility.c
	gcc -c -o utility.o utility.c

rsq.bonus2.func.demo: rsq.o rsq.bonus2.func.tester utility.o
	gcc -o rsq.bonus2.func.demo rsq.o rsq.bonus2.func.tester utility.o

rsq.bonus2.func.tester: rsq.bonus2.func.tester.c
	gcc -c -o rsq.bonus2.func.tester rsq.bonus2.func.tester.c

rsq.perf.demo: rsq.o rsq.perf.tester
	gcc -o rsq.perf.demo rsq.o rsq.perf.tester

rsq.perf.tester: rsq.perf.tester.c
	gcc -c -o rsq.perf.tester rsq.perf.tester.c

clean:
	rm -f *.demo *.tester *.o
