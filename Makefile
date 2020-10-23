all: sudoku.o main.o compile run clean

compile:
	@gcc sudoku.o main.o -o s -lm

main.o:
	@gcc -c main.c

sudoku.o:
	@gcc -c sudoku.c


clean:
	 @rm main.o sudoku.o s

run:
	@./s

zip:
	zip -r sudoku *.c *.h Makefile
