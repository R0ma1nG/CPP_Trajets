#Authors : Quentin, Victor, Romain

FLAGS=-Wall -std=c++0x 
CFLAGS=-c -D MAP
COMP=g++
EXENAME=TP2

TP2: Catalogue.o ListeTrajets.o TrajetCompose.o TrajetSimple.o Main.o
	$(COMP) -o $(EXENAME) Catalogue.o ListeTrajets.o TrajetCompose.o TrajetSimple.o Main.o $(FLAGS)

Catalogue.o : Catalogue.h Catalogue.cpp
	$(COMP) $(CFLAGS) Catalogue.cpp $(FLAGS)

ListeTrajets.o : ListeTrajets.h ListeTrajets.cpp
	$(COMP) $(CFLAGS) ListeTrajets.cpp $(FLAGS)

TrajetSimple.o : TrajetSimple.h TrajetSimple.cpp
	$(COMP) $(CFLAGS) TrajetSimple.cpp $(FLAGS)

TrajetCompose.o : TrajetCompose.h TrajetCompose.cpp
	$(COMP) $(CFLAGS) TrajetCompose.cpp $(FLAGS)
	
Main.o: Main.cpp
	$(COMP) $(CFLAGS) Main.cpp $(FLAGS)

clean : 
	rm -rf *.o

