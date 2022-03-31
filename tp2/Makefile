# Makefile pour TP2.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).


# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
#OPTIONS = -g -O0 -Wall
OPTIONS = -O2 -Wall

all : tp2 testdate

tp2 : tp2.cpp commande.o carte.o pointst.o date.o epicerie.o arbreavl.h arbremap.h tableau.h
	g++ ${OPTIONS} -o tp2 tp2.cpp commande.o carte.o pointst.o date.o epicerie.o

commande.o : commande.cpp commande.h pointst.o date.o carte.o tableau.h
	g++ ${OPTIONS} -c -o commande.o commande.cpp

carte.o : carte.cpp carte.h epicerie.o arbreavl.h
	g++ ${OPTIONS} -c -o carte.o carte.cpp

pointst.o : pointst.cpp pointst.h
	g++ ${OPTIONS} -c -o pointst.o pointst.cpp

date.o : date.cpp date.h
	g++ ${OPTIONS} -c -o date.o date.cpp

epicerie.o : epicerie.cpp epicerie.h pointst.o arbremap.h
	g++ ${OPTIONS} -c -o epicerie.o epicerie.cpp

testdate : testdate.cpp date.o
	g++ $(OPTIONS) -o testdate testdate.cpp date.o

clean:
	rm -rf tp2 testdate *~ *.o

