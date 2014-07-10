all: os.func.demo os.bonus.func.demo

os.bonus.func.demo: os.o os.bonus.func.tester utility.o 
		gcc -o os.bonus.func.demo os.o os.bonus.func.tester utility.o

os.func.demo: os.o os.func.tester utility.o 
		gcc -o os.func.demo os.o os.func.tester utility.o

os.perf.demo: os.o os.perf.tester 
		gcc -o os.perf.demo os.o os.perf.tester

os.o: os.c
		gcc -c -o os.o os.c

os.bonus.func.tester: os.bonus.func.tester.c
		gcc -c -o  os.bonus.func.tester os.bonus.func.tester.c

os.func.tester: os.func.tester.c
		gcc -c -o os.func.tester os.func.tester.c

utility.o: utility.c
		gcc -c -o utility.o utility.c

os.perf.tester: os.perf.tester.c
		gcc -c -o os.perf.tester os.perf.tester.c

clean:
		rm -f *.demo *.tester *.o

