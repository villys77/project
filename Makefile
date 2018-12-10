main : main.o functions.o
	gcc -g3 -I3 -o main main.o functions.o -lm

main.o : main.c
	gcc -g3 -I3 -c main.c

functions.o : functions.c
	gcc -g3 -I3 -c functions.c

clean:
	rm main ; rm *.o

