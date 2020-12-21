output: main.o commands.o
	gcc main.o commands.o utils.o -o prog

main.o: main.c
	gcc -c main.c

commands.o: commands.c commands.h
	gcc -c commands.c

utils.o: utils.c utils.h
	gcc -c utils.c

clean:
	rm +*.o prog