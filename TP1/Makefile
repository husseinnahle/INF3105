OPTIONS = -g -O0 -Wall

tp1: tp1.cpp immeuble.o point.o station.o parser.o
	g++ ${OPTIONS} -o tp1 tp1.cpp immeuble.o point.o station.o parser.o

immeuble.o: immeuble.h immeuble.cpp
	g++ $(OPTIONS) -c -o immeuble.o immeuble.cpp
	
point.o: point.h point.cpp
	g++ $(OPTIONS) -c -o point.o point.cpp

station.o: station.h station.cpp
	g++ $(OPTIONS) -c -o station.o station.cpp

parser.o: parser.h parser.cpp
	g++ $(OPTIONS) -c -o parser.o parser.cpp

clean :
	rm -f *.o
	rm -f tp1
	rm -f *~

