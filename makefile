all: keylogger

keylogger: main.o help.o
	gcc -o keylogger objects/main.o objects/help.o

main.o: src/main.c src/help.h src/config.h
	gcc -o objects/main.o src/main.c -c -W -Wall

help.o: src/help.c src/help.h
	gcc -o objects/help.o src/help.c -c -W -Wall

clean:
	rm -rf objects/*.o *~ keylogger

