VPATH   =   ./src
CXXFLAGS=   gcc -I  "./include/" -o

all: Dosyalar Olustur Calistir

Dosyalar:
	$(CXXFLAGS)  ./lib/Fonksiyonlar.o  -c ./src/Fonksiyonlar.c

Olustur:
	$(CXXFLAGS)  ./bin/Program  ./lib/Fonksiyonlar.o  ./src/main.c

Calistir:
	./bin/Program
