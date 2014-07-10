all: disj.func.demo 

disj.func.demo: disj.o disj.func.tester 
	gcc disj.o disj.func.tester -o disj.func.demo

disj.o: disj.c
	gcc -c disj.c -o disj.o

disj.func.tester: disj.func.tester.c 
	gcc -c disj.func.tester.c -o disj.func.tester

clean:
	rm -rf *.o *.demo *.tester
