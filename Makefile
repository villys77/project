main : main.o functions.o
	gcc -I3 -g3 -o main main.o functions.o -lm

main.o : main.c
	gcc -I3 -g3 -c main.c

functions.o : functions.c
	gcc -I3 -g3 -c functions.c


clean:
	rm main ; rm *.o

