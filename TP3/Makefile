OPTIONS = -O2 -Wall

all : tp3

tp3: tp3.o carte.o lieu.o coordonnee.o
	g++ $(OPTIONS) -g -o tp3 tp3.o carte.o lieu.o coordonnee.o

tp3.o: tp3.cpp carte.h lieu.h coordonnee.h
	g++ $(OPTIONS) -c -o tp3.o tp3.cpp

carte.o: carte.h carte.cpp lieu.h
	g++ $(OPTIONS) -c -o carte.o carte.cpp

lieu.o: lieu.h lieu.cpp coordonnee.h
	g++ $(OPTIONS) -c -o lieu.o lieu.cpp

coordonnee.o: coordonnee.h coordonnee.cpp
	g++ $(OPTIONS) -c -o coordonnee.o coordonnee.cpp

clean :
	rm -f *.o
	rm -f tp3
	rm -f *~

