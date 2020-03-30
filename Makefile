a.out: main.o die.o
	g++ main.o die.o

main.o: main.cc die.h
	g++ -c main.cc

die.o: die.cc die.h
	g++ -c die.cc

clean:
	rm -f *.o a.out core
