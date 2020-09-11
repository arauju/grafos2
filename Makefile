main: GRAFOmatriz.c FILA.c main.c
	gcc -O3 FILA.c GRAFOmatriz.c main.c -o main

clean :
	rm main

