a.out: main.o die.o table.o player.o
	g++ main.o die.o table.o player.o

main.o: main.cc table.h
	g++ -c main.cc

die.o: die.cc die.h
	g++ -c die.cc

table.o: table.cc table.h player.h
	g++ -c table.cc

player.o: player.cc player.h die.h
	g++ -c player.cc

clean:
	rm -f *.o a.out core
