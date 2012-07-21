CC=g++
CFLAGS=-c -O3 -Wall


all: mp3index

mp3index: main.o Index.o IndexError.o MyHash.o Options.o Tools.o
	$(CC) -o mp3index main.o Index.o IndexError.o MyHash.o Options.o Tools.o

main.o: main.cpp Options.h
	$(CC) $(CFLAGS) main.cpp

Index.o: Index.cpp Index.h
	$(CC) $(CFLAGS) Index.cpp

IndexError.o: IndexError.cpp IndexError.h
	$(CC) $(CFLAGS) IndexError.cpp

MyHash.o: MyHash.cpp MyHash.h
	$(CC) $(CFLAGS) MyHash.cpp

Options.o: Options.cpp Options.h
	$(CC) $(CFLAGS) Options.cpp

Tools.o: Tools.cpp Tools.h
	$(CC) $(CFLAGS) Tools.cpp

debug: main.o
	g++ -g -o mp3index main.cpp Index.cpp IndexError.cpp MyHash.cpp Options.cpp Tools.cpp

clean:
	rm -rf *.o mp3index *~
