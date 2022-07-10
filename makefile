all: keylogger.out

keylogger.out: main.o help.o keylogger.o
	gcc -o keylogger.out objects/main.o objects/help.o objects/keylogger.o

main.o: src/main.c src/help.h src/config.h
	gcc -o objects/main.o src/main.c -c -W -Wall

help.o: src/help.c src/help.h
	gcc -o objects/help.o src/help.c -c -W -Wall

keylogger.o: src/keylogger.c src/keylogger.h
	gcc -o objects/keylogger.o src/keylogger.c -c -W -Wall

clean:
	rm -rf objects/*.o *~ keylogger

