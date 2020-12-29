output: main.o commands.o
	gcc main.o commands.o -o prog

main.o: main.c
	gcc -c main.c

commands.o: commands.c commands.h
	gcc -c commands.c

clean:
	rm +*.o prog